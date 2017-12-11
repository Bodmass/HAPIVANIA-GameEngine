#include "Sound.h"

Sound::Sound()
{

}


Sound::~Sound()
{
}

void Sound::addSound(std::string sName, std::string sFile)
{
	SoundEffects[sName] = sFile;
	if (!HAPI.LoadSound(sFile))
		std::cout << sFile << " had an error loading...\n";
	sound_Index+=1;
}

void Sound::addMusic(std::string mName, std::string mFile)
{
	Music.insert({ mName, std::make_pair(mFile, music_Index) });

	music_Index+=1;
}

void Sound::playSound(std::string sName)
{
	for (auto se : SoundEffects)
	{
		if (se.first == sName)
		{
			HAPI.PlayStreamedMedia(se.second);
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
			//HAPI.StopStreamedMedia(se.second);
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

std::string Sound::getSound(std::string sName)
{
	for (auto se : SoundEffects)
	{
		if (se.first == sName)
		{
			return se.second;
		}
	}
}
