#include "Player.h"
Player::Player() {
	pos_ = { 340.0f, 360.0f };
	size_ = { 30,30 };
	spd_ = 10.0f;
	color_ = WHITE;
}

void Player::Initialization() {
	pos_ = { 340.0f, 360.0f };
	size_ = { 30,30 };
	spd_ = 10.0f;
	color_ = WHITE;
}
void Player::Control(char* keys,char*preKeys) {
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

	if (keys[DIK_R] && !preKeys[DIK_R]) {
		Initialization();
	}
}

void Player::Draw()
{
	Novice::DrawEllipse((int)pos_.x, (int)pos_.y, size_.w, size_.h, 0, color_, kFillModeSolid);
}
