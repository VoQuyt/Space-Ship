#include "Stern.h"


Stern::Stern()
{
	this->name = "Stern";
	this->R = 70;
	this->life = 1;
}


Stern::~Stern()
{
}


void Stern::settings(Animation &a, float oldX, float oldY, float angle, int species)
{
	this->anim = a;
	this->OldX = oldX;
	this->OldY = oldY;
	this->Angle = angle;
	this->Species = species;
}
void Stern::update()
{
	if (this->Species == 0)
		OldY += 4;
	if(this->Species == 1)
		OldY += 8;
	if (this->Species == 2)
		OldY += 6;

}
void Stern::draw(RenderWindow &window)
{
	anim.sprite.setPosition(OldX, OldY);
	anim.sprite.setRotation(Angle + 90);
	window.draw(anim.sprite);

	CircleShape circle(R);
	circle.setFillColor(Color(255, 0, 0, 170));
	circle.setPosition(OldX, OldY);
	circle.setOrigin(R, R);
}