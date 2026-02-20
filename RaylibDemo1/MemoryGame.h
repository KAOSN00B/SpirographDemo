#pragma once
#include <vector>
#include "raylib.h"
#include "Tile.h"

using namespace std;

class MemoryGame
{
public:

#define GAP 15
#define WH 800

	vector<Tile> tiles;
	int gridSize = 4; // 4x4 6x6 8x8


	void Main();
	void Start();
	void Update();
	void Draw();

private:
	
};