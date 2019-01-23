#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"


class Asteroid : public Entity //thực thể hành tinh
{
public:
	int Speed;
	Asteroid();//sinh tạo độ thiên thạch ngẩu nhiên
	~Asteroid();
	void settings(Animation &a, float X, float Y, float Angle, float radius);
	void  update();
	void draw(RenderWindow &window);
};

