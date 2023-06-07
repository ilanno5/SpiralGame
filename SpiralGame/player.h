#pragma once
#include "Entity.h"

class Player: public Entity{
public:
	Player() {}
	Player(Vector2 pos, float speed) { _pos = pos, _speed = speed; }
	~Player() {}
	float getSpeed() { return _speed; }
	Vector2 getPos() { return _pos; }
	float getRadius() { return _radius; }
	void setSpeed(float s) { _speed = s; }
	void setPos(Vector2 pos) { _pos = pos; }
	void setRadius(float r) { _radius = r; }
private:
	Vector2 _pos;
	float _speed;
	float _radius;
};

//static Player player;
