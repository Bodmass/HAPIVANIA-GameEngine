#pragma once
#include <unordered_map>
#include <HAPI_lib.h>
#include <HAPI_Types.h>
class Sound
{
private:
	static std::unordered_map<std::string, std::string> SoundEffects;
	static int sound_Index;
	static std::unordered_map<std::string, std::pair<std::string, int>> Music;
	static int music_Index;
	static const HAPISPACE::HAPI_TSoundOptions soundOptions;
	static const HAPISPACE::HAPI_TSoundOptions musicOptions;
public:
	Sound();
	~Sound();
	static void addSound(std::string sName, std::string sFile);
	static void addMusic(std::string mName, std::string mFile);
	static void playSound(std::string sName);
	static void playMusic(std::string mName);
	static void stopSound(std::string sName);
	static void stopMusic(std::string mName);
	static std::string getSound(std::string sName);
	static std::string getMusic(std::string mName);
	static int getMusicID(std::string mName, int id);
};

