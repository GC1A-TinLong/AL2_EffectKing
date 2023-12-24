#pragma once
#include <Novice.h>
#include <Struct.h>
class Player
{
public:
	Player();

	Vector2 pos_;
	Size size_;
	float spd_;
	unsigned int color_;

	void Initialization();

	void Control(char* keys,char*preKeys);

	void Draw();
};

