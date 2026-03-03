#include "MemoryGame.h"
#include "Tile.h"
#include <vector>
#include <ctime>
#include <iostream>

void MemoryGame::Main()
{
    gameState = GameState::Menu;
    shouldExit = false;

    InitWindow(WH, WH + 200, "Memory Game");
    SetTargetFPS(60);

    while (!WindowShouldClose() && !shouldExit)
    {
        Update();

        BeginDrawing();
        ClearBackground(Color{ 25,25,25 });
        Draw();
        EndDrawing();
    }

    CloseWindow();
}

void MemoryGame::Start()
{
    if (gridSize != 4 && gridSize != 6 && gridSize != 8)
        gridSize = 4;

    tiles.clear();

    std::vector<int> numbers;
    int pairCount = (gridSize * gridSize) / 2;

    for (int i = 1; i <= pairCount; i++)
    {
        numbers.push_back(i);
        numbers.push_back(i);
    }

    int tileWH = (WH - (GAP + GAP * gridSize)) / gridSize;

    for (int x = 0; x < gridSize; x++)
    {
        for (int y = 0; y < gridSize; y++)
        {
            int drawX = GAP + x * (GAP + tileWH);
            int drawY = GAP + y * (GAP + tileWH) + 100;

            int randIndex = rand() % numbers.size();
            tiles.emplace_back(drawX, drawY, tileWH, numbers[randIndex]);
            numbers.erase(numbers.begin() + randIndex);
        }
    }

    tile1 = nullptr;
    tile2 = nullptr;
    compareMode = false;
    clickAllowed = true;
    timeOfSecondClick = 0;

    gameTimer = 60.0f;
    totalTime = 0.0f;
    finalTime = 0.0f;
    score = 0;
}

void MemoryGame::Update()
{
    switch (gameState)
    {
    case GameState::Menu:
        Menu();
        break;

    case GameState::Play:
        Play();
        break;

    case GameState::Pause:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            gameState = GameState::Play;
        break;

    case GameState::GameOver:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            gameState = GameState::Menu;
        break;

    case GameState::Win:

        if (scoreAnimating)
        {
            int increment = (score - displayedScore) / 8;

            if (increment < 5)
                increment = 5;

            displayedScore += increment;

            if (displayedScore >= score)
            {
                displayedScore = score;
                scoreAnimating = false;
            }
        }
        else
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                gameState = GameState::Menu;
        }

        break;

    default:
        break;
    }
}

void MemoryGame::Play()
{
    float dt = GetFrameTime();
    gameTimer -= dt;
    totalTime += dt;

    if (gameTimer <= 0)
    {
        gameTimer = 0;
        gameState = GameState::GameOver;
        return;
    }

    Vector2 mousePos = GetMousePosition();

    // Bottom buttons
    float btnW = 180;
    float btnH = 55;
    float spacing = 25;
    float padding = 30;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    float totalWidth = btnW * 4 + spacing * 3;
    float startX = screenW / 2 - totalWidth / 2;
    float yPos = screenH - btnH - padding;

    Rectangle btnMenu = { startX, yPos, btnW, btnH };
    Rectangle btnRestart = { startX + btnW + spacing, yPos, btnW, btnH };
    Rectangle btnPause = { startX + 2 * (btnW + spacing), yPos, btnW, btnH };
    Rectangle btnQuit = { startX + 3 * (btnW + spacing), yPos, btnW, btnH };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePos, btnMenu))
        {
            gameState = GameState::Menu;
            return;
        }

        if (CheckCollisionPointRec(mousePos, btnRestart))
        {
            Start();
            return;
        }

        if (CheckCollisionPointRec(mousePos, btnPause))
        {
            gameState = GameState::Pause;
            return;
        }

        if (CheckCollisionPointRec(mousePos, btnQuit))
        {
            shouldExit = true;
            return;
        }
    }

    // Tile clicking
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && clickAllowed)
    {
        for (auto& tile : tiles)
        {
            if (CheckCollisionPointRec(mousePos, tile.rect) && tile.state == Hidden)
            {
                tile.state = Flipped;

                if (!tile1)
                    tile1 = &tile;
                else if (&tile != tile1)
                {
                    tile2 = &tile;
                    compareMode = true;
                    clickAllowed = false;
                    timeOfSecondClick = GetTime();
                }
                break;
            }
        }
    }

    if (compareMode && GetTime() > timeOfSecondClick + WAITTIME)
    {
        if (tile1->number == tile2->number)
        {
            tile1->state = Matched;
            tile2->state = Matched;
            score += 500;
        }
        else
        {
            tile1->state = Hidden;
            tile2->state = Hidden;
        }

        tile1 = nullptr;
        tile2 = nullptr;
        compareMode = false;
        clickAllowed = true;

        // Check win
        bool allMatched = true;
        for (auto& tile : tiles)
        {
            if (tile.state != Matched)
            {
                allMatched = false;
                break;
            }
        }

        if (allMatched)
        {
            finalTime = totalTime;
            timeBonus = (int)gameTimer * 200;   // 200 points per remaining second
            score += timeBonus;
            displayedScore = 0;        // start at zero
            scoreAnimating = true;     // enable animation
            gameState = GameState::Win;
        }
    }
}

void MemoryGame::Menu()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    Vector2 mousePos = GetMousePosition();

    float btnW = 500;      // bigger
    float btnH = 90;       // taller
    float gap = 35;

    float centerX = screenW / 2.0f;
    float startY = screenH * 0.35f;

    Rectangle btn4 = { centerX - btnW / 2, startY, btnW, btnH };
    Rectangle btn6 = { centerX - btnW / 2, startY + btnH + gap, btnW, btnH };
    Rectangle btn8 = { centerX - btnW / 2, startY + 2 * (btnH + gap), btnW, btnH };

    Rectangle btnQuit = { centerX - 200, screenH - 140, 400, 70 };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePos, btn4)) { gridSize = 4; Start(); gameState = GameState::Play; }
        else if (CheckCollisionPointRec(mousePos, btn6)) { gridSize = 6; Start(); gameState = GameState::Play; }
        else if (CheckCollisionPointRec(mousePos, btn8)) { gridSize = 8; Start(); gameState = GameState::Play; }
        else if (CheckCollisionPointRec(mousePos, btnQuit)) { shouldExit = true; }
    }
}

void MemoryGame::Draw()
{
    switch (gameState)
    {
    case GameState::Menu:
        DrawMenu();
        break;

    case GameState::Play:
        DrawPlay();
        break;

    case GameState::GameOver:
        DrawGameOver();
        break;

    case GameState::Win:
        DrawWin();
        break;

    case GameState::Pause:
        DrawPause();
        break;

    default:
        break;
    }
}
void MemoryGame::DrawMenu()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    Vector2 mousePos = GetMousePosition();

    const char* title = "MEMORY GAME";
    DrawText(title,
        screenW / 2 - MeasureText(title, 70) / 2,
        100,
        70,
        RAYWHITE);

    float btnW = 500;
    float btnH = 90;
    float gap = 35;

    float centerX = screenW / 2.0f;
    float startY = screenH * 0.35f;

    Rectangle btn4 = { centerX - btnW / 2, startY, btnW, btnH };
    Rectangle btn6 = { centerX - btnW / 2, startY + btnH + gap, btnW, btnH };
    Rectangle btn8 = { centerX - btnW / 2, startY + 2 * (btnH + gap), btnW, btnH };
    Rectangle btnQuit = { centerX - 200, screenH - 140, 400, 70 };

    bool hover4 = CheckCollisionPointRec(mousePos, btn4);
    bool hover6 = CheckCollisionPointRec(mousePos, btn6);
    bool hover8 = CheckCollisionPointRec(mousePos, btn8);
    bool hoverQuit = CheckCollisionPointRec(mousePos, btnQuit);

    DrawRectangleRec(btn4, hover4 ? DARKBLUE : BLUE);
    DrawRectangleRec(btn6, hover6 ? DARKBLUE : BLUE);
    DrawRectangleRec(btn8, hover8 ? DARKBLUE : BLUE);
    DrawRectangleRec(btnQuit, hoverQuit ? MAROON : RED);

    DrawText("4 x 4", btn4.x + btnW / 2 - MeasureText("4 x 4", 36) / 2, btn4.y + btnH / 2 - 18, 36, RAYWHITE);
    DrawText("6 x 6", btn6.x + btnW / 2 - MeasureText("6 x 6", 36) / 2, btn6.y + btnH / 2 - 18, 36, RAYWHITE);
    DrawText("8 x 8", btn8.x + btnW / 2 - MeasureText("8 x 8", 36) / 2, btn8.y + btnH / 2 - 18, 36, RAYWHITE);
    DrawText("QUIT", btnQuit.x + btnQuit.width / 2 - MeasureText("QUIT", 30) / 2,
        btnQuit.y + btnQuit.height / 2 - 15, 30, RAYWHITE);
}

void MemoryGame::DrawPlay()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    Vector2 mousePos = GetMousePosition();

    for (auto& tile : tiles)
        tile.Update();

    DrawText("Memory Match",
        screenW / 2 - MeasureText("Memory Match", 40) / 2,
        10,
        40,
        RAYWHITE);

    // Timer
    std::string timerText = "Time: " + std::to_string((int)gameTimer);
    DrawText(timerText.c_str(), 30, 30, 32, RAYWHITE);

    // Score
    std::string scoreText = "Score: " + std::to_string(score);
    DrawText(scoreText.c_str(),
        screenW - MeasureText(scoreText.c_str(), 32) - 30,
        30,
        32,
        RAYWHITE);

    float btnW = 180;     
    float btnH = 55;
    float padding = 30;
    float spacing = 25;

    float totalWidth = btnW * 4 + spacing * 3;
    float startX = screenW / 2 - totalWidth / 2;
    float yPos = screenH - btnH - padding;

    Rectangle btnMenu = { startX + 0 * (btnW + spacing), yPos, btnW, btnH };
    Rectangle btnRestart = { startX + 1 * (btnW + spacing), yPos, btnW, btnH };
    Rectangle btnPause = { startX + 2 * (btnW + spacing), yPos, btnW, btnH };
    Rectangle btnQuit = { startX + 3 * (btnW + spacing), yPos, btnW, btnH };

    bool hoverMenu = CheckCollisionPointRec(mousePos, btnMenu);
    bool hoverRestart = CheckCollisionPointRec(mousePos, btnRestart);
    bool hoverPause = CheckCollisionPointRec(mousePos, btnPause);
    bool hoverQuit = CheckCollisionPointRec(mousePos, btnQuit);

    DrawRectangleRec(btnMenu, hoverMenu ? DARKGREEN : GREEN);
    DrawRectangleRec(btnRestart, hoverRestart ? DARKBLUE : BLUE);
    DrawRectangleRec(btnPause, hoverPause ? ORANGE : GOLD);
    DrawRectangleRec(btnQuit, hoverQuit ? MAROON : RED);

    DrawText("Menu",
        btnMenu.x + btnW / 2 - MeasureText("Menu", 20) / 2,
        btnMenu.y + btnH / 2 - 10,
        20, RAYWHITE);

    DrawText("Restart",
        btnRestart.x + btnW / 2 - MeasureText("Restart", 20) / 2,
        btnRestart.y + btnH / 2 - 10,
        20, RAYWHITE);

    DrawText("Pause",
        btnPause.x + btnW / 2 - MeasureText("Pause", 20) / 2,
        btnPause.y + btnH / 2 - 10,
        20, RAYWHITE);

    DrawText("Quit",
        btnQuit.x + btnW / 2 - MeasureText("Quit", 20) / 2,
        btnQuit.y + btnH / 2 - 10,
        20, RAYWHITE);
}

void MemoryGame::DrawGameOver()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    DrawText("GAME OVER",
        screenW / 2 - MeasureText("GAME OVER", 70) / 2,
        screenH / 2 - 100,
        70,
        RED);

    std::string finalScore = "Final Score: " + std::to_string(score);
    DrawText(finalScore.c_str(),
        screenW / 2 - MeasureText(finalScore.c_str(), 40) / 2,
        screenH / 2,
        40,
        RAYWHITE);
}

void MemoryGame::DrawWin()
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    // Title
    DrawText("YOU WIN!",
        screenW / 2 - MeasureText("YOU WIN!", 70) / 2,
        screenH / 2 - 170,
        70,
        GREEN);

    // Animated Score (uses displayedScore)
    std::string scoreText = "Final Score: " + std::to_string(displayedScore);
    DrawText(scoreText.c_str(),
        screenW / 2 - MeasureText(scoreText.c_str(), 45) / 2,
        screenH / 2 - 40,
        45,
        GOLD);

    // Time
    std::string timeText = "Time Taken: " + std::to_string((int)finalTime) + " seconds";
    DrawText(timeText.c_str(),
        screenW / 2 - MeasureText(timeText.c_str(), 35) / 2,
        screenH / 2 + 30,
        35,
        RAYWHITE);

    // Time Bonus (if you added it)
    std::string bonusText = "Time Bonus: +" + std::to_string(timeBonus);
    DrawText(bonusText.c_str(),
        screenW / 2 - MeasureText(bonusText.c_str(), 30) / 2,
        screenH / 2 + 80,
        30,
        YELLOW);

    // Return instruction (only after animation finishes)
    if (!scoreAnimating)
    {
        DrawText("Click to return to Menu",
            screenW / 2 - MeasureText("Click to return to Menu", 25) / 2,
            screenH / 2 + 130,
            25,
            GRAY);
    }
}

void MemoryGame::DrawPause()
{
    //// draw board behind pause
    //DrawPlay();

    // dark overlay
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));

    DrawText("PAUSED",
        GetScreenWidth() / 2 - MeasureText("PAUSED", 60) / 2,
        GetScreenHeight() / 2 - 50,
        60,
        YELLOW);

    DrawText("Click to Resume",
        GetScreenWidth() / 2 - MeasureText("Click to Resume", 25) / 2,
        GetScreenHeight() / 2 + 30,
        25,
        RAYWHITE);
}