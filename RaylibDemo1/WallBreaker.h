#pragma once
#include "raylib.h"
#include "Ball.h"
#include <vector>
#include <algorithm>
class WallBreaker
{
public:

#define LIVES 3
#define ROWS_OF_BRICKS 5
#define BRICKS_PER_ROW 8
#define GAP 8
#define BRICK_HEIGHT 24
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

	struct Player
	{
		Rectangle rect;
		Color color = WHITE;
	};

	struct Brick
	{
		Color color = WHITE;
		Rectangle rect{};

		void Draw() { DrawRectangleRec(rect, color); }
	};

	struct Ball
	{
		Vector2 position{};
		Vector2 speed = { 0, -3 };
		float radius = 8;
		Color color = MAROON;
		bool launched = false;

		void Draw()
		{
			DrawCircle(position.x, position.y, radius, color);
		}

		void Update()
		{
			position += speed;
		}
	};

public:
	WallBreaker();

	void Start();
	void Update();
	void Draw();
	void Controls();
	void ResetBall();

private:

	Color colors[ROWS_OF_BRICKS] =
	{
		RED,
		GREEN,
		YELLOW,
		BLUE,
		PURPLE
	};

	std::vector<Brick> bricks;

	Player player;
	Ball ball;
};