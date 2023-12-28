#include "Bullet.h"

Bullet::Bullet()
{
	pos = { -1000,0 };
	radius = 50;
	spd = 50.0f;
	color = 0xFF0000FF;

}

void Bullet::Initialization() {
	pos = { -1000,0 };
	radius = 50;
	spd = 50.0f;
	color = 0xFF0000FF;
}