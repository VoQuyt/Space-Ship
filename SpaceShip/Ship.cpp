#include "Ship.h"



Ship::Ship()
{
	this->name = "Ship";
	this->life = 1;
	this->Health = 3;
	this->Blood = 21;
	this->R = 20;
	this->R1_Ship = 400;//60
	this->R2_Ship = 600;
	this->R3_Ship = 1000;
	this->Angle = 90;
	this->frame_Ship = 0;
	this->time_Ship = 2;
}


Ship::~Ship()
{
}

void Ship::settings(Animation &a, float oldX, float oldY, float angle)
{
	this->anim = a;
	this->OldX = oldX;
	this->OldY = oldY;
	this->Angle = angle;
}
void Ship::update()
{
	if (thrust)
	{
		YoungX += cos(Angle*DEGTORAD)*0.2;
		YoungY += sin(Angle*DEGTORAD)*0.2;
	}
	else
	{
		YoungX *= 0.99;
		YoungY *= 0.99;
	}

	int maxSpeed = 15;
	float speed = sqrt(YoungX*YoungX + YoungY*YoungY);
	if (speed > maxSpeed)
	{
		YoungX *= maxSpeed / speed;
		YoungY *= maxSpeed / speed;
	}

	//xử lý va chạm với biên
	if (this->OldX <= 0)
	{
		this->YoungX = 0;
		this->OldX += 1;
	}
	if (this->OldX >= 6000)
	{
		this->YoungX = 0;
		this->OldX -= 1;
	}
	if (this->OldY <= 0)
	{
		this->YoungY = 0;
		this->OldY += 1;
	}
	if (this->OldY >= 4000)
	{
		this->YoungY = 0;
		this->OldY -= 1;
	}
	OldX += YoungX;
	OldY += YoungY;
}

void Ship::draw(RenderWindow &window)
{
	anim.sprite.setPosition(OldX, OldY);
	anim.sprite.setRotation(Angle + 90);
	window.draw(anim.sprite);

	CircleShape circle(R);
	circle.setFillColor(Color(255, 0, 0, 170));
	circle.setPosition(OldX, OldY);
	circle.setOrigin(R, R);

	CircleShape circle1(R1_Ship);
	circle1.setFillColor(Color(255, 0, 0, 170));
	circle1.setPosition(OldX, OldY);
	circle1.setOrigin(R1_Ship, R1_Ship);

	CircleShape circle2(R2_Ship);
	circle2.setFillColor(Color(255, 0, 0, 170));
	circle2.setPosition(OldX, OldY);
	circle2.setOrigin(R2_Ship, R2_Ship);

	CircleShape circle3(R3_Ship);
	circle3.setFillColor(Color(255, 0, 0, 170));
	circle3.setPosition(OldX, OldY);
	circle3.setOrigin(R3_Ship, R3_Ship);
	//window.draw(circle);//cmt here///////////////////////////////////
}