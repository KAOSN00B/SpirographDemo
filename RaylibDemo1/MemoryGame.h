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
	bool shouldExit = false;
	float gameTimer = 60.0f;   // 60 seconds
	float totalTime = 0.0f;     // tracks elapsed time
	float finalTime = 0.0f;		// used for win screen
	int score = 0;
	int timeBonus = 0;		// bonus points for finishing early
	int displayedScore = 0;
	bool scoreAnimating = false;
	bool matchScored = false;  // prevents double scoring
	float timeOfSecondClick = 0.0f;
	GameState gameState = GameState::Menu;

	void Main();
	void Start();
	void Update();
	void Draw();
	void Play();
	void Menu();
	void DrawMenu();
	void DrawPlay();
	void DrawWin();
	void DrawGameOver();
	void DrawPause();
private:
	
};