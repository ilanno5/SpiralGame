#pragma once
#include "Spiral.h"
#include "Player.h"
#include "Wall.h"
struct EndLevel
{
	Vector2 _pos;
	Vector2 _size;
};


class Level
{
public:
	Level() {}
	~Level() {
		for (auto w: wallsVec) {
			delete w;
		}
	}
	virtual void init() = 0;
	virtual std::string getType() = 0;
	std::vector<Spiral> getVecSpiral() { return vecSpiral; }
	Player* getPlayer() { return player; }
	EndLevel getEndLevel() { return endlevel; }
	std::vector<Wall*> getWalls() { return wallsVec; }
protected:
	std::vector<Spiral> vecSpiral;
	Player* player = new Player();
	EndLevel endlevel;
	std::vector<Wall*> wallsVec;
};

class Level1 : public Level {
public:
	Level1() {}
	~Level1() {}
	void init();
	std::string getType() { return "level1"; }
};

class Level2 : public Level {
public:
	Level2() {}
	~Level2() {}
	void init();
	std::string getType() { return "level2"; }
};

class Level3 : public Level {
public:
	Level3() {}
	~Level3() {}
	void init();
	std::string getType() { return "level3"; }
};