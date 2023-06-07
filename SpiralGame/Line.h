#pragma once
#include "raylib.h"
class Line
{
public:
	Line() {}
	Line(Vector2 pos1, Vector2 pos2, int length) { _pos1 = pos1, _pos2 = pos2, _length = length; }
	~Line() {}
	void setPos1(Vector2 p1) { _pos1 = p1; }
	void setPos2(Vector2 p2) { _pos2 = p2; }
	void setLength(int l) { _length = l; }
	Vector2 getPos1() {return  _pos1 ; }
	Vector2 getPos2() { return _pos2 ; }
	int getLength() { return _length; }
	float getAngle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }
private:
	Vector2 _pos1;
	Vector2 _pos2;
	int _length;
	float _angle;
};

