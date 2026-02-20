#include "MemoryGame.h"
#include "Tile.h"
#include <random>
#include <algorithm>



void MemoryGame::Main()
{
    Start();

    InitWindow(WH, WH, "Memory Game");
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
            int y = GAP + v * (GAP + tileWH);

            int num =  h + (v * gridSize);

            int randomID = rand() % numbers.size();


            Tile tile = Tile{ x, y, tileWH, numbers[randomID]};
            
            tiles.push_back(tile);
            numbers.erase(numbers.begin() + randomID);
            
        }
    }
}
void MemoryGame::Update()
{
    for (int i = 0; i < tiles.size(); i++)
    {
        tiles[i].Update();
        
    }
}
void MemoryGame::Draw()
{
    
}
