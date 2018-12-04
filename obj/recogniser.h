#ifndef RECOGNISER_H
#define RECOGNISER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include "pocketsphinx.h"

#pragma comment(lib,"pocketsphinx.lib")
#pragma comment(lib,"sphinxbase.lib")

//заменить на путь до папки zero_ru_cont_8k_v3
#define MODELDIR "C:/Users/AvadaCedavra/Desktop/SpeechRec/test/Debug/model/zero_ru_cont_8k_v3"

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <sys/select.h>
#endif

class Recognizer {
private:
	ps_decoder_t *ps;
	cmd_ln_t *config;
	int check_wav_header(char *header, int expected_sr);
	std::string inName;
	std::string outName;
public:
	Recognizer() {
		config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", MODELDIR "/zero_ru.cd_cont_4000",
			"-lm", MODELDIR "/ru.lm",
			"-dict", MODELDIR "/ru.dic",
			"-remove_noise", "no",
			"-samprate", "8000",
			NULL);
		
		
		if (config == NULL) {
			std::cout << "Filed to init config" << std::endl;
			cmd_ln_free_r(config);
		}

		ps_default_search_args(config);
		ps = ps_init(config);
		
		if (ps == NULL) {
			std::cout << "Filed to init decoder" << std::endl;
			cmd_ln_free_r(config);
		}

		inName = "decoder-test.wav";
		outName = "out.dat";
	}
	~Recognizer() {
		ps_free(ps);
		cmd_ln_free_r(config);
	}

	void recognize_from_file(std::string inn = "", std::string outt = "");

};

#endif // !RECOGNISER_H
