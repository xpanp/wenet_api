#include "glog/logging.h"
#include <iostream>
#include "wenet_api.h"
#include "wav.h"

int main(int argc, char* argv[]) {
	const char *model_dir = argv[1];
	std::string wav_path = argv[2];
  	google::InitGoogleLogging(argv[0]);

	wenet_set_log_level(2);

	void* decoder = wenet_init(model_dir);
	wenet_set_timestamp(decoder, 0);
	wenet_set_chunk_size(decoder, 320);

	phs::WavReader wav_reader(wav_path);
	std::vector<int16_t> data(wav_reader.num_samples());
	for (int i = 0; i < wav_reader.num_samples(); i++) {
		data[i] = static_cast<int16_t>(*(wav_reader.data() + i));
	}

	for (int i = 0; i < 2; i++) {
		// Return the final result when last is 1
		wenet_decode(decoder, reinterpret_cast<const char*>(data.data()),
					data.size() * 2, 1);
		const char* result = wenet_get_result(decoder);
		LOG(INFO) << i << " " << result;
		wenet_reset(decoder);
	}

	wenet_free(decoder);
	return 0;
}