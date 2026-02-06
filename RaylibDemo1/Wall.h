#pragma once
#include "raylib.h"

enum Direction
{
	HORIZONTAL, 
	VERTICAL,
	BOTH
};

struct Wall
{
public:
	Rectangle rect;
	Direction dir = VERTICAL;


	Wall(float x, float y, float w, float h, Direction d) // w = width h =height
	{
		this->dir = d;
		rect = Rectangle{ x, y, w, h };
	}

	void Draw()
	{
		DrawRectangleRec(rect, GREEN);
	}
};