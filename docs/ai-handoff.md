# UniInfer AI Handoff

本文件用于把 UniInfer 当前学习和实现进度交接给服务器上的 AI。请后续 AI 继续遵守：用户希望自己手写代码，AI 负责讲解、规划、代码 review 和定位问题；除非用户明确要求，不要直接代写或大规模改仓库代码。

## 1. 项目目标

UniInfer 是一个从零搭建的 C++ 推理框架练习项目，不再沿用 trtyolo 名称。长期目标是支持：

- 多模型：检测、分类、分割、OCR、Embedding 等。
- 多后端：Mock、TensorRT、ONNX Runtime、OpenVINO、NPU SDK 等。
- 多设备：CPU、NVIDIA GPU、国产 NPU、边缘设备。
- 高性能：batch 推理、CUDA stream、异步拷贝、CUDA Graph、多 context、多线程调度。
- 可学习：每一步都从最小可运行代码出发，逐渐替换 mock 部件。

当前阶段还不是完整推理框架，而是一个逐步教学项目。不要一上来重构成复杂工业框架。

## 2. 命名和风格约定

- 项目名：`UniInfer`。
- include 路径：`include/uninfer/...`。
- namespace：`uninfer`。
- target/library 名：`uninfer`。
- 类型名：`UpperCamelCase`，例如 `ModelConfig`、`HostBuffer`、`MockDetectionModel`。
- 函数名：`lowerCamelCase`，例如 `dataTypeSize()`、`elementCount()`、`computeBytes()`、`refreshBytes()`。
- 变量名、成员变量、结构体字段：`snake_case`，例如 `model_path`、`device_id`、`class_id`、`host_data_`。
- enum 值：`k` + `UpperCamelCase`，例如 `DataType::kFloat32`、`BackendType::kMock`。
- 头文件应自包含：自己直接用到的标准库或项目类型，就自己 include，不依赖间接包含。
- 代码格式暂时不强求，后续可以用 clang-format 统一。

## 3. 当前总体架构

当前已经有一条可运行的 mock 检测 pipeline：

```text
ModelConfig
  -> createDetectionModel(config)
  -> MockDetectionModel(config)
  -> MockPreprocessor
  -> MockBackend
  -> MockDetectionDecoder
  -> std::vector<DetectionResult>
```

运行时数据流：

```text
std::vector<Image>
  -> MockPreprocessor::preprocess(images)
  -> Tensor input, shape [N, 3, H, W]
  -> MockBackend::infer({input})
  -> Tensor output, shape [N, 6], HostBuffer owns memory
  -> MockDetectionDecoder::decode(outputs)
  -> std::vector<DetectionResult>
```

重要语义：

- `std::vector<Tensor>` 传给 backend 表示“模型输入 tensor 列表”，不是 batch 里的每张图。
- batch size 由 tensor shape 的第 0 维表示，即 `shape.dims[0]`。
- 常规图像模型输入一般是一个 tensor：`[N, C, H, W]`。
- `TensorShape` 只描述形状。
- `Tensor` 描述一份数据：name、dtype、shape、bytes、buffer。
- `IBuffer/HostBuffer` 负责真实内存所有权。

## 4. 当前已完成模块

### 4.1 基础数据结构

已完成或已有：

- `Image`
- `PixelFormat`
- `Box`
- `Detection`
- `DetectionResult`
- `BackendType`
- `TaskType`
- `ModelConfig`
- `DataType`
- `TensorShape`
- `Tensor`

`TensorShape` 当前支持：

- `rank()`
- `empty()`
- `elementCount()`

`Tensor` 当前支持：

- `data()` / `data() const`
- `empty()`
- `elementCount()`
- `computeBytes()`
- `refreshBytes()`

注意：运行时 `TensorShape` 不允许负数维度。TensorRT 模型描述里可以有 `-1` 动态维度，但运行时 Tensor 必须是确定 shape，例如 `[4, 3, 640, 640]`。后续动态 shape 应该另建 `TensorDesc`、`ModelInputDesc` 或 profile 描述结构。

### 4.2 接口

已有接口：

- `IDetectionModel`
  - 单图 predict
  - batch predict
- `IBackend`
  - `load(model_path)`
  - `infer(std::vector<Tensor>)`
- `IDecoder<ResultType>`
- `IPreprocessor`

设计原则：batch 是核心路径，单图接口复用 batch 接口。

### 4.3 Mock 实现

已有：

- `MockDetectionModel`
- `MockPreprocessor`
- `MockBackend`
- `MockDetectionDecoder`

当前 mock output 约定：

```text
shape = [N, 6]
每行 = left, top, right, bottom, score, class_id
```

示例输出曾验证正常：

```text
backend = Mock
image[0]
class_id = 0, score = 0.99, box = (160, 120, 480, 360)
image[1]
class_id = 0, score = 0.99, box = (160, 120, 480, 360)
image[2]
class_id = 0, score = 0.99, box = (160, 120, 480, 360)
```

### 4.4 Buffer 抽象

已经从旧版 `Buffer` 过渡到：

```text
IBuffer
  -> HostBuffer
  -> future CudaDeviceBuffer
  -> future CudaPinnedHostBuffer
  -> future CudaUnifiedBuffer
```

当前 `Tensor` 持有：

```cpp
std::shared_ptr<IBuffer> buffer;
```

当前 `MockBackend` 创建：

```cpp
output.buffer = std::make_shared<HostBuffer>();
output.buffer->resize(output.bytes);
```

然后通过：

```cpp
auto* data = static_cast<float*>(output.data());
```

写入 buffer 内存。

当前 `MockDecoder` 通过：

```cpp
const auto* data = static_cast<const float*>(output.data());
```

读取 buffer 内存。

这一步已经把职责拆开：

```text
TensorShape: 形状
Tensor: 数据描述
IBuffer/HostBuffer: 内存所有权
```

## 5. CUDA 当前状态

已经新增可选 CUDA 开关：

```cmake
option(UNINFER_ENABLE_CUDA "Build UniInfer with CUDA support" OFF)
```

当前 CMake 逻辑：

- 默认 `UNINFER_ENABLE_CUDA=OFF`。
- 关闭 CUDA 时排除 `src/cuda_check.cpp`。
- 开启 CUDA 时 `find_package(CUDAToolkit REQUIRED)`。
- 开启 CUDA 时链接 `CUDA::cudart`。
- 开启 CUDA 时给 target 添加 `UNINFER_ENABLE_CUDA=1` 编译宏。

关键点：`option()` 只是开关，必须配合 `if()` 控制源文件、include、link 和 compile definitions。

当前 `cuda_check.hpp` 应该整体包在：

```cpp
#ifdef UNINFER_ENABLE_CUDA
...
#endif
```

原因：CUDA 关闭时不能暴露 `cudaError_t`，否则没有 CUDA 的机器 include 这个头会编译失败。

当前 CUDA check 设计：

```cpp
#define UNINFER_CUDA_CHECK(expr) \
    ::uninfer::cudaCheck((expr), __FILE__, __LINE__, #expr)
```

`#expr` 是宏字符串化，会把表达式转成字符串。`__FILE__`、`__LINE__` 是编译器预定义宏，用于错误定位。

后续 CUDA API 都应该用：

```cpp
UNINFER_CUDA_CHECK(cudaMalloc(&ptr, bytes));
```

不要裸调用 CUDA API 后忽略返回值。

## 6. 已讲过的重要知识点

### 6.1 TensorShape vs Tensor

```text
TensorShape = 尺寸标签
Tensor = 数据描述对象
```

`TensorShape` 只管：

```text
shape.dims = [N, C, H, W]
rank
element count
```

`Tensor` 管：

```text
name
dtype
shape
bytes
buffer/data
```

`shape.empty()` 表示 shape 没设置；`tensor.empty()` 表示元素数为 0。

### 6.2 动态 shape

模型描述可以有：

```text
[-1, 3, 640, 640]
```

但运行时 Tensor 不应该有 `-1`，必须变成：

```text
[batch, 3, 640, 640]
```

TensorRT 动态 batch 后续需要：

- optimization profile
- min/opt/max shape
- context set input shape
- 根据真实 shape 重新计算 binding bytes
- 必要时重新分配 device buffer

### 6.3 Batch 语义

单图 predict 复用 batch predict：

```cpp
return predict(std::vector<Image>{image}).front();
```

不要让 batch 接口循环调用单图接口，因为真实推理后端通常以 `[N, C, H, W]` 作为核心输入。

### 6.4 Buffer 内存类型

- `kHost`: 普通 CPU 内存。
- `kDevice`: GPU 显存，通常 `cudaMalloc/cudaFree`。
- `kPinnedHost`: 页锁定 CPU 内存，通常 `cudaHostAlloc/cudaFreeHost`，适合异步 H2D/D2H 拷贝。
- `kUnified`: 统一内存，通常 `cudaMallocManaged/cudaFree`，方便但不一定最快。

`cudaHostAlloc` 不等同于 `malloc`。二者都返回 CPU 可访问地址，但 pinned memory 不能被操作系统随意换页，适合 GPU DMA 和 `cudaMemcpyAsync`。

### 6.5 C++ 所有权和移动

`IBuffer` 禁止拷贝是合理的，因为 buffer 是资源所有者。未来如果是 GPU 显存，浅拷贝会导致重复释放，深拷贝成本高且语义复杂。

移动构造可以允许，因为移动表示资源所有权转移。

`noexcept` 对移动构造有价值，尤其对象放进 `std::vector` 时，容器扩容更愿意使用 noexcept move。

### 6.6 const data 重载

```cpp
void* data();
const void* data() const;
```

前者用于可写对象，后者用于只读对象。只读对象不能暴露可写指针。

### 6.7 `explicit`

单参数构造函数建议加 `explicit`，避免隐式转换偷偷构造对象。

### 6.8 异常语义

- `std::invalid_argument`: 调用者传入的参数不合法。
- `std::runtime_error`: 请求本身合理，但运行过程中无法完成，或后端输出损坏。

### 6.9 shape/bytes 校验

Decoder 读取 tensor 前应按顺序校验：

1. outputs 是否为空。
2. shape rank 是否符合预期。
3. dtype 是否符合 decoder 读取方式。
4. batch 是否合理。
5. buffer 是否存在。
6. tensor.bytes 和 buffer->bytes 是否足够。
7. data 指针是否非空。

例如 mock decoder 当前应该先确认 `DataType::kFloat32`，再 `static_cast<const float*>`。

## 7. 当前注意点和小坑

- `src/buffer.cpp` 里如果还保留 `<stdexcept>`，当前可能已经不用，可以清理。
- `model.cpp.o has no symbols` 只是说明当前 `model.cpp` 没有实际符号，不是关键错误。
- CMake 使用 `GLOB_RECURSE CONFIGURE_DEPENDS` 后，新文件会触发重新配置，但 CUDA 文件必须用 list filter 或更清晰的目录组织避免无 CUDA 环境编译失败。
- `cuda_check.hpp` 不应该在 CUDA 关闭时暴露 `cudaError_t`。
- `const char*` 是语言基本指针类型，不来自 `<string>`。
- `.cpp` 里使用 `std::string` 和 `std::to_string` 应自己 include `<string>`。
- `std::uint8_t` 来自 `<cstdint>`。
- `std::numeric_limits` 来自 `<limits>`。
- 用了 `std::vector` 最好自己 include `<vector>`。
- 用了 `std::make_shared` 最好自己 include `<memory>`。

## 8. 推荐的下一步课程路线

### 下一课：CudaDeviceBuffer

目标：写第一个真正 CUDA RAII 对象。

建议新增：

```text
include/uninfer/cuda_buffer.hpp
src/cuda_buffer.cpp
```

或者把类放在现有 `buffer.hpp` 中，但 `.cpp` 实现放到 CUDA 可选编译文件里。为了减少无 CUDA 环境污染，更建议单独文件。

初始类：

```cpp
#ifdef UNINFER_ENABLE_CUDA

class CudaDeviceBuffer : public IBuffer
{
public:
    CudaDeviceBuffer() = default;
    ~CudaDeviceBuffer() override;

    CudaDeviceBuffer(const CudaDeviceBuffer&) = delete;
    CudaDeviceBuffer& operator=(const CudaDeviceBuffer&) = delete;

    CudaDeviceBuffer(CudaDeviceBuffer&& other) noexcept;
    CudaDeviceBuffer& operator=(CudaDeviceBuffer&& other) noexcept;

    MemoryType memoryType() const override;
    std::size_t bytes() const override;
    bool empty() const override;

    void* data() override;
    const void* data() const override;

    void resize(std::size_t bytes) override;
    void clear() override;

private:
    void* data_ = nullptr;
    std::size_t bytes_ = 0;
};

#endif
```

实现重点：

- `resize(0)` 应该清空。
- 如果已有内存且大小足够，可以先简单释放重分配，后续再优化为 capacity 策略。
- `clear()` 调用 `cudaFree(data_)`，然后置空。
- 析构函数必须释放显存。
- 移动构造/移动赋值必须转移 `data_` 和 `bytes_`，并把 old object 置空。
- 使用 `UNINFER_CUDA_CHECK(cudaMalloc(...))` 和 `UNINFER_CUDA_CHECK(cudaFree(...))`。

注意：`cudaFree` 在析构函数里如果失败，不应该从析构函数抛异常。第一版可以在 `clear()` 里检查，在析构里尽量直接释放或捕获错误。这个点可以单独教学。

### 再下一课：CudaPinnedHostBuffer

目标：用 `cudaHostAlloc/cudaFreeHost` 实现 pinned host memory。

用途：为 `cudaMemcpyAsync` 提供高效 host staging buffer。

### 再下一课：CudaStream

目标：RAII 封装 `cudaStream_t`。

接口可能包括：

- create/destroy
- `get()`
- `synchronize()`

### 再下一课：异步拷贝工具

目标：封装：

- H2D: host -> device
- D2H: device -> host
- D2D: device -> device

API 可考虑：

```cpp
copyAsync(dst_buffer, src_buffer, bytes, stream);
```

但要先明确 src/dst 的 `MemoryType`。

### 后续：TensorRTBackend

进入 TensorRT 前，需要这些基础设施：

- CudaDeviceBuffer
- CudaPinnedHostBuffer
- CudaStream
- TensorRT logger
- Engine loader
- Runtime/Engine/Context RAII 管理
- Binding 信息解析
- 输入输出 TensorDesc
- 动态 shape/profile 支持

## 9. 当前建议的 AI 教学方式

后续 AI 应继续按这个节奏：

1. 先讲这一课为什么需要。
2. 给出最小类/函数设计。
3. 解释每个 C++/CUDA 概念。
4. 让用户自己手写。
5. 用户完成后再 review。
6. 不要一次性塞完整 TensorRTBackend。

用户是从零学习，但目标很专业。请保持节奏：小步、真实、可编译、逐步替换 mock。

