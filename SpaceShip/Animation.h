#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Animation
{
public:
	////////////Thuộc tính/////////////
	float Frame, speed;
	Sprite sprite;
	std::vector<IntRect> frames;


	////////Phương thức/////////////
	Animation();
	~Animation();
	Animation(Texture &t, int x, int y, int w, int h, int count, float Speed);
	void update();
	bool isEnd();
};