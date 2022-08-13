base_dir=~/wenet
export LD_LIBRARY_PATH="$base_dir/wenet_api/libs/onnx_lib: \
    $base_dir/wenet_api/fc_base/glog-build/:$LD_LIBRARY_PATH"
export GLOG_logtostderr=1
export GLOG_v=2
wav_path=$base_dir/wav/14-208-0002.wav
model_dir=$base_dir/env/librispeech_0813
./build/api_main $model_dir $wav_path  2>&1 | tee log.txt
