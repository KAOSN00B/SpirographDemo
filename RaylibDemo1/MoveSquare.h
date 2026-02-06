#pragma once
#include <vector>
#include "raylib.h"
#include "Wall.h"
#include "Ball.h"

class MoveSquare	
{
public:
	MoveSquare(Vector2 pos, int w, int h)
	{
		_position = pos;
		_width = w;
		_height = h;
	}

	void Draw()
	{
		DrawRectangleV(_position, Vector2{ (float)_width, (float)_height }, RED);
	}

	void PlayerInput();
	void Update();
	void Main();
	void CheckCollisionWithWalls(const Wall& wall);
	void ShootProjectile();	


private:

	Vector2 _position;
	int _height;
	int _width;
	float _bulletSpeed = 500.0f;
	std::vector <Ball> _ballsShot;

};