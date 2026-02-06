#pragma once
#include "raylib.h"
#include "Wall.h"


inline Vector2 operator-(const Vector2& v)
{
	return Vector2{ -v.x, -v.y };
}

inline Vector2& operator+=(Vector2& a, const Vector2& b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

class Ball
{
public:
	Vector2 center;
	int radius;
	Color color;
	int timeToCollide = 0;

	Vector2 velocity;

	bool collideWith;

#define MAX_BALLS 20;



	Ball(Vector2 cen, int r, Color c, bool colWith = true) 
	{
		this->center = cen;
		this->radius = r;
		this->color = c;
		this->collideWith = colWith;

		float xVel = GetRandomValue(-5, 10);
		SetRandomSeed(32);
		float yVel = GetRandomValue(-5, 5);

		this->velocity = Vector2{ float(xVel), float(yVel)};
	}

	void CheckAgainstWall(Wall wall)
	{
		if (CheckCollisionCircleRec(center, radius, wall.rect))
			ChangeDirection(wall.dir);
	}

	void Update()
	{
		DrawCircle(center.x, center.y, radius, color);

		center += velocity;
		timeToCollide += 1;

		if (timeToCollide > 100)
		{
			collideWith = true;
		}

	}

	void ChangeDirection(Direction dir = BOTH)
	{
		if (dir == BOTH)
			this->velocity = -this->velocity;
		else if (dir == VERTICAL)
			this->velocity.x *= -1;
		else
			this->velocity.y *= -1;
		
	}


private:


};