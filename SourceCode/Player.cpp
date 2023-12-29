#include "Player.h"
Player::Player() {
	bullet = new Bullet;

	pos_ = { 640.0f, 360.0f };
	size_ = { 40,40 };
	spd_ = 3.0f;
	color_ = 0x0000AAFF;

	vector = { 0,0 };
	mouseDistance = 0;
}
Player::~Player() {
	delete bullet;
}

void Player::Initialization() {
	pos_ = { 640.0f, 360.0f };
	size_ = { 40,40 };
	spd_ = 3.0f;
	color_ = 0x000088FF;

	vector = { 0,0 };
	mouseDistance = 0;

	effect = None;
}
void Player::Control(char* keys) {
	if (keys[DIK_W] || keys[DIK_UPARROW]) {
		pos_.y -= spd_;
	}
	if (keys[DIK_S] || keys[DIK_DOWNARROW]) {
		pos_.y += spd_;
	}
	if (keys[DIK_A] || keys[DIK_LEFTARROW]) {
		pos_.x -= spd_;
	}
	if (keys[DIK_D] || keys[DIK_RIGHTARROW]) {
		pos_.x += spd_;
	}

	if (pos_.x >= 1280.0f - size_.w) {
		pos_.x = 1280.0f - size_.w;
	}
	if (pos_.x <= size_.w) {
		pos_.x = (float)size_.w;
	}
	if (pos_.y >= 720.0f - size_.h) {
		pos_.y = 720.0f - size_.h;
	}
	if (pos_.y <= size_.h) {
		pos_.y = (float)size_.h;
	}
}

void Player::ChargingShot(Vector2i& mouse) {
	vector.x = (float)mouse.x;
	vector.y = (float)mouse.y;

	Normalization(vector, pos_, mouseDistance);
	bullet->pos.x += vector.x * bullet->spd;
	bullet->pos.y += vector.y * bullet->spd;
}

void Player::Draw()
{
	Novice::DrawEllipse((int)pos_.x, (int)pos_.y, size_.w, size_.h, 0, color_, kFillModeSolid);
}
void Player::ChargeShotDraw()
{
	Novice::DrawEllipse(int(bullet->pos.x), int(bullet->pos.y), bullet->radius, bullet->radius, 0, bullet->color, kFillModeSolid);
}
	