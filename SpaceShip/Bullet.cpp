#include "Bullet.h"



Bullet::Bullet()
{
	this->R = 25;
	this->name = "Bullet";
	this->life = 1;
	this->time_UFO = 2;
	this->frame_UFO = 0;
}


Bullet::~Bullet()
{
}

void Bullet::settings(Animation &a, float oldX, float oldY, float angle, int species)
{
	this->anim = a;
	this->OldX = oldX;
	this->OldY = oldY;
	this->Angle = angle;
	this->Species = species;

}
void Bullet::update()
{
	int v = 15;//tốc độ bay của đạn
	if (this->Species == 1)
		v = 20;
	YoungX = cos(Angle*DEGTORAD) * v;
	YoungY = sin(Angle*DEGTORAD) * v;
	OldX += YoungX;
	OldY += YoungY;
}
void Bullet::draw(RenderWindow &window)
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