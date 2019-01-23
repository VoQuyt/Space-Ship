#include "Tank.h"



Tank::Tank()
{
	this->name = "Tank";
	this->life = 1;
	this->R = 80;
	this->Blood = 4;
	this->Angle = 90;
	this->time_Tank = 3;
	this->speed_Tank = 0;
	this->frame_Tank = 5;
}


Tank::~Tank()
{
}

void Tank::settings(Animation &a, float oldX, float oldY, float angle, int species)
{
	this->anim = a;
	this->OldX = oldX;
	this->OldY = oldY;
	this->Angle = angle;
	this->Species = species;
}
void Tank::update()
{

}

void Tank::draw(RenderWindow &window)
{
	anim.sprite.setPosition(OldX, OldY);
	anim.sprite.setRotation(Angle + 90);
	window.draw(anim.sprite);

	CircleShape circle(R);
	circle.setFillColor(Color(255, 0, 0, 170));
	circle.setPosition(OldX, OldY);
	circle.setOrigin(R, R);
	//window.draw(circle);//cmt here///////////////////////////////////
}
