#pragma once
#include <vector>
#include "raylib.h"
#include "Tile.h"

using namespace std;

enum GameState
{
	Menu,
	Play,
	GameOver,
	Pause,
	Win
};

class MemoryGame
{
public:

#define GAP 15
#define WH 1000
#define WAITTIME .800 //ms

	vector<Tile> tiles;

	Tile* tile1 = nullptr;
	Tile* tile2 = nullptr;
	int gridSize = 4; // 4x4 6x6 8x8
	bool compareMode = false;
	bool clickAllowed = true;
	float timeOfSecondClick = 0.0f;

	float gameTimer;
	GameState gameState = GameState::Menu;

	void Main();
	void Start();
	void Update();

	void Play();
	void Menu();
	void Pause();
	void GameOver();
	void Win();
private:
	
};