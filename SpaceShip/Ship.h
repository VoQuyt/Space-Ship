#pragma once
#include "Entity.h"
#include "Stern.h"
class Ship:public Entity
{
public:
	bool thrust;
	void settings(Animation &a, float oldX, float oldY, float Angle);
	void update();
	void draw(RenderWindow &window);
	Ship();
	~Ship();
};

