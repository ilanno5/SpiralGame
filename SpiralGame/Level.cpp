#include "Level.h"
#include "Player.h"
#include "Setting.h"
#include "Wall.h"
#define BASESPEED PI/1000
#define RIGHTSIDE true 
#define LEFTSIDE false

std::vector<Line*> crateLines(Vector2 pos, int numberOfLines, int length) {

    std::vector<Line*> vecLine;
    float angle = 0;
    float angleToAdd = 360 / numberOfLines;
    for (int i = 0; i < numberOfLines; i++) {
        float x = pos.x + length * cos(angle * DEG2RAD);
        float y = pos.y + length * sin(angle * DEG2RAD);
        Line* l = new Line(pos, { x,y }, length);
        l->setAngle(angle * DEG2RAD);
        vecLine.push_back(l);
        angle += angleToAdd;
    }
    return vecLine;
}



void Level1::init()
{
    
    
    //first spiral
    vecSpiral.clear();
    Vector2 posS1 = { 100,200 };
    Spiral s1(posS1, 5 * BASESPEED);
    s1.setLines(crateLines(posS1, 10, 100));
    s1.setDirection(RIGHTSIDE);
    vecSpiral.push_back(s1);


    //second spiral
    Vector2 posS2 = { 300,200 };
    Spiral s2(posS1, 5 * BASESPEED);
    s2.setLines(crateLines(posS2, 10, 100));
    s2.setDirection(LEFTSIDE);
    vecSpiral.push_back(s2);

    //third spiral
    Vector2 posS3 = { 500,200 };
    Spiral s3(posS3, 5 * BASESPEED);
    s3.setLines(crateLines(posS3, 10, 100));
    s3.setDirection(RIGHTSIDE);
    vecSpiral.push_back(s3);

    //fourth spiral
    Vector2 posS4 = { 700,200 };
    Spiral s4(posS4, 5 * BASESPEED);
    s4.setLines(crateLines(posS4, 10, 100));
    s4.setDirection(LEFTSIDE);
    vecSpiral.push_back(s4);

    //Player
    
    player->setRadius(10);
    player->setPos({ player->getRadius(), player->getRadius() });
    player->setSpeed(5);

    //Endlevel
    endlevel._pos = { setting::screenWidth - player->getRadius() * 2 - 5, setting::screenHeight - player->getRadius() * 2 -5};
    endlevel._size = { player->getRadius() * 2 + 5 , player->getRadius() * 2 +5 };

    //walls

    recWall* w1 = new recWall({ setting::screenWidth / 2,0 }, 5, setting::screenHeight / 5 , BROWN);
    wallsVec.push_back(w1);
}
void Level2::init()
{

    //first spiral
    vecSpiral.clear();
    Vector2 posS1 = { 100,200 };
    Spiral s1(posS1, 5 * BASESPEED);
    s1.setLines(crateLines(posS1, 10, 100));
    s1.setDirection(RIGHTSIDE);
    vecSpiral.push_back(s1);


    //second spiral
    Vector2 posS2 = { 300,200 };
    Spiral s2(posS1, 5 * BASESPEED);
    s2.setLines(crateLines(posS2, 10, 100));
    s2.setDirection(LEFTSIDE);
    vecSpiral.push_back(s2);

    //third spiral
    Vector2 posS3 = { 500,200 };
    Spiral s3(posS3, 5 * BASESPEED);
    s3.setLines(crateLines(posS3, 10, 100));
    s3.setDirection(RIGHTSIDE);
    vecSpiral.push_back(s3);

    //fourth spiral
    Vector2 posS4 = { 700,200 };
    Spiral s4(posS4, 5 * BASESPEED);
    s4.setLines(crateLines(posS4, 10, 100));
    s4.setDirection(LEFTSIDE);
    vecSpiral.push_back(s4);

    //Player

    player->setRadius(10.0);
    float r = player->getRadius();
    player->setPos({ r  , r });
    player->setSpeed(5);

    //Endlevel
    endlevel._pos = { setting::screenWidth - player->getRadius() * 2 - 5, setting::screenHeight - player->getRadius() * 2 - 5 };
    endlevel._size = { player->getRadius() * 2 + 5 , player->getRadius() * 2 + 5 };

    //walls

    recWall* w1 = new recWall({ 200,0 }, 2, setting::screenHeight / 2, BROWN);
    wallsVec.push_back(w1);
    recWall* w2 = new recWall({ 400,setting::screenHeight / 2 }, 2, setting::screenHeight / 2, BROWN);
    wallsVec.push_back(w2);
    recWall* w3 = new recWall({ 600,0 }, 2, setting::screenHeight / 2, BROWN);
    wallsVec.push_back(w3);

}

void Level3::init() {

    //first spiral
    vecSpiral.clear();
    Vector2 posS1 = { 200,200 };
    Spiral s1(posS1, 5 * BASESPEED);
    s1.setLines(crateLines(posS1, 10, 200));
    s1.setDirection(RIGHTSIDE);
    vecSpiral.push_back(s1);


    //second spiral
    Vector2 posS2 = { 600,200 };
    Spiral s2(posS1, 6 * BASESPEED);
    s2.setLines(crateLines(posS2, 10, 200));
    s2.setDirection(LEFTSIDE);
    vecSpiral.push_back(s2);

    //Player

    player->setRadius(10.0);
    float r = player->getRadius();
    player->setPos({ r  , r });
    player->setSpeed(5);

    //Endlevel
    endlevel._pos = { setting::screenWidth - player->getRadius() * 2 - 5, setting::screenHeight - player->getRadius() * 2 - 5 };
    endlevel._size = { player->getRadius() * 2 + 5 , player->getRadius() * 2 + 5 };

    //walls

    recWall* w1 = new recWall({ 200,setting::screenHeight / 10 * 9 }, 2, setting::screenHeight / 10, BROWN);
    wallsVec.push_back(w1);
    recWall* w2 = new recWall({ 600,setting::screenHeight / 10*9 }, 2, setting::screenHeight / 10, BROWN);
    wallsVec.push_back(w2);

}
