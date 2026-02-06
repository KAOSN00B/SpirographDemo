#pragma once
#include <string>
#include <vector>
#include "raylib.h"

class Beginner
{
public:

	void Update();
	void CollisionTest();
	void MoveCircleWASD();

	Rectangle DrawFromCenter(float cenX, float cenY, float width, float height)
	{
		return Rectangle{ cenX - (width / 2), cenY - (height / 2), width, height };

	}

	void MouseUpdate();
	void PolyUpdate();
	void ButtonUpdate();
	void DrawRectangleShadows(Rectangle rect, int length, int steps);
	void StarterUpdate();
	
	Vector2 PlaceCircle(int x, int y)
	{

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			x = GetMouseX();
			y = GetMouseY();
		}

		DrawCircle(x, y, 40, GREEN);

		return Vector2{ (float)x, (float)y };

	}

	struct Circle
	{
		Vector2 cen; Color color; float fallSpeedX; float fallSpeedY;
	};

private:

};