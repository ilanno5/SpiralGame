#include "Player.h"
#include "Spiral.h"
#include<cmath>
#include "Level.h"
#include "Setting.h"
#define PI 3.14159265358979323846f
#define DEG2RAD (PI/180.0f)
#define BASESPEED PI/1000
#define RIGHTSIDE true 
#define LEFTSIDE false
//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------

//static std::vector<Spiral> vecSpiral;
//static Player player;
static Level* level;
static float fadeLevel = 1.0f;
EndLevel endLevel;
static int currentLevel = 1;
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UpdateDrawFrame(void);  // Update and Draw (one frame)


int main(void)
{
    
	InitWindow(setting::screenWidth, setting::screenHeight, "Spiral Game");
    level = new Level1();
	InitGame();
    SetTargetFPS(60);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
    CloseWindow();        // Close window and OpenGL context

    return 0;
}



void InitGame() {

    level->init();
    int k = 1;

}
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

float dist(float x1, float y1, float x2, float y2) {
    return sqrt((y2 - y1)* (y2 - y1) + (x2 - x1)*(x2-x1));
}

bool pointCircle(float px, float py, float cx, float cy, float r) {

    float distX = px - cx;
    float distY = py - cy;
    float distance = sqrt((distX * distX) + (distY * distY));
    if (distance <= r) {
        return true;
    }
    return false;
}
bool linePoint(float x1, float y1, float x2, float y2, float px, float py) {


    float d1 = dist(px, py, x1, y1);
    float d2 = dist(px, py, x2, y2);


    float lineLen = dist(x1, y1, x2, y2);
    float buffer = 0.2;    

    if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer) {
        return true;
    }
    return false;
}

//bool checkCollisionRecCircle(Vector2 center, float radius, Rectangle rec) {
//    bool collision = false;
//
//
//
//    int recCenterX = (int)(rec.x + rec.width / 2.0f);
//    int recCenterY = (int)(rec.y + rec.height / 2.0f);
//
//    float dx = fabsf(center.x - (float)recCenterX);
//    float dy = fabsf(center.y - (float)recCenterY);
//
//    if (dx > (rec.width / 2.0f + radius)) { return false; }
//    if (dy > (rec.height / 2.0f + radius)) { return false; }
//
//    if (dx <= (rec.width / 2.0f)) { return true; }
//    if (dy <= (rec.height / 2.0f)) { return true; }
//
//    
//
//
//    float cornerDistanceSq = (dx - rec.width / 2.0f) * (dx - rec.width / 2.0f) +
//        (dy - rec.height / 2.0f) * (dy - rec.height / 2.0f);
//
//    collision = (cornerDistanceSq <= (radius * radius));
//
//    return collision;
//}


void UpdateGame(void)
{
    
    std::string direction = "";
    for (int i = 0; i < level->getVecSpiral().size(); i++) {
        for (Line* line : level->getVecSpiral()[i].getLines()) {
            if(level->getVecSpiral()[i].iSRight())
                line->setAngle(line->getAngle() + level->getVecSpiral()[i].getSpeed());
            else
                line->setAngle(line->getAngle() - level->getVecSpiral()[i].getSpeed());
            float x = line->getPos1().x + line->getLength() * cos(line->getAngle());
            float y = line->getPos1().y + line->getLength() * sin(line->getAngle());
            line->setPos2({x,y});

        }
    }
    if (IsKeyDown(KEY_LEFT)) {
        level->getPlayer()->setPos({ level->getPlayer()->getPos().x - level->getPlayer()->getSpeed(),level->getPlayer()->getPos().y });
        if (level->getPlayer()->getPos().x - level->getPlayer()->getRadius() <= 0) level->getPlayer()->setPos({ level->getPlayer()->getRadius(),level->getPlayer()->getPos().y});
        direction = "left";
    }
    if (IsKeyDown(KEY_RIGHT)) {
        level->getPlayer()->setPos({ level->getPlayer()->getPos().x + level->getPlayer()->getSpeed(),level->getPlayer()->getPos().y });
        if (level->getPlayer()->getPos().x + level->getPlayer()->getRadius() >= setting::screenWidth) level->getPlayer()->setPos({ setting::screenWidth - level->getPlayer()->getRadius(),level->getPlayer()->getPos().y });
        direction = "right";
    }
    if (IsKeyDown(KEY_DOWN)) {
        level->getPlayer()->setPos({ level->getPlayer()->getPos().x ,level->getPlayer()->getPos().y + level->getPlayer()->getSpeed() });
        if (level->getPlayer()->getPos().y + level->getPlayer()->getRadius() >= setting::screenHeight) level->getPlayer()->setPos({ level->getPlayer()->getPos().x, setting::screenHeight - level->getPlayer()->getRadius() });
        direction = "down";
    }
    if (IsKeyDown(KEY_UP)) {
        level->getPlayer()->setPos({ level->getPlayer()->getPos().x ,level->getPlayer()->getPos().y - level->getPlayer()->getSpeed() });
        if (level->getPlayer()->getPos().y - level->getPlayer()->getRadius() <= 0) level->getPlayer()->setPos({ level->getPlayer()->getPos().x, level->getPlayer()->getRadius() });
        direction = "up";
    }
    //collision with Spiral
   for (int i = 0; i < level->getVecSpiral().size(); i++) {
        float buffer = 0.1;
        float px = level->getPlayer()->getPos().x;
        float py = level->getPlayer()->getPos().y;
        for (Line* line : level->getVecSpiral()[i].getLines()) {
            float x1 = line->getPos1().x;
            float y1 = line->getPos1().y;
            float x2 = line->getPos2().x;
            float y2 = line->getPos2().y;
            float r = level->getPlayer()->getRadius();
            bool inside1 = pointCircle(x1, y1, px, py, r);
            bool inside2 = pointCircle(x2, y2, px, py, r);
            if (inside1 || inside2) {
                InitGame();
                break;
            }
            else {
                float dot = (((px - x1) * (x2 - x1)) + ((py - y1) * (y2 - y1))) / pow(line->getLength(), 2);
                float closestX = x1 + (dot * (x2 - x1));
                float closestY = y1 + (dot * (y2 - y1));
                bool onSegment = linePoint(x1, y1, x2, y2, closestX, closestY);
                if (!onSegment)
                    continue;
                else {

                    float distX = closestX - px;
                    float distY = closestY - py;
                    float distance = sqrt((distX * distX) + (distY * distY));

                    if (distance <= r) {
                        InitGame();
                        break;
                    }
                }
            }




        }
    }

   //collision with Wall
   for (int i = 0; i < level->getWalls().size(); i++) {
       float px = level->getPlayer()->getPos().x;
       float py = level->getPlayer()->getPos().y;
       if (level->getWalls()[i]->getType() == "Recwall") {
           recWall* recwall = static_cast<recWall*>(level->getWalls()[i]);
           Rectangle rec = { recwall->getPos().x, recwall->getPos().y, recwall->getWidth(), recwall->getHeight() };
           if (CheckCollisionCircleRec({ px,py }, level->getPlayer()->getRadius(), rec)) {
               if (direction == "left") {
                   level->getPlayer()->setPos({ recwall->getPos().x + recwall->getWidth() + level->getPlayer()->getRadius() + 1,level->getPlayer()->getPos().y });
               }
               else if (direction == "right") {
                   level->getPlayer()->setPos({ recwall->getPos().x - level->getPlayer()->getRadius() - 1 ,level->getPlayer()->getPos().y}); //recwall->getPos().x - level->getPlayer()->getRadius()
               }
               else if (direction == "down") {
                   level->getPlayer()->setPos({ level->getPlayer()->getPos().x ,level->getPlayer()->getPos().y - level->getPlayer()->getSpeed() });

               }
               else if (direction == "up") {
                   level->getPlayer()->setPos({ level->getPlayer()->getPos().x ,level->getPlayer()->getPos().y + level->getPlayer()->getSpeed() });
               }
           }
       }
   }


    //finish Level
    if (level->getPlayer()->getPos().x - level->getPlayer()->getRadius() >= level->getEndLevel()._pos.x && level->getPlayer()->getPos().y - level->getPlayer()->getRadius() >= level->getEndLevel()._pos.y - level->getEndLevel()._size.y) {
        if (level->getType() == "level1") {
            currentLevel = 2;
            level = new Level2();
        }
        else if (level->getType() == "level2") {
            currentLevel = 3;
            level = new Level3();
        }



            fadeLevel = 1.0f;
            level->init();
        }
}



void DrawGame(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangleV(level->getEndLevel()._pos, level->getEndLevel()._size, YELLOW);
    
    if (fadeLevel > 0 && currentLevel == 1) {
        DrawText("LeveL 1", setting::screenWidth / 2 - MeasureText("LeveL 1", 40) , setting::screenHeight / 2 - 100, 80, Fade(BLACK, fadeLevel));
        fadeLevel -= 0.01;
    }
    if (fadeLevel > 0 && currentLevel == 2) {
        DrawText("LeveL 2", setting::screenWidth / 2 - MeasureText("LeveL 2", 40), setting::screenHeight / 2 - 100, 80, Fade(BLACK, fadeLevel));
        fadeLevel -= 0.01;
    }
    if (fadeLevel > 0 && currentLevel == 3) {
        DrawText("LeveL 2", setting::screenWidth / 2 - MeasureText("LeveL 3", 40), setting::screenHeight / 2 - 100, 80, Fade(BLACK, fadeLevel));
        fadeLevel -= 0.01;
    }
    for (int i = 0; i < level->getVecSpiral().size(); i++) {
        for (Line* line : level->getVecSpiral()[i].getLines()) {
            Vector2 vec1 = line->getPos1();
            Vector2 vec2 = line->getPos2();
            DrawLineEx(vec1, vec2,2, GREEN);
        }
    }
    DrawCircleV(level->getPlayer()->getPos(), level->getPlayer()->getRadius(), RED);
    for (int i = 0; i < level->getWalls().size(); i++) {
        level->getWalls()[i]->Draw();
    }
    //DrawLine(400, 90, 420, 90, BLUE);
 
    EndDrawing();
}

