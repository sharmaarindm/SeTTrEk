/*
PROJECT NAME : SETTrek
FILE NAME	: sound.h
DESCRIPTION : the purpose of this file is to model a all the sounds that will be played in our game.
DATE : 2017-04-11
NAME OF THE PROGRAMMER : ARINDM SHARMA
*/
#pragma once
#include <windows.h>
#include <xaudio2.h>
#include "wave.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <chrono>

/*
Name : sound
Purpose : this class acts as the model for a sound object.
*/
class sound
{
private:
	IXAudio2* g_engine;
	IXAudio2SourceVoice* g_source; //pin to which sound buffers can feed into
	IXAudio2MasteringVoice* g_master; //conclusion of all audio processing streams
	//helper class to load wave files; trust me, this makes it MUCH easier
	Wave buffer;
public:
	//constructor
	sound();
	~sound();
	//desctructor

	
	int collisonSound(); //sound the collision sound
	int backgroundSoundStart(); //sounds the background sound
	int backgroundSoundPlay(); //sounds the background sound
	int backgroundSoundStop(); //sounds the background sound
	int force(); // sounds the sound on gameover.
	void releases(); //for the cleanup after sound is played.

};