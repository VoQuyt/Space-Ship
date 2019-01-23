#pragma once
#include "Entity.h"
class Rocket:public Entity
{
public:
	Rocket();
	~Rocket();
	void settings(Animation &a, float oldX, float oldY, float Angle, int species);
	void update();
	void draw(RenderWindow &window);
};

