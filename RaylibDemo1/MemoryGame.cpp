#include "MemoryGame.h"
#include "Tile.h"
#include <random>
#include <algorithm>




void MemoryGame::Main()
{

	Start();

	InitWindow(WH, WH + 200, "Memory Game"); // change 200 to a variable 
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(Color{ 25, 25, 25 });

		Update();

		EndDrawing();
	}

	CloseWindow();
}
void MemoryGame::Start()
{
	srand(time(NULL));
	vector<int> numbers;
	for (int i = 0; i < gridSize * gridSize; ++i)
	{
		numbers.push_back(i);
		numbers.push_back(i);
	}

	int tileWH = (WH - (GAP + GAP * gridSize)) / gridSize;


	for (int h = 0; h < gridSize; h++)
	{
		for (int v = 0; v < gridSize; v++)
		{
			int x = GAP + h * (GAP + tileWH);
			int y = GAP + v * (GAP + tileWH) + 100; // 100 needs a name just a place holder

			int num = h + (v * gridSize);

			int randomID = rand() % numbers.size();

			Tile tile = Tile{ x, y, tileWH, numbers[randomID] };

			tiles.push_back(tile);
			numbers.erase(numbers.begin() + randomID);
		}
	}
}
void MemoryGame::Update()
{

	switch (gameState)
	{
	case GameState::Play: Play();
	case GameState::Menu: Menu();
	case GameState::Pause: Pause();
	case GameState::GameOver: GameOver();
	case GameState::Win: Win();
	default:
		break;
	}
}
void MemoryGame::Play()
{
	Vector2 mousePos = GetMousePosition();

	// Add a timer
	// add game over if it takes longer then x minutes
	// this has to be relevant to grid
	// have game finished state
	// if the player finishes show how long it took
	// have a restart button 
	// have a UI for selecting mode of game(4, 6 or 8x8)
	// beggining of game ask for user name
	// when they finish or when they they press a button (leaderboard)
	// show leaderboard
	// come up with a scoring system that is used regardless of game mode

	// ==========================
	// INPUT PHASE
	// ==========================
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && clickAllowed)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			if (CheckCollisionPointRec(mousePos, tiles[i].rect))
			{
				if (tiles[i].state != Hidden)
					continue;

				tiles[i].state = Flipped;

				if (tile1 == nullptr)
				{
					tile1 = &tiles[i];
				}
				else if (&tiles[i] != tile1)
				{
					tile2 = &tiles[i];
					compareMode = true;
					clickAllowed = false;
					timeOfSecondClick = GetTime();
				}

				break;
			}
		}
	}

	// ==========================
	// RESOLVE PHASE (RUN EVERY FRAME)
	// ==========================
	if (compareMode)
	{
		if (GetTime() > timeOfSecondClick + WAITTIME)
		{
			if (tile1 && tile2)
			{
				if (tile1->number == tile2->number)
				{
					tile1->state = Matched;
					tile2->state = Matched;
				}
				else
				{
					tile1->state = Hidden;
					tile2->state = Hidden;
				}
			}

			tile1 = nullptr;
			tile2 = nullptr;
			compareMode = false;
			clickAllowed = true;
		}
	}

	// ==========================
	// TILE UPDATE
	// ==========================
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].Update();
	}
}

void MemoryGame::Menu()
{

}

void MemoryGame::Pause()
{

}

void MemoryGame::GameOver()
{

}

void MemoryGame::Win()
{

}
