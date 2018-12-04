#include <iostream>
#include <fstream>
#include <string>
#include "recogniser.h"

#pragma comment(lib,"pocketsphinx.lib")
#pragma comment(lib,"sphinxbase.lib")


#define MODELDIR "C:/Users/AvadaCedavra/Desktop/SpeechRec/test/Debug/model/zero_ru_cont_8k_v3"

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <sys/select.h>
#endif

//#include <sphinxbase/err.h>
//#include <sphinxbase/ad.h>
//
//#include "pocketsphinx.h"
//
//static ps_decoder_t *ps;
//static cmd_ln_t *config;
//
//static int
//check_wav_header(char *header, int expected_sr)
//{
//	int sr;
//
//	if (header[34] != 0x10) {
//		E_ERROR("Input audio file has [%d] bits per sample instead of 16\n", header[34]);
//		return 0;
//	}
//	if (header[20] != 0x1) {
//		E_ERROR("Input audio file has compression [%d] and not required PCM\n", header[20]);
//		return 0;
//	}
//	if (header[22] != 0x1) {
//		E_ERROR("Input audio file has [%d] channels, expected single channel mono\n", header[22]);
//		return 0;
//	}
//	sr = ((header[24] & 0xFF) | ((header[25] & 0xFF) << 8) | ((header[26] & 0xFF) << 16) | ((header[27] & 0xFF) << 24));
//	if (sr != expected_sr) {
//		E_ERROR("Input audio file has sample rate [%d], but decoder expects [%d]\n", sr, expected_sr);
//		return 0;
//	}
//	return 1;
//}
//
///*
//* Continuous recognition from a file
//*/
//static void recognize_from_file() {	
//	int16 adbuf[2048];
//	const char *hyp;
//	int32 k;
//	uint8 utt_started, in_speech; 
//	
//	std::string inName = "decoder-test.wav";
//	std::string outName = "out.dat";
//
//	std::ofstream out(outName.c_str(), std::ios::binary | std::ios::ate);
//	std::ifstream in(inName.c_str(), std::ios::binary);
//
//	char waveheader[44];
//	in.read(waveheader, 44);
//	if (!check_wav_header(waveheader, (int)cmd_ln_float32_r(config, "-samprate"))) {
//		std::cout << "Failed to process file" << inName << "due to format mismatch.\n";
//		return;
//	}
//
//	if (inName.find(".mp3") != -1) {
//		std::cout << "Can not decode mp3 files, convert input file to WAV 8kHz 16 - bit mono before decoding.\n";
//		return;
//	}
//
//	ps_start_utt(ps);
//	utt_started = FALSE;
//
//	while (!in.eof()) {
//		in.read(reinterpret_cast<char *>(&adbuf), sizeof(int16)*2048);
//		std::cout << in.gcount() << std::endl;
//		ps_process_raw(ps, adbuf, in.gcount()/2, FALSE, FALSE);
//		in_speech = ps_get_in_speech(ps);
//		if (in_speech && !utt_started) {
//			utt_started = TRUE;
//		}
//		if (!in_speech && utt_started) {
//			ps_end_utt(ps);
//			hyp = ps_get_hyp(ps, NULL);
//			if (hyp != NULL) {
//				out << hyp;
//			}
//			fflush(stdout);
//
//			ps_start_utt(ps);
//			utt_started = FALSE;
//		}
//	}
//
//	ps_end_utt(ps);
//	if (utt_started) {
//		hyp = ps_get_hyp(ps, NULL);
//		if (hyp != NULL) {
//			out << hyp;
//			out << '\n';
//		}
//	}
//
//	in.close();
//	out.close();
//}

int main(int argc, char *argv[])
{
	Recognizer rec;
	rec.recognize_from_file();
	//~Recognizer();
	/*char const *cfg;

	config = cmd_ln_init(NULL, ps_args(), TRUE,
		"-hmm", MODELDIR "/zero_ru.cd_cont_4000",
		"-lm", MODELDIR "/ru.lm",
		"-dict", MODELDIR "/ru.dic",
		"-remove_noise", "no",
		"-samprate", "8000",
		NULL);

	ps_default_search_args(config);
	ps = ps_init(config);
	if (ps == NULL) {
		cmd_ln_free_r(config);
		return 1;
	}

	recognize_from_file();
	ps_free(ps);
	cmd_ln_free_r(config);*/

	system("pause");
	return 0;
}
