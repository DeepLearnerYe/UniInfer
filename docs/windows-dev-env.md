# UniInfer Windows 开发环境安装文档

## 目标环境

推荐环境：

```text
Windows 11 x64
Visual Studio 2022 Community 或 Build Tools
CMake
Git
NVIDIA Driver
CUDA Toolkit 12.9 Update 1 或 13.2 Update 1
TensorRT 11.x Windows ZIP
```

当前 UniInfer 阶段只需要 C++、CMake、Git。CUDA 和 TensorRT 是后面实现 TensorRT 后端时再用，但可以提前装好。

NVIDIA CUDA Windows 文档要求 CUDA-capable GPU、受支持 Windows、受支持 Visual Studio 和 CUDA Toolkit。TensorRT 11.0.0 文档列出的 CUDA 支持是 CUDA 12.x 和 CUDA 13.x 中的指定版本，所以建议先用 CUDA 12.9 Update 1，稳定性更好。

参考：

- [CUDA Installation Guide for Microsoft Windows](https://docs.nvidia.com/cuda/cuda-installation-guide-microsoft-windows/)
- [TensorRT Prerequisites](https://docs.nvidia.com/deeplearning/tensorrt/latest/installing-tensorrt/prerequisites.html)

## 一、安装最小 C++ 环境

### 1. 安装 Visual Studio 2022 Community 或 Build Tools

安装时选择 workload：

```text
Desktop development with C++
```

建议勾选组件：

```text
MSVC v143 C++ build tools
Windows 10/11 SDK
C++ CMake tools for Windows
```

参考：

- [Install C and C++ support in Visual Studio](https://learn.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-170)

### 2. 安装 Git

下载：

```text
https://git-scm.com/download/win
```

### 3. 安装 CMake

下载 Windows x64 Installer：

```text
https://cmake.org/download/
```

安装时勾选：

```text
Add CMake to the system PATH
```

参考：

- [CMake Download](https://cmake.org/download/)

## 二、验证最小 C++ 环境

打开：

```text
x64 Native Tools Command Prompt for VS 2022
```

不要用普通 cmd。Microsoft 官方建议使用 Developer Command Prompt，因为它会自动设置 MSVC 的 `PATH`、`INCLUDE`、`LIB` 等环境变量。

参考：

- [Use the Microsoft C++ Build Tools from the command line](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170)

执行：

```bat
cl
cmake --version
git --version
```

进入 UniInfer 仓库：

```bat
cd /d D:\your\path\UniInfer
cmake -S . -B build
cmake --build build --config Release
.\build\Release\detect_mock.exe
```

如果输出类似：

```text
class_id = 0, score = 0.99, box = (160, 120, 480, 360)
```

说明第一阶段环境可用。

## 三、安装 NVIDIA Driver

先安装最新 NVIDIA 显卡驱动。

验证：

```bat
nvidia-smi
```

能看到 GPU、Driver Version 即可。

TensorRT 文档要求 Windows driver 至少 r537；CUDA 13.x 需要 r580 或更高。

参考：

- [TensorRT Prerequisites](https://docs.nvidia.com/deeplearning/tensorrt/latest/installing-tensorrt/prerequisites.html)

## 四、安装 CUDA Toolkit

推荐先装：

```text
CUDA Toolkit 12.9 Update 1
```

如果你明确要跟最新 TensorRT 11.x 的 CUDA 13 包配套，也可以用：

```text
CUDA Toolkit 13.2 Update 1
```

下载：

```text
https://developer.nvidia.com/cuda-downloads
```

安装顺序建议：

```text
Visual Studio / Build Tools
NVIDIA Driver
CUDA Toolkit
```

验证：

```bat
nvcc -V
```

NVIDIA 官方建议进一步编译运行 `deviceQuery` 和 `bandwidthTest` 来验证 CUDA 硬件通信。

参考：

- [CUDA verification](https://docs.nvidia.com/cuda/cuda-installation-guide-microsoft-windows/)

## 五、安装 TensorRT

Windows 推荐使用 ZIP 包。TensorRT 官方说明 ZIP 方式适合 Windows C++/Python 开发、自定义安装路径，并包含 C++ headers。

参考：

- [TensorRT Windows ZIP installation](https://docs.nvidia.com/deeplearning/tensorrt/latest/installing-tensorrt/install-zip.html)

步骤：

1. 登录 NVIDIA Developer。
2. 下载 TensorRT Windows x64 ZIP。
3. 解压到固定目录，例如：

```text
D:\SDK\TensorRT-11.0.0.0
```

4. 设置环境变量：

```text
TRT_ROOT=D:\SDK\TensorRT-11.0.0.0
```

5. 把下面路径加入系统 `PATH`：

```text
%TRT_ROOT%\bin
```

之后重新打开终端。

后面 UniInfer 写 TensorRT 后端时，CMake 大概率会这样传：

```bat
cmake -S . -B build -DTRT_ROOT=%TRT_ROOT%
```

## 六、可选工具

推荐但不是现在必须：

```text
VS Code
CMake Tools extension
C/C++ extension
Ninja
Python 3.10-3.12
Netron
```

Python 后面可能用于：

```text
ONNX 导出
模型检查
TensorRT Python 工具
测试脚本
```

Netron 用来看 ONNX 输入输出结构，很适合学习模型 IO。

## 七、最终检查清单

装完后确认这些命令可用：

```bat
cl
cmake --version
git --version
nvidia-smi
nvcc -V
```

确认这些环境变量：

```bat
echo %CUDA_PATH%
echo %TRT_ROOT%
```

确认这些文件存在：

```text
%CUDA_PATH%\bin\nvcc.exe
%TRT_ROOT%\include\NvInfer.h
%TRT_ROOT%\lib\nvinfer.lib
%TRT_ROOT%\bin\nvinfer_*.dll 或 nvinfer.dll
```
