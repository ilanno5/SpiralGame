#pragma once
#include "Entity.h"
#include "Line.h"
class Spiral: public Entity 
{
public:
	Spiral() {}
	~Spiral() {}
	Spiral(Vector2 pos, float speed) { _pos = pos, _speed = speed; }
	Spiral(Vector2 pos, float speed, std::vector<Line*> numOfLines) { _pos = pos, _speed = speed, _numOfLines = numOfLines; }
	void setPos(Vector2 p) { _pos = p;}
	void setSpeed(float s) { _speed = s; }
	void setLines(std::vector<Line*> arms) { _numOfLines = arms; }
	std::vector<Line*> getLines() { return _numOfLines; }
	float getSpeed() { return _speed; }
	void setDirection(bool dir) { _direction = dir; }
	bool iSRight() { return _direction; }
private:
	Vector2 _pos;
	std::vector<Line*> _numOfLines;
	float _speed;
	bool _direction;
};

//static std::vector<Spiral> vecSpiral;
