#pragma once
#include <unordered_map>
#include <HAPI_lib.h>
#include <HAPI_Types.h>
class Sound
{
private:
	std::unordered_map<std::string, std::string> SoundEffects;
	int sound_Index = 0;
	std::unordered_map<std::string, std::pair<std::string, int>> Music;
	int music_Index = 0;
	const HAPISPACE::HAPI_TSoundOptions soundOptions = HAPISPACE::HAPI_TSoundOptions(0.85f, false);
	const HAPISPACE::HAPI_TSoundOptions musicOptions = HAPISPACE::HAPI_TSoundOptions(0.5f, true);
public:
	Sound();
	~Sound();
	void addSound(std::string sName, std::string sFile);
	void addMusic(std::string mName, std::string mFile);
	void playSound(std::string sName);
	void playMusic(std::string mName);
	void stopSound(std::string sName);
	void stopMusic(std::string mName);
	std::string getSound(std::string sName);
};

