#pragma once
#include <Novice.h>
#include <Struct.h>
#include <Function.h>
#include <Bullet.h>
class Player
{
public:
	Player();
	~Player();

	Bullet* bullet;

	Vector2 pos_;
	Size size_;
	float spd_;

	Vector2 vector;
	float mouseDistance;

	unsigned int color_;

	Effect effect;

	void Initialization();

	void Control(char* keys);

	void ChargingShot(Vector2i &mouse);

	void Draw();
	void ChargeShotDraw();
};

