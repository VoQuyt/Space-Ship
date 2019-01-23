#pragma once
#include "Entity.h"
class Stern:public Entity
{
public:

	void settings(Animation &a, float oldX, float oldY, float Angle, int species);
	void update();
	void draw(RenderWindow &window);
	Stern();
	~Stern();
};

