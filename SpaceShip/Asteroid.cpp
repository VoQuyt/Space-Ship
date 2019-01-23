#include "Asteroid.h"



Asteroid::Asteroid()
{
	//this->dx = 0;
	//this->dy = 0;
	name = "asteroid";
	this->life = 1;
	this->Speed = rand() % 7 + 3;
	this->Blood = 5;
}
Asteroid::~Asteroid()
{}

void Asteroid::update()
{
	YoungX = cos(Angle*DEGTORAD) * Speed;
	YoungY = sin(Angle*DEGTORAD) * Speed;

	OldX += YoungX;
	OldY += YoungY;
}

void Asteroid::settings(Animation &a, float X, float Y, float Angle, float radius)
{
	this->anim = a;
	this->OldX = X; this->OldY = Y;
	this->Angle = Angle;
	this->R = radius;
}

void Asteroid::draw(RenderWindow &window)
{
	anim.sprite.setPosition(OldX, OldY);
	anim.sprite.setRotation(Angle + 90);
	window.draw(anim.sprite);

	CircleShape circle(R);
	circle.setFillColor(Color(255, 0, 0, 170));
	circle.setPosition(OldX, OldY);
	circle.setOrigin(R, R);

	///*CircleShape circleAI(AI);
	//circleAI.setFillColor(Color(255, 0, 0, 170));
	//circleAI.setPosition(x, y);
	//circleAI.setOrigin(AI, AI);*/
	//window.draw(circleAI);//cmt here///////////////////////////////////
}