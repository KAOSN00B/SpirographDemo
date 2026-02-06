#include "Beginner.h"
#include "raylib.h"
#include <string>
#include <vector>

using namespace std;

void Beginner::StarterUpdate()
{

	DrawCircle(250, 250, 80, RED);

	DrawLine(50, 50, 450, 50, BLACK);

	Vector2 startPos = { 50, 100 };
	Vector2 endPos = { 450, 100 };

	DrawLineEx(startPos, endPos, 5, RED);

	Color myColour = { 20, 144, 122, 255 };

	DrawRectangle(150, 150, 150, 50, myColour);

}


void Beginner::DrawRectangleShadows(Rectangle rect, int length, int steps)
{
	int stepSize = length / steps;
	float alphaStep = 255.0f / (steps + 1);

	for (int i = steps; i > 0; i--)
	{
		Rectangle shadow = {
			rect.x,
			rect.y + stepSize * i,
			rect.width,
			rect.height
		};

		unsigned char alpha = (unsigned char)(255 - (alphaStep * i));
		Color c = { 0, 0, 0, alpha };

		DrawRectangleRounded(shadow, 0.5f, 16, c);
	}
}

void Beginner::ButtonUpdate()
{

	std::string text = "Click Me!";
	int fontSize = 36;
	float pad = 24.0f;

	int textWidth = MeasureText(text.c_str(), fontSize);

	Rectangle rect = DrawFromCenter(
		250, 250,
		textWidth + 2 * pad,
		fontSize + 2 * pad);

	DrawRectangleShadows(rect, 30, 4);

	DrawRectangleRounded(rect, 0.5f, 16, MAROON);
	DrawRectangleRoundedLinesEx(rect, 0.5f, 16, 6, BLACK);

	DrawText(
		text.c_str(),
		250 - textWidth / 2,
		250 - fontSize / 2,
		fontSize,
		BLACK
	);
}

void Beginner::PolyUpdate()
{
	DrawPoly(Vector2{ 250, 250 }, 6, 100.0f, 0.0f, BLUE);
}

void Beginner::MouseUpdate()
{
	if (IsKeyDown(KEY_SPACE))
	{
		DrawCircle(GetMouseX(), GetMouseY(), 40, GREEN);
	}

}


void Beginner::MoveCircleWASD()
{
	InitWindow(800, 1000, "My First Game");
	SetTargetFPS(60);

	float x = 400;
	float y = 500;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawCircle(400, 500, 80, RED);

		if (IsKeyPressed(KEY_W))


			EndDrawing();
	}
}

void Beginner::CollisionTest()
{

	Rectangle bottom = Rectangle{ 0, 450, 500, 50 };

	int radius = 50;

	Vector2 centre = Vector2{ 250, 100 };
	int gravity = 2;

	InitWindow(500, 500, "My First Game");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		DrawRectangleRec(bottom, RED);
		DrawCircle(centre.x, centre.y, radius, BLUE);
		centre.y += gravity; // the pixels (2) amount until circle goes to the bottom.

		if (CheckCollisionCircleRec(centre, radius, bottom))
		{
			gravity *= -1;
		}

		EndDrawing();
	}

	CloseWindow();
}

void Beginner::Update()
{
	vector<Circle> circles;   // inside Update, but ABOVE the while

	float x = GetRandomValue(50, 250);
	float y = GetRandomValue(50, 300);
	float speedX = 5;
	float speedY = 5;

	float radius = 25;



	vector<Color> colors = { RED, BLUE, GREEN, ORANGE, PURPLE, MAROON, GOLD,
		PINK, YELLOW, VIOLET, BROWN, DARKBROWN, PURPLE };

	InitWindow(500, 500, "My First Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		if (x + speedX - radius <= 0 || x + speedX + radius >= 500 ||
			y + speedY - radius <= 0 || y + speedY + radius >= 500)
		{
			if (x + speedX - radius <= 0 || x + speedX + radius >= 500)
			{
				speedX *= -1;

			}

			if (y + speedY - radius <= 0 || y + speedY + radius >= 500)
			{
				speedY *= -1;

			}

			Circle c;
			c.cen = { x, y };
			c.fallSpeedX = speedX;
			c.fallSpeedY = speedY;
			c.color = colors[GetRandomValue(0, colors.size() - 1)];
			circles.push_back(c);
		}

		// move once
		x += speedX;
		y += speedY;

		DrawCircle(x, y, radius, colors[0]);

		// update & draw all other circles
		for (Circle& c : circles)
		{
			if (c.cen.x + c.fallSpeedX - radius <= 0 || c.cen.x + c.fallSpeedX + radius >= 500)
			{
				c.fallSpeedX *= -1;
				speedY += .2f;
			}

			if (c.cen.y + c.fallSpeedY - radius <= 0 || c.cen.y + c.fallSpeedY + radius >= 500)
			{
				c.fallSpeedY *= -1;
				speedX += .2f;
			}

			c.cen.x += c.fallSpeedX;
			c.cen.y += c.fallSpeedY;

			DrawCircle(c.cen.x, c.cen.y, radius, c.color);
		}

		EndDrawing();
	}

	CloseWindow();
}