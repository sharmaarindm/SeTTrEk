#include "sound.h"

sound::sound()
{

}

sound::~sound()
{
}

int sound::collisonSound()
{

	//must call this for COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//create the engine
	if (FAILED(XAudio2Create(&g_engine)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
	{
		g_engine->Release();
		CoUninitialize();
		return -2;
	}

	//helper class to load wave files; trust me, this makes it MUCH easier
	Wave buffer;

	//load a wave file
	if (!buffer.load("explosive.wav"))
	{
		g_engine->Release();
		CoUninitialize();
		return -3;
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
	{
		g_engine->Release();
		CoUninitialize();
		return -4;
	}

	//start consuming audio in the source voice
	g_source->Start();

	auto starte = std::chrono::high_resolution_clock::now();
	long long microsecondse = 0;

	do 
	{
		//play the sound
		g_source->SubmitSourceBuffer(buffer.xaBuffer());
		auto elapsede = std::chrono::high_resolution_clock::now() - starte;
		 microsecondse = std::chrono::duration_cast<std::chrono::microseconds>(elapsede).count();
	} while (microsecondse < 2000000);



	//release the engine, NOT the voices!
	g_engine->Release();

	//again, for COM
	CoUninitialize();

	return 0;
}

int sound::backgroundSoundStart()
{

	//must call this for COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//create the engine
	if (FAILED(XAudio2Create(&g_engine)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
	{
		g_engine->Release();
		CoUninitialize();
		return -2;
	}



	//load a wave file
	if (!buffer.load("music.wav"))
	{
		g_engine->Release();
		CoUninitialize();
		return -3;
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
	{
		g_engine->Release();
		CoUninitialize();
		return -4;
	}

	//start consuming audio in the source voice
	g_source->Start();

	return 0;
}

int sound::backgroundSoundPlay()
{
    //play the sound
	g_source->SubmitSourceBuffer(buffer.xaBuffer());
	return 0;
}

int sound::backgroundSoundStop()
{
	//release the engine, NOT the voices!
	g_engine->Release();

	//again, for COM
	CoUninitialize();
	return 0;
}

int sound::force()
{
	//must call this for COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//create the engine
	if (FAILED(XAudio2Create(&g_engine)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
	{
		g_engine->Release();
		CoUninitialize();
		return -2;
	}

	//helper class to load wave files; trust me, this makes it MUCH easier
	Wave buffer;

	//load a wave file
	if (!buffer.load("force.wav"))
	{
		g_engine->Release();
		CoUninitialize();
		return -3;
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
	{
		g_engine->Release();
		CoUninitialize();
		return -4;
	}

	//start consuming audio in the source voice
	g_source->Start();

	auto starte = std::chrono::high_resolution_clock::now();
	long long microsecondse = 0;

	do
	{

		//play the sound
		g_source->SubmitSourceBuffer(buffer.xaBuffer());


		auto elapsede = std::chrono::high_resolution_clock::now() - starte;
		microsecondse = std::chrono::duration_cast<std::chrono::microseconds>(elapsede).count();
	} while (microsecondse < 4000000);



	//release the engine, NOT the voices!
	g_engine->Release();

	//again, for COM
	CoUninitialize();

	return 0;
}

void sound::releases()
{
	//release the engine, NOT the voices!
	g_engine->Release();

	//again, for COM
	CoUninitialize();

}
