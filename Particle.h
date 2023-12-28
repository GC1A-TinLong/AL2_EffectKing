#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Novice.h>
#include <Struct.h>
#include <Function.h>
#include "Player.h"

class Particle
{
public:
	Particle();
	~Particle();

	Vector2 emitter_;
	Vector2 vector_;
	Vector2 pos_;
	Vector2 randSpawnPos_;
	Size halfsize_;
	float spd_;
	float distanceFromEmitter_;
	float normalizedSpd_;
	int endTimer_;
	int resetTimer_;

	int randArea;
	unsigned int randColor;

	unsigned int color_;
	unsigned int R;
	unsigned int G;
	unsigned int B;
	unsigned int A;
	int randRadius;

	float theta;
	float amplitude;
	float waveSpd;
	int randWaveDirection;
	Vector2 wavePos;
	Vector2 tempPos;

	int bufStart_;
	int spawnStart_;
	int effectStart_;
	int bloomStart_;

	void Initialization();

	void Blooming(Vector2 &pos);
	void Charging(Vector2 &pos);
	void MouseCharging(Vector2 &pos);
	void Spawning(Vector2 &pos);
	void SpawnOfWave(Player& player);
	void Waving	 (Player &player);

	/// <summary>
	/// Start from emitter
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="emitter"></param>
	void Normalization(Vector2& vector, Vector2& emitter);
	/// <summary>
	/// Start from pos to emitter
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="emitter"></param>
	void Normalization_toEmitter(Vector2& vector, Vector2& emitter);
	void Draw(/*int handle, Mode mode*/);
};

void ModeSelect(char* keys, char* preKeys, Mode &mode);