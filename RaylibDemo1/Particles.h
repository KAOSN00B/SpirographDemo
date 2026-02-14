#pragma once
#include "raylib.h"
#include <vector>

using namespace std;
struct SingleParticle
{
	Vector2 center = Vector2{ 0, 0 };
	float radius = 0.0f;
	Color color = BLACK;
	float speed = 0.0f;
	float angle = 0.0f;
	float gravity = -0.5f;

	float increaseRadius = 0.1f + (float)(rand() % 20) / 20.0f;
	bool active = false;

	void Activate(Vector2 cen, float ang, Color col, float rad, float sp)
	{
		this->center = cen;
		this->angle = ang;
		this->color = col;
		this->radius = rad;
		this->speed = sp;
		gravity = -0.5f;

		active = true;

		
	}

	void Update()
	{
		if (!this->active)
			return;
		
		center.x += cos(angle * DEG2RAD) * speed;
		center.y += sin(angle * DEG2RAD) * speed + gravity;

		radius += increaseRadius;
		speed += 0.25f;
		gravity -= 0.075f;

		float alpha = color.a;

		if (color.a > 0)
		{
			color.a -= 5;
			color.g -= 1;
		}
	
		else
			active = false;

	}

	void Draw()
	{
		this->Update();

		if(this->active)
			DrawCircle(center.x, center.y, radius, color);
	}

	
};

class Particles
{
public:

#define POOL_SIZE 1000 // MAXIMUM AMOUNT

	vector<SingleParticle>  pool;

	// object pooling


	void Main();
	void Start();
	void Update();
	void Draw();

private:


};