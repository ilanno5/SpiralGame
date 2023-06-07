#include "Wall.h"

void recWall::Draw()
{	
	DrawRectangle(_pos.x , _pos.y, _width, _height, _c);
}


