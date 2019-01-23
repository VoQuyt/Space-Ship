#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <SFML/Audio.hpp>
using namespace sf;

#include <iostream>
using namespace std;


const int W = 1920;
const int H = 1080;

const float DEGTORAD = 0.017453f;

class Entity// thực thể
{
public:
	Animation anim;
	string name;
	float OldX, OldY, YoungX, YoungY, R, Angle;
	bool life;
	int Health, Blood;
	int R1_Ship, R2_Ship, R3_Ship;
	int R1_Bullet, R2_Bullet, R3_Bullet;
	int R1_Rocket, R2_Rocket, R3_Rocket;
	int R1_UFO, R2_UFO, R3_UFO, Species;
	float time_Ship, speed_Ship, frame_Ship, time_Tank, speed_Tank, frame_Tank, time_UFO, speed_UFO, frame_UFO;
	
	//////////////phương thức////////////////////////
	Entity();
	virtual void settings(Animation &a, float oldX, float oldY, float angle, int species);
	virtual void update() {};
	virtual void draw(RenderWindow &windown);
	virtual ~Entity() {};
};

