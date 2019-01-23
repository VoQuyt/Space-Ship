#include "Rocket.h"



Rocket::Rocket()
{
	this->R = 30;
	this->name = "Rocket";
	this->life = 1;
	this->R1_Rocket = 1000;
	this->R2_Rocket = 1000;
	this->Blood = 2;
}


Rocket::~Rocket()
{
}

void Rocket::settings(Animation &a, float oldX, float oldY, float Angle, int species)
{
	this->anim = a;
	this->OldX = oldX;
	this->OldY = oldY;
	this->Angle = Angle;
	this->Species = species;
}
void Rocket::update()
{
	int v = 13;//tốc độ bay của đạn
	if (this->Species == 1)
		v = 15;
	YoungX = cos(Angle*DEGTORAD) * v;
	YoungY = sin(Angle*DEGTORAD) * v;
	OldX += YoungX;
	OldY += YoungY;
}
void Rocket::draw(RenderWindow &window)
{
	anim.sprite.setPosition(OldX, OldY);
	anim.sprite.setRotation(Angle + 90);
	window.draw(anim.sprite);

	CircleShape circle(R);
	circle.setFillColor(Color(255, 0, 0, 170));
	circle.setPosition(OldX, OldY);
	circle.setOrigin(R, R);

	CircleShape circle1(this->R1_Rocket);
	circle1.setFillColor(Color(255, 0, 0, 170));
	circle1.setPosition(OldX, OldY);
	circle1.setOrigin(R1_Rocket, R1_Rocket);

	CircleShape circle2(this->R2_Rocket);
	circle2.setFillColor(Color(255, 0, 0, 170));
	circle2.setPosition(OldX, OldY);
	circle2.setOrigin(R2_Rocket, R2_Rocket);
	//window.draw(circle);//cmt here///////////////////////////////////
}