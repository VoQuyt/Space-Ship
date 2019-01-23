#include "Entity.h"



Entity::Entity()
{
	this->life = 1;
}

void Entity::settings(Animation &a, float oldX, float oldY, float angle, int species) 
{
	this->anim = a;
	this->OldX = oldX;
	this->OldY = oldY;
	this->Angle = angle;
	this->Species = species;
}

void Entity::draw(RenderWindow &windown)
{
	anim.sprite.setPosition(OldX, OldY);
	anim.sprite.setRotation(Angle + 90);
	windown.draw(anim.sprite);

	CircleShape circle(R);
	circle.setFillColor(Color(255, 0, 0, 170));
	circle.setPosition(OldX, OldY);
	circle.setOrigin(R, R);
	//app.draw(circle);
}