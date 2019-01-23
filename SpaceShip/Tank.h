#pragma once
#include "Entity.h"

class Tank:public Entity
{
public:
	Tank();
	~Tank();
	void settings(Animation &a, float oldX, float oldY, float angle, int species);
	void update();
	void draw(RenderWindow &window);                                                                              
};

