#pragma once
#include "Entity.h"
class Bullet:public Entity
{
public:

	Bullet();
	~Bullet();
	void settings(Animation &a, float oldX, float oldY, float Angle,int species);
	void update();
	void draw(RenderWindow &window);
};

