#pragma once
#include "raylib.h"
#include <string>

class Wall
{
public:
	Wall() {}
	~Wall() {};
	virtual void Draw() {}
	virtual std::string getType() { return "bla"; }
};


class recWall :public Wall {
public:
	recWall() {}
	recWall(Vector2 pos, int width, int height, Color c) { _pos = pos, _width = width, _height = height, _c = c ; }
	~recWall() {}
	Vector2 getPos() { return _pos; }
	int getWidth() { return _width; }
	int getHeight() { return _height; }
	void Draw() override ;
	std::string getType() { return "Recwall"; }
private:
	Color _c;
	Vector2 _pos;
	int _width;
	int _height;
};
