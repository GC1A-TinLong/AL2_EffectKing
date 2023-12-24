#include "Enemy.h"
Enemy::Enemy() {
	pos_ = { -1000,0 };
	spd_ = 12.0f;
	vector_ = {};

}

void Enemy::Initialization() {
	pos_ = { -1000,0 };
}