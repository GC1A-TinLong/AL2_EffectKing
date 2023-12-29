#pragma once

struct Vector2 {
	float x;
	float y;
};
struct Vector2i {
	int x;
	int y;
};
struct Size {
	int w;
	int h;
};

enum Mode {
	NoBlend,
	Normal,
	Add,
	Subtract,
	Multiply,
	Screen,
};
enum Area {
	Top,
	Bottom,
	Left,
	Right,
};
enum Effect {
	None,
	Bloom,
	Charge,
	Wave,
	ChargeShot,
	Spark,
};