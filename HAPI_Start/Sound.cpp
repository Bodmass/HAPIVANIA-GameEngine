#include "Sound.h"

std::unordered_map<std::string, std::string> Sound::SoundEffects;
int Sound::sound_Index = 0;
std::unordered_map<std::string, std::pair<std::string, int>> Sound::Music;
int Sound::music_Index = 0;
const HAPISPACE::HAPI_TSoundOptions Sound::soundOptions = HAPISPACE::HAPI_TSoundOptions(0.55f, false);
const HAPISPACE::HAPI_TSoundOptions Sound::musicOptions = HAPISPACE::HAPI_TSoundOptions(0.25f, false);

Sound::Sound()
{

}


Sound::~Sound()
{
}

void Sound::addSound(std::string sName, std::string sFile)
{
	//Load a sound into the Map, return an error if it can't be found.
	SoundEffects[sName] = sFile;
	if (!HAPI.LoadSound(sFile))
		std::cout << sFile << " had an error loading...\n";
	sound_Index+=1;

}

void Sound::addMusic(std::string mName, std::string mFile)
{
	//Insert the track passed through into the Music Map.
	Music.insert({ mName, std::make_pair(mFile, music_Index) });
}

void Sound::playSound(std::string sName)
{
	//Play the sound passed through with the options set for Sound.
	HAPI.PlaySound(getSound(sName), soundOptions);
}

void Sound::playMusic(std::string mName)
{
	//Play the Music passed through with the options set for Music.
	//and get the Instance ID of the sound.
	int instanceid = 0;
	HAPI.PlaySound(getMusic(mName), musicOptions, instanceid);
	getMusicID(mName, instanceid);
}

void Sound::stopSound(std::string sName)
{
	//Disabled
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
	//Stop the Music with the Given Name.
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
	//Pass through the name of the sound to recieve it's FileName.
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
	//Pass through the name of the music to recieve it's FileName.
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
	//Return the Instance ID of the specified music.
	for (auto bgm : Music)
	{
		if (bgm.first == mName)
		{
			Music[mName] = std::make_pair(bgm.second.first, id);
			return id;
		}
	}
	return 0;
}
