#pragma once
class Rectangle
{
private:
	//Rectangle Values
	int rTop{ 0 }, rBtm{ 0 }, rLeft{ 0 }, rRight{ 0 };
	int rWidth{ 0 }, rHeight{ 0 };
	int rPosX{ 0 }, rPosY{ 0 };
	
public:
	Rectangle()=default;
	Rectangle(int l, int r, int t, int b) : rLeft(l), rRight(r), rTop(t), rBtm(b) {}
	Rectangle(int w, int h) : rLeft(0), rRight(w), rTop(0), rBtm(h) {}

	//Getters
	int getTop() const { return rTop; };
	int getBtm() const { return rBtm; };
	int getLeft() const { return rLeft; };
	int getRight() const { return rRight; };

	int getWidth() const { return  rRight - rLeft; };
	int getHeight() const { return rBtm - rTop; };

	int getX() const { return rPosX; }
	int getY() const { return rPosY; }

	//Setters
	void setTop(int val) { rTop = val; };
	void setBtm(int val) { rBtm = val; };
	void setLeft(int val) { rLeft = val; };
	void setRight(int val) { rRight = val; };

	//Functions
	void Translate(int x, int y); //moves the rectangle clip
	void Move(int x, int y);
	int Clamp(int number, int lowest, int highest); 
	Rectangle rContains(Rectangle &rect);


};
