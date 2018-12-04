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

int main(int argc, char *argv[])
{
	Recognizer rec;
	rec.recognize_from_file();
	~Recognizer();

	system("pause");
	return 0;
}
