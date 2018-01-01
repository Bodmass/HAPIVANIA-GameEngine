#pragma once
#include <unordered_map>
#include <HAPI_lib.h>
#include <HAPI_Types.h>
class Sound
{
	/*
	Sound is a Static Class so it be called by any function that requires Sound to be played.
	*/
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
	//Adds a Sound to the Sound Unordered Map using a String which its called by and the File Location.
	static void addMusic(std::string mName, std::string mFile);
	//Adds a Music to the Music Unordered Map using a String which its called by and the File Location.
	static void playSound(std::string sName);
	//Plays a sound with their given string
	static void playMusic(std::string mName);
	//Plays music with its given string.
	static void stopSound(std::string sName);
	//Stops the current sound being played
	static void stopMusic(std::string mName);
	//Stops the current music being played
	static std::string getSound(std::string sName);
	//Gets the sound at the given string
	static std::string getMusic(std::string mName);
	//Gets the music at the given string
	static int getMusicID(std::string mName, int id);
	//Returns the instance ID of the specified music.
};

