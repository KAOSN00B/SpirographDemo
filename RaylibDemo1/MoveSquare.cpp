#include "MoveSquare.h"

void MoveSquare::PlayerInput()
{

	if (IsKeyDown(KEY_A))
	{
		_position.x -= 5.0f;
	}
	if (IsKeyDown(KEY_D))
	{
		_position.x += 5.0f;
	}
}

void MoveSquare::Update()
{
	Draw();
}


void MoveSquare::Main()
{
	InitWindow(1200, 1200, "Top Down Shooter Demo");
	SetTargetFPS(60);

	// Create walls ONCE
	Wall walls[] =
	{
		Wall(0, 0, 1200, 10, HORIZONTAL),      // Top
		Wall(0, 1190, 1200, 10, HORIZONTAL),    // Bottom
		Wall(0, 0, 10, 1200, VERTICAL), // Left
		Wall(1190, 0, 10, 1200, VERTICAL) // Right

	};

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		PlayerInput();

		for (const Wall& w : walls)
			CheckCollisionWithWalls(w);

		Update();   // draw LAST

		EndDrawing();
	}

	CloseWindow();
}

void MoveSquare::CheckCollisionWithWalls(const Wall& wall)
{
	Rectangle player = {
		_position.x,
		_position.y,
		(float)_width,
		(float)_height
	};

	if (!CheckCollisionRecs(player, wall.rect))
		return;

	if (wall.dir == HORIZONTAL)
	{
		if (_position.y < wall.rect.y)
			_position.y = wall.rect.y - _height;   // hit from top
		else
			_position.y = wall.rect.y + wall.rect.height; // from bottom
	}
	else if (wall.dir == VERTICAL)
	{
		if (_position.x < wall.rect.x)
			_position.x = wall.rect.x - _width;   // hit from left
		else
			_position.x = wall.rect.x + wall.rect.width; // from right
	}

}

//void MoveSquare::ShootProjectile()
//{
//		if (IsKeyPressed(KEY_SPACE)) {
//			Ball newBullet = {
//				{ playerPos.x, playerPos.y },
//				{ 0, -bulletSpeed }, // Moving up
//				5.0f,
//				RED,
//				true
//			};
//			bullets.push_back(newBullet);
//		}
//
//		// Update: Bullets
//		for (int i = 0; i < bullets.size(); i++) {
//			if (bullets[i].active) {
//				bullets[i].position.y += bullets[i].speed.y * GetFrameTime();
//
//				// Deactivate if off-screen
//				if (bullets[i].position.y < 0) bullets[i].active = false;
//			}
//		}
//
//		// Cleanup: Remove inactive bullets to free memory
//		for (int i = 0; i < bullets.size(); i++) {
//			if (!bullets[i].active) {
//				bullets.erase(bullets.begin() + i);
//				i--; // Adjust index after erase
//			}
//		}
//}

