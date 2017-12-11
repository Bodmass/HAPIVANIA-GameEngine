#include "Sound.h"

std::unordered_map<std::string, std::string> Sound::SoundEffects;
int Sound::sound_Index = 0;
std::unordered_map<std::string, std::pair<std::string, int>> Sound::Music;
int Sound::music_Index = 0;
const HAPISPACE::HAPI_TSoundOptions Sound::soundOptions = HAPISPACE::HAPI_TSoundOptions(0.85f, false);
const HAPISPACE::HAPI_TSoundOptions Sound::musicOptions = HAPISPACE::HAPI_TSoundOptions(0.55f, false);

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

	//music_Index+=1;
}

void Sound::playSound(std::string sName)
{
	HAPI.PlaySound(getSound(sName), soundOptions);
}

void Sound::playMusic(std::string mName)
{
	int instanceid = 0;
	HAPI.PlaySound(getMusic(mName), musicOptions, instanceid);
	getMusicID(mName, instanceid);
}

void Sound::stopSound(std::string sName)
{
	for (auto se : SoundEffects)
	{
		if (se.first == sName)
		{
			return;
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
			HAPI.StopSound(bgm.second.second);
			return;
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
	return "";
}

std::string Sound::getMusic(std::string mName)
{
	for (auto bgm : Music)
	{
		if (bgm.first == mName)
		{
			return bgm.second.first;
		}
	}
	return "";
}

int Sound::getMusicID(std::string mName, int id)
{
	for (auto bgm : Music)
	{
		if (bgm.first == mName)
		{
			//std::string mFile = bgm.second.first
			Music[mName] = std::make_pair(bgm.second.first, id);
			return id;
		}
	}
	return 0;
}
