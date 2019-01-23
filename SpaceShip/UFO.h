#pragma once
#include "Entity.h"
class UFO:public Entity
{
public:
	UFO();
	~UFO();
	void settings(Animation &a, float oldX, float oldY, float radius,float R2, float Angle, int speces, int blood);
	void update();
	void draw(RenderWindow &window);
};

