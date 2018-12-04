#include "recogniser.h"

int Recognizer::check_wav_header(char *header, int expected_sr) {
	int sr;

	if (header[34] != 0x10) {
		E_ERROR("Input audio file has [%d] bits per sample instead of 16\n", header[34]);
		return 0;
	}
	if (header[20] != 0x1) {
		E_ERROR("Input audio file has compression [%d] and not required PCM\n", header[20]);
		return 0;
	}
	if (header[22] != 0x1) {
		E_ERROR("Input audio file has [%d] channels, expected single channel mono\n", header[22]);
		return 0;
	}
	sr = ((header[24] & 0xFF) | ((header[25] & 0xFF) << 8) | ((header[26] & 0xFF) << 16) | ((header[27] & 0xFF) << 24));
	if (sr != expected_sr) {
		E_ERROR("Input audio file has sample rate [%d], but decoder expects [%d]\n", sr, expected_sr);
		return 0;
	}
	return 1;
}

void Recognizer::recognize_from_file(std::string inn, std::string outt) {
	int16 adbuf[2048];
	const char *hyp;
	uint8 utt_started, in_speech;

	if (inn != "") {
		inName = inn;
	}
	if (outt != "") {
		outName = outt;
	}

	std::ofstream out(outName.c_str(), std::ios::binary | std::ios::ate);
	std::ifstream in(inName.c_str(), std::ios::binary);
	if (!in.is_open()) {
		std::cout << "Failed to open incoming file\n";
	}
	if (!out.is_open()) {
		std::cout << "Failed to open outcoming file\n";
	}

	char waveheader[44];
	in.read(waveheader, 44);
	if (!check_wav_header(waveheader, (int)cmd_ln_float32_r(config, "-samprate"))) {
		std::cout << "Failed to process file" << inName << "due to format mismatch.\n";
		return;
	}

	if (inName.find(".mp3") != -1) {
		std::cout << "Can not decode mp3 files, convert input file to WAV 8kHz 16 - bit mono before decoding.\n";
		return;
	}

	ps_start_utt(ps);
	utt_started = FALSE;

	while (!in.eof()) {
		in.read(reinterpret_cast<char *>(&adbuf), sizeof(int16) * 2048);
		std::cout << in.gcount() << std::endl;
		ps_process_raw(ps, adbuf, in.gcount() / 2, FALSE, FALSE);
		in_speech = ps_get_in_speech(ps);
		if (in_speech && !utt_started) {
			utt_started = TRUE;
		}
		if (!in_speech && utt_started) {
			ps_end_utt(ps);
			hyp = ps_get_hyp(ps, NULL);
			if (hyp != NULL) {
				out << hyp;
			}
			fflush(stdout);

			ps_start_utt(ps);
			utt_started = FALSE;
		}
	}

	ps_end_utt(ps);
	if (utt_started) {
		hyp = ps_get_hyp(ps, NULL);
		if (hyp != NULL) {
			out << hyp;
			out << '\n';
		}
	}

	in.close();
	out.close();
}