#include "UFO.h"



UFO::UFO()
{
	this->life = 1;
	this->name = "UFO";
	this->Blood = 5;
	this->R1_UFO = 70;//300 vàng
	this->R2_UFO = 1000;//800 xanh dương
	this->R3_UFO = 5000;//3000 xanh lá cây
	//this->YoungX = 0.001;
	//this->YoungY = 0.001;
	this->time_UFO = 5;
	this->frame_UFO = 0;
}


UFO::~UFO()
{
}

void UFO::settings(Animation &a, float oldX, float oldY, float radius,float R2, float angle, int species, int blood)
{
	this->anim = a;
	this->OldX = oldX;
	this->OldY = oldY;
	this->R = radius;
	this->Angle = angle;
	this->Species = species;
	this->Blood = blood;
	this->R2_UFO = R2;
}
void UFO::update()
{

	int v = 10;
	if (this->Species == 0)
		v = 12;
	OldX += YoungX * v;
	OldY += YoungY * v;
	if (this->Species == 4 || this->Species == 5 || this->Species == 6)
	{
		OldX = OldX;
		OldY = OldY;
	}
}
void UFO::draw(RenderWindow &window)
{
	anim.sprite.setPosition(OldX, OldY);
	anim.sprite.setRotation(Angle + 90);
	window.draw(anim.sprite);

	CircleShape circle3(R3_UFO);
	circle3.setFillColor(Color(54, 171, 223, 170));//xanh lá cây
	circle3.setPosition(OldX, OldY);
	circle3.setOrigin(R3_UFO, R3_UFO);
	//window.draw(circle3);//cmt here///////////////////////////////////

	CircleShape circle2(R2_UFO);
	circle2.setFillColor(Color(16, 54, 103, 170));//xanh dương
	circle2.setPosition(OldX, OldY);
	circle2.setOrigin(R2_UFO, R2_UFO);
	//window.draw(circle2);//cmt here///////////////////////////////////

	CircleShape circle1(R1_UFO);
	circle1.setFillColor(Color(252, 245, 76, 170));//vàng
	circle1.setPosition(OldX, OldY);
	circle1.setOrigin(R1_UFO, R1_UFO);
	//window.draw(circle1);//cmt here///////////////////////////////////

	CircleShape circle(R);
	circle.setFillColor(Color(255, 0, 0, 170));//đỏ
	circle.setPosition(OldX, OldY);
	circle.setOrigin(R, R);
	//window.draw(circle);//cmt here///////////////////////////////////

}
