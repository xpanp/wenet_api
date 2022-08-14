# wenet_api

A demo use wenet official api with onnx

[wenet](https://github.com/wenet-e2e/wenet)是一个端到端的语音识别模型，为语音识别提供全栈解决方案，由于仅依赖Pytorch，且部署方便（Onnx、LibTorch）、准确率高、文档齐全，故非常适合用于生产环境以及学习。

本项目主要使用wenet提供的api，进行二次开发，不需要依赖原环境。

## Detail

- 建议在ubuntu18.04上进行开发以及部署，否则可能需要解决各种gcc版本问题。
- 截止目前(2022.08.13)，wenet官方代码中只提供了Libtorch版本的api代码，但只需要简单修改即可支持Onnx。具体编译好的动态库可以在[这里](https://github.com/xpanp/wenet_api/releases)获取到。
- 由于gflags模块在动态库中已经包含使用，在main中再次引入时总是存在冲突，因此目前在该项目中没有使用gflags解析命令行参数。
- 目前是在[librispeech](http://www.openslr.org/12)数据集上进行测试的，这是一个大型(1000小时)阅读英语演讲语料库 ，本人训练好的模型可以在[这里](https://github.com/xpanp/wenet_api/releases)获取到，包括onnx模型以及LM模型。
- 测试语料使用librispeech中的数据较好，日常对话的语料识别效果并不好（这和训练模型的语料有关）。[这里](https://github.com/xpanp/wenet_api/releases)提供一条librispeech中的语料，便于测试。若想使用其它语料，要求文件为wav格式且语音为16000采样率-16bit-单通道的pcm数据，才能保证正确识别。

## Build

- 克隆仓库

```bash
git clone https://github.com/xpanp/wenet_api.git
```

- 下载依赖项

在[这里](https://github.com/xpanp/wenet_api/releases)下载动态库、测试语料、训练好的模型。

其中将动态库解压后放在`./libs/`目录中，目录结构为：
```
- wenet_api
    - libs
        - include
        - onnx_lib
        - torch_lib
```

- 编译

```bash
mkdir build && cd build
# Onnx
cmake ..
# LibTorch
# cmake -DTORCH=ON -DONNX=OFF ..
make
```

- 修改run.sh，正确指定模型、语音、动态库的位置

```bash
base_dir=~/wenet
export LD_LIBRARY_PATH="$base_dir/wenet_api/libs/onnx_lib: \
    $base_dir/wenet_api/fc_base/glog-build/:$LD_LIBRARY_PATH"
export GLOG_logtostderr=1
export GLOG_v=2
wav_path=$base_dir/wav/14-208-0002.wav
model_dir=$base_dir/env/librispeech_0813
./build/api_main $model_dir $wav_path  2>&1 | tee log.txt
```

