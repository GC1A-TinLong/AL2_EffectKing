#pragma once
#include <Struct.h>
#include <Function.h>

class Sparkling
{
public:
	Sparkling();
	
	Vector2 emitter;
	Vector2 vector;
	Vector2 pos;
	Vector2 randSpawnPos1;
	Vector2 randSpawnPos2;
	Vector2 randSpawnPos3;
	int radius;

	float t;
	float endframe;
	Vector2 randP1;
	Vector2 randP2;
	Vector2 randP3;
	int randArea2;
	int randArea3;

	int start;

	int endTimer;
	int resetTimer;

	unsigned int color;
	unsigned int randColor;
	unsigned int R;
	unsigned int G;
	unsigned int B;
	unsigned int A;
	int randRadius;

	void Initialization();

	void SparkSpawn(Vector2i &mouse);
	void SparkEffect();

	void Draw();
};

