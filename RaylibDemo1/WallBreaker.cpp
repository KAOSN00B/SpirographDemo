#include "WallBreaker.h"

WallBreaker::WallBreaker()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Wall Breaker");
	SetTargetFPS(60);

	Start();

	while (!WindowShouldClose())
	{
		Update();

		BeginDrawing();
		ClearBackground(Color{ 25,25,25 });

		Draw();

		EndDrawing();
	}

	CloseWindow();
}

void WallBreaker::Start()
{
	player.rect =
	{
		SCREEN_WIDTH / 2 - 50,
		SCREEN_HEIGHT - 40,
		100,
		20
	};

	ResetBall();

	float spaceForBricks = SCREEN_WIDTH - (GAP * (BRICKS_PER_ROW + 1));
	float brickWidth = spaceForBricks / BRICKS_PER_ROW;

	for (int row = 0; row < ROWS_OF_BRICKS; row++)
	{
		for (int col = 0; col < BRICKS_PER_ROW; col++)
		{
			float x = GAP + col * (brickWidth + GAP);
			float y = GAP + row * (BRICK_HEIGHT + GAP);

			Brick brick;
			brick.color = colors[row];
			brick.rect = { x, y, brickWidth, BRICK_HEIGHT };

			bricks.push_back(brick);
		}
	}
}

void WallBreaker::Update()
{
	Controls();

	if (!ball.launched)
		return;

	ball.Update();

	// Wall collisions
	if (ball.position.x <= ball.radius ||
		ball.position.x >= SCREEN_WIDTH - ball.radius)
	{
		ball.speed.x *= -1;
	}

	if (ball.position.y <= ball.radius)
	{
		ball.speed.y *= -1;
	}

	if (ball.position.y > SCREEN_HEIGHT)
	{
		ResetBall();
	}

	// Paddle collision
	if (CheckCollisionCircleRec(ball.position, ball.radius, player.rect))
	{
		if (ball.speed.y > 0) // only bounce if the ball is moving downwards
		ball.speed.y *= -1;
	}

	// Brick collision
	for (int i = 0; i < bricks.size(); i++)
	{
		if (CheckCollisionCircleRec(ball.position, ball.radius, bricks[i].rect))
		{
			ball.speed.y *= -1;

			bricks.erase(bricks.begin() + i);

			break;
		}
	}
}

void WallBreaker::Draw()
{
	DrawRectangleRec(player.rect, player.color);

	ball.Draw();

	for (Brick& b : bricks)
	{
		b.Draw();
	}
}

void WallBreaker::Controls()
{
	const float speed = 5;

	if (IsKeyDown(KEY_A))
	{
		player.rect.x -= speed;
	}

	if (IsKeyDown(KEY_D))
	{
		player.rect.x += speed;
	}

	// left wall
	if (player.rect.x < 0)
	{
		player.rect.x = 0;
	}

	// right wall
	if (player.rect.x > SCREEN_WIDTH - player.rect.width)
	{
		player.rect.x = SCREEN_WIDTH - player.rect.width;
	}
	if (!ball.launched)
	{
		ball.position.x = player.rect.x + player.rect.width / 2;
		ball.position.y = player.rect.y - ball.radius;

		if (IsKeyPressed(KEY_SPACE))
		{
			ball.launched = true;
		}
	}
}

void WallBreaker::ResetBall()
{
	ball.position.x = player.rect.x + player.rect.width / 2;
	ball.position.y = player.rect.y - ball.radius;

	ball.speed = { 4, -4 };
	ball.launched = false;
}