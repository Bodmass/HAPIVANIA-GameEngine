#include <HAPI_lib.h>
#include <string>

using namespace HAPISPACE;

class textures
{
private:
	int t_Width, t_Height;
	std::string tName;
	BYTE* t_sprite{nullptr};
	bool hasAlpha{ true };
	bool isPlayer_{ false };
	int t_X = 1;
	int t_Y = 1;
public:
	textures() {};
	/*textures(const textures& other);*/
	textures(std::string filename);
	~textures();
	BYTE* getSprite();
	bool getAlpha() { return hasAlpha; };
	int getWidth() { return t_Width; };
	int getHeight() { return t_Height; };
	bool checkPlayer() { return isPlayer_; };
	int &getPosX() { return t_X; };
	int &getPosY() { return t_Y; };
};

