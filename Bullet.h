#pragma once
#include <Struct.h>

class Bullet
{
public:
	Bullet();

	Vector2 pos;
	int radius;
	float spd;
	unsigned int color;

	void Initialization();
};

