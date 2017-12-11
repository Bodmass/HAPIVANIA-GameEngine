#include "Sound.h"



Sound::Sound()
{
}


Sound::~Sound()
{
}

void Sound::addSound(std::string sName, std::string sFile)
{
	SoundEffects.insert({ sName, std::make_pair(sFile, sound_Index)});
	sound_Index++;
}

void Sound::addMusic(std::string mName, std::string mFile)
{
	Music.insert({ mName, std::make_pair(mFile, sound_Index) });
	music_Index++;
}

void Sound::playSound(std::string sName)
{
	for (auto se : SoundEffects)
	{
		if (se.first == sName)
		{
			HAPI.PlaySound(se.second.first);
		}
	}
}

void Sound::playMusic(std::string mName)
{
	for (auto bgm : Music)
	{
		if (bgm.first == mName)
		{
			HAPI.PlayStreamedMedia(bgm.second.first);
		}
	}
}

void Sound::stopSound(std::string sName)
{
	for (auto se : SoundEffects)
	{
		if (se.first == sName)
		{
			HAPI.StopSound(se.second.second);
		}
	}
}

void Sound::stopMusic(std::string mName)
{
	for (auto bgm : Music)
	{
		if (bgm.first == mName)
		{
			HAPI.StopStreamedMedia(bgm.second.second);
		}
	}
}
