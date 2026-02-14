#include "BallBounce.h"
#include "Wall.h"
#include "Ball.h"
#include "raylib.h" 
#include <iostream>
#include <string>
#include <algorithm>

// Helper function for clamping values
float ClampValue(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void BallBounce::Main()
{
    std::cout << "Test" << std::endl;

    Start();

    InitWindow(2300, 1400, "Spirograph Simulator");
    SetTargetFPS(60);

    InitializeUI();

    while (!WindowShouldClose())
    {
        HandleUIInput();

        BeginDrawing();
        ClearBackground(currentBgColor);


        DrawUI();

        EndDrawing();
    }

    CloseWindow();
}

void BallBounce::Start()
{
    Ball blueBall = Ball{ Vector2 {200, 200}, 25, BLUE };
    Ball red = Ball{ Vector2 {200, 40}, 25, RED };

    balls.push_back(blueBall);
    balls.push_back(red);

    Wall left = Wall(0, 0, 10, 1400, VERTICAL);
    walls.push_back(left);

    Wall right = Wall(1790, 0, 10, 1400, VERTICAL);
    walls.push_back(right);

    Wall top = Wall(0, 0, 1800, 10, HORIZONTAL);
    walls.push_back(top);

    Wall bottom = Wall(0, 1390, 1800, 10, HORIZONTAL);
    walls.push_back(bottom);

}

void BallBounce::InitializeUI()
{
    float buttonSize = 30;
    float spacing = 5;

    // === LEFT SIDE: Color Palette (shared for both pen and background) ===
    float leftStartX = 20;
    float leftStartY = 80; // Leave room for mode buttons

    // Define color palette (10 rows x 10 columns)
    std::vector<std::vector<Color>> colorPalette = {
        // Row 1: Grayscale
        {
            {0, 0, 0, 255}, {51, 51, 51, 255}, {102, 102, 102, 255},
            {153, 153, 153, 255}, {178, 178, 178, 255}, {204, 204, 204, 255},
            {229, 229, 229, 255}, {242, 242, 242, 255}, {255, 255, 255, 255},
            {255, 235, 238, 255}
        },
        // Row 2: Vivid colors
        {
            {204, 0, 0, 255}, {255, 0, 0, 255}, {255, 153, 0, 255},
            {255, 255, 0, 255}, {0, 255, 0, 255}, {0, 255, 204, 255},
            {0, 204, 255, 255}, {0, 0, 255, 255}, {153, 0, 255, 255},
            {255, 0, 255, 255}
        },
        // Row 3: Pastels
        {
            {255, 204, 203, 255}, {255, 179, 186, 255}, {255, 223, 186, 255},
            {255, 250, 205, 255}, {220, 255, 220, 255}, {204, 255, 229, 255},
            {204, 229, 255, 255}, {186, 186, 255, 255}, {220, 204, 255, 255},
            {255, 204, 255, 255}
        },
        // Row 4: Light saturated
        {
            {230, 138, 115, 255}, {255, 153, 153, 255}, {255, 204, 153, 255},
            {255, 255, 153, 255}, {204, 255, 153, 255}, {153, 255, 204, 255},
            {153, 204, 255, 255}, {153, 153, 255, 255}, {204, 153, 255, 255},
            {255, 153, 255, 255}
        },
        // Row 5: Medium saturated
        {
            {204, 102, 102, 255}, {255, 102, 102, 255}, {255, 153, 102, 255},
            {255, 255, 102, 255}, {102, 204, 102, 255}, {102, 204, 153, 255},
            {102, 153, 204, 255}, {102, 102, 204, 255}, {153, 102, 204, 255},
            {204, 102, 204, 255}
        },
        // Row 6: Saturated
        {
            {153, 51, 51, 255}, {204, 51, 51, 255}, {204, 102, 0, 255},
            {204, 204, 0, 255}, {51, 153, 51, 255}, {51, 153, 102, 255},
            {51, 102, 153, 255}, {51, 51, 153, 255}, {102, 51, 153, 255},
            {153, 51, 153, 255}
        },
        // Row 7: Rich colors
        {
            {153, 0, 0, 255}, {204, 0, 0, 255}, {153, 76, 0, 255},
            {153, 153, 0, 255}, {0, 153, 0, 255}, {0, 153, 76, 255},
            {0, 76, 153, 255}, {0, 0, 153, 255}, {76, 0, 153, 255},
            {153, 0, 153, 255}
        },
        // Row 8: Dark saturated
        {
            {102, 0, 0, 255}, {153, 0, 0, 255}, {102, 51, 0, 255},
            {102, 102, 0, 255}, {0, 102, 0, 255}, {0, 102, 51, 255},
            {0, 51, 102, 255}, {0, 0, 102, 255}, {51, 0, 102, 255},
            {102, 0, 102, 255}
        },
        // Row 9: Very dark
        {
            {51, 0, 0, 255}, {76, 0, 0, 255}, {76, 38, 0, 255},
            {76, 76, 0, 255}, {0, 76, 0, 255}, {0, 76, 38, 255},
            {0, 38, 76, 255}, {0, 0, 76, 255}, {38, 0, 76, 255},
            {76, 0, 76, 255}
        },
        // Row 10: Extra dark
        {
            {38, 0, 0, 255}, {51, 25, 0, 255}, {51, 51, 0, 255},
            {25, 51, 0, 255}, {0, 51, 0, 255}, {0, 51, 51, 255},
            {0, 25, 51, 255}, {0, 0, 51, 255}, {25, 0, 51, 255},
            {51, 0, 51, 255}
        }
    };

    // Create color buttons (shared palette)
    for (int row = 0; row < colorPalette.size(); row++) {
        for (int col = 0; col < colorPalette[row].size(); col++) {
            ColorButton btn;
            btn.rect = {
                leftStartX + col * (buttonSize + spacing),
                leftStartY + row * (buttonSize + spacing),
                buttonSize,
                buttonSize
            };
            btn.color = colorPalette[row][col];
            colorButtons.push_back(btn);
        }
    }

    uiInitialized = true;
}

void BallBounce::HandleUIInput()
{
    Vector2 mousePos = GetMousePosition();

    // Mode toggle buttons
    Rectangle penModeBtn = { 20, 20, 160, 45 };
    Rectangle bgModeBtn = { 190, 20, 160, 45 };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Handle mode selection
        if (CheckCollisionPointRec(mousePos, penModeBtn)) {
            currentMode = PEN_MODE;
        }
        if (CheckCollisionPointRec(mousePos, bgModeBtn)) {
            currentMode = BACKGROUND_MODE;
        }

        // Handle color button clicks (apply to current mode)
        for (auto& btn : colorButtons) {
            if (CheckCollisionPointRec(mousePos, btn.rect)) {
                if (currentMode == PEN_MODE) {
                    currentPenColor = btn.color;
                }
                else {
                    currentBgColor = btn.color;
                }
            }
        }

        // Handle toggle buttons
        for (auto& btn : toggleButtons) {
            if (CheckCollisionPointRec(mousePos, btn.rect)) {
                *btn.state = !(*btn.state);
            }
        }
    }

    // Handle slider dragging
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        for (auto& slider : sliders) {
            if (CheckCollisionPointRec(mousePos, slider.rect)) {
                slider.dragging = true;
            }
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        for (auto& slider : sliders) {
            slider.dragging = false;
        }
    }

    // Update slider values
    for (auto& slider : sliders) {
        if (slider.dragging) {
            float normalizedPos = (mousePos.x - slider.rect.x) / slider.rect.width;
            normalizedPos = ClampValue(normalizedPos, 0.0f, 1.0f);
            *slider.value = slider.minValue + normalizedPos * (slider.maxValue - slider.minValue);
        }
    }
}

bool BallBounce::ClearButtonPressed()
{
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Rectangle clearBtn = { 20, 1400 - 70, 120, 50 };
        if (CheckCollisionPointRec(mousePos, clearBtn)) {
            return true;
        }
    }
    return false;
}

void BallBounce::DrawUI()
{
    // === LEFT SIDE UI ===

    // Mode toggle buttons
    Rectangle penModeBtn = { 20, 20, 160, 45 };
    Rectangle bgModeBtn = { 190, 20, 160, 45 };

    // Pen mode button
    Color penBtnColor = (currentMode == PEN_MODE) ? DARKBLUE : LIGHTGRAY;
    DrawRectangleRec(penModeBtn, penBtnColor);
    DrawRectangleLinesEx(penModeBtn, 2, BLACK);
    DrawText("PEN COLOR", penModeBtn.x + 20, penModeBtn.y + 12, 20,
        (currentMode == PEN_MODE) ? WHITE : BLACK);

    // Background mode button
    Color bgBtnColor = (currentMode == BACKGROUND_MODE) ? DARKBLUE : LIGHTGRAY;
    DrawRectangleRec(bgModeBtn, bgBtnColor);
    DrawRectangleLinesEx(bgModeBtn, 2, BLACK);
    DrawText("BG COLOR", bgModeBtn.x + 25, bgModeBtn.y + 12, 20,
        (currentMode == BACKGROUND_MODE) ? WHITE : BLACK);

    // Draw color buttons
    for (const auto& btn : colorButtons) {
        DrawRectangleRec(btn.rect, btn.color);

        // Highlight selected color based on current mode
        Color targetColor = (currentMode == PEN_MODE) ? currentPenColor : currentBgColor;

        if (btn.color.r == targetColor.r &&
            btn.color.g == targetColor.g &&
            btn.color.b == targetColor.b &&
            btn.color.a == targetColor.a) {
            DrawRectangleLinesEx(btn.rect, 3, WHITE);
            DrawRectangleLinesEx({ btn.rect.x - 1, btn.rect.y - 1,
                                 btn.rect.width + 2, btn.rect.height + 2 }, 1, BLACK);
        }
        else {
            DrawRectangleLinesEx(btn.rect, 1, DARKGRAY);
        }
    }

    // Current color preview boxes
    float previewSize = 40;
    float previewY = 80 + 30 * 10 + 5 * 9 + 20; // Below color palette

    DrawText("Current Pen:", 20, previewY, 18, BLACK);
    DrawRectangle(150, previewY - 5, previewSize, previewSize, currentPenColor);
    DrawRectangleLinesEx({ 150, previewY - 5, previewSize, previewSize }, 2, BLACK);

    // Draw sliders (LEFT SIDE - below previews)
    for (const auto& slider : sliders) {
        // Label
        DrawText(slider.label, slider.rect.x, slider.rect.y - 25, 18, BLACK);

        // Slider track
        DrawRectangleRec(slider.rect, LIGHTGRAY);
        DrawRectangleLinesEx(slider.rect, 1, DARKGRAY);

        // Slider value position
        float normalizedValue = (*slider.value - slider.minValue) / (slider.maxValue - slider.minValue);
        float handleX = slider.rect.x + normalizedValue * slider.rect.width;

        // Slider handle
        DrawCircle(handleX, slider.rect.y + slider.rect.height / 2, 12, DARKGRAY);
        DrawCircle(handleX, slider.rect.y + slider.rect.height / 2, 10, WHITE);

        // Value text
        char valueText[32];
        if (slider.label[0] == 'S') { // Speed slider
            snprintf(valueText, sizeof(valueText), "%.2fx", *slider.value);
        }
        else {
            snprintf(valueText, sizeof(valueText), "%d", (int)*slider.value);
        }
        DrawText(valueText, slider.rect.x + slider.rect.width + 10,
            slider.rect.y, 18, BLACK);
    }

    // Draw control buttons (LEFT BOTTOM)
    Rectangle clearBtn = { 20, 1400 - 70, 120, 50 };
    Rectangle pauseBtn = { 150, 1400 - 70, 120, 50 };

    // Clear button
    DrawRectangleRec(clearBtn, DARKGRAY);
    DrawRectangleLinesEx(clearBtn, 2, BLACK);
    DrawText("CLEAR", clearBtn.x + 25, clearBtn.y + 15, 20, WHITE);

    // Pause/Play button
    DrawRectangleRec(pauseBtn, isPaused ? GREEN : RED);
    DrawRectangleLinesEx(pauseBtn, 2, BLACK);
    const char* pauseText = isPaused ? "PLAY" : "PAUSE";
    DrawText(pauseText, pauseBtn.x + 25, pauseBtn.y + 15, 20, WHITE);
}

void BallBounce::SpirographEffect()
{
    static float angle = 0.0f;
    static float R = 600;
    static float r = 220;
    static float h = 150;
    static float speed = 1.0f;
    static float lineThickness = 2.0f;
    static Vector2 center = { 1150, 700 }; // Centered in 2300x1400
    static std::vector<Vector2> penTrail;
    static std::vector<Color> colorTrail; // Store colors for each point

    // Initialize sliders only once
    if (sliders.empty() && uiInitialized) {
        float previewY = 80 + 30 * 10 + 5 * 9 + 20; // Below color palette
        float sliderY = previewY + 110; // Below preview boxes
        float sliderSpacing = 70;

        sliders = {
            {{20, sliderY, 200, 20}, &R, 100, 800, "Big Ring (R)"},
            {{20, sliderY + sliderSpacing, 200, 20}, &r, 50, 400, "Small Gear (r)"},
            {{20, sliderY + sliderSpacing * 2, 200, 20}, &h, 50, 300, "Pen Offset (h)"},
            {{20, sliderY + sliderSpacing * 3, 200, 20}, &lineThickness, 1, 10, "Line Thickness"},
            {{20, sliderY + sliderSpacing * 4, 200, 20}, &speed, 0, 5, "Speed"}
        };

        // Initialize toggle buttons
        toggleButtons = {
            {{150, 1400 - 70, 120, 50}, "PAUSE", &isPaused}
        };
    }

    // Check if parameters changed (except speed and line thickness)
    static float lastR = R;
    static float lastR2 = r;
    static float lastH = h;
    if (R != lastR || r != lastR2 || h != lastH) {
        penTrail.clear();
        colorTrail.clear();
        angle = 0.0f;
        lastR = R;
        lastR2 = r;
        lastH = h;
    }

    // Check for clear button
    if (ClearButtonPressed()) {
        penTrail.clear();
        colorTrail.clear();
        angle = 0.0f;
    }

    // Only update if not paused
    if (!isPaused) {
        // Compute current spirograph point
        float t = angle;
        Vector2 pen;
        pen.x = center.x + (R - r) * cos(t) + h * cos(((R - r) / r) * t);
        pen.y = center.y + (R - r) * sin(t) - h * sin(((R - r) / r) * t);

        Vector2 currentPos = { pen.x, pen.y };
        penTrail.push_back(currentPos);
        colorTrail.push_back(currentPenColor);

        const int maxBallAmount = 30000;
        if ((int)penTrail.size() > maxBallAmount) {
            penTrail.erase(penTrail.begin());
            colorTrail.erase(colorTrail.begin());
        }

        angle += 0.02f * speed;
    }

    // Draw trail as connected lines
    for (int i = 0; i < (int)penTrail.size() - 1; i++) {
        DrawLineEx(penTrail[i], penTrail[i + 1], lineThickness, colorTrail[i]);
    }

    // Draw current position indicator
    if (!penTrail.empty()) {
        DrawCircleV(penTrail.back(), 8.0f, GREEN);
    }
}

void BallBounce::Update()
{
    for (int i = 0; i < walls.size(); i++)
        walls[i].Draw();

    for (int i = 0; i < balls.size(); i++)
    {
        balls[i].Update();
        for (int w = 0; w < walls.size(); w++)
            balls[i].CheckAgainstWall(walls[w]);

        for (int j = i + 1; j < balls.size(); j++)
        {
            if (balls[i].collideWith &&
                balls[j].collideWith &&
                CheckCollisionOnBalls(balls[i], balls[j]))
            {
                balls[i].collideWith = false;
                balls[j].collideWith = false;

                balls[i].timeToCollide = 0;
                balls[j].timeToCollide = 0;

                balls[i].ChangeDirection();
                balls[j].ChangeDirection();

                if (balls.size() < MAX_BALLS)
                {
                    float cenX = (balls[i].center.x + balls[j].center.x) * 0.5f;
                    float cenY = (balls[i].center.y + balls[j].center.y) * 0.5f;

                    balls.emplace_back(Vector2{ cenX, cenY }, 25, YELLOW, false);
                }
            }
        }
    }
}

void BallBounce::PendulumEffect()
{
    static float T = 100.0f;
    static float L = 600;
    static float G = 10.0f;

    static Vector2 origin = { 600, 500 };

    static float angle = 2.0f;
    static float angularVelocity = 0.0f;

    static Vector2 prevPos = origin;

    float angularAcceleration = (-G / L) * sin(angle);
    angularVelocity += angularAcceleration;
    angle += angularVelocity;
    float x = origin.x + L * sin(angle);
    float y = origin.y + L * cos(angle);
    Vector2 currentPos = { x, y };

    DrawCircleV(currentPos, 50.0f, RED);
    prevPos = currentPos;
}

void BallBounce::DoublePendulumEffect()
{
    float G = .5f;
    static Vector2 origin = { 600, 300 };
    static float L1 = 200.0f;
    static float L2 = 200.0f;
    static float m1 = 10.0f;
    static float m2 = 10.0f;
    static float angle1 = 3.14f / 2;
    static float angle2 = 3.14f / 2;
    static float angularVelocity1 = 0.0f;
    static float angularVelocity2 = 0.0f;
    static Vector2 prevPos1 = origin;
    static Vector2 prevPos2 = origin;

    float num1 = -G * (2 * m1 + m2) * sin(angle1);
    float num2 = -m2 * G * sin(angle1 - 2 * angle2);

    float num3 = -2 * sin(angle1 - angle2) * m2;
    float num4 = angularVelocity2 * angularVelocity2 * L2 + angularVelocity1 * angularVelocity1 * L1 * cos(angle1 - angle2);
    float den = L1 * (2 * m1 + m2 - m2 * cos(2 * angle1 - 2 * angle2));
    float angularAcceleration1 = (num1 + num2 + num3 * num4) / den;
    float num5 = 2 * sin(angle1 - angle2);

    float num6 = (angularVelocity1 * angularVelocity1 * L1 * (m1 + m2));
    float num7 = G * (m1 + m2) * cos(angle1);
    float num8 = angularVelocity2 * angularVelocity2 * L2 * m2 * cos(angle1 - angle2);
    float den2 = L2 * (2 * m1 + m2 - m2 * cos(2 * angle1 - 2 * angle2));
    float angularAcceleration2 = (num5 * (num6 + num7 + num8)) / den2;
    angularVelocity1 += angularAcceleration1;
    angularVelocity2 += angularAcceleration2;
    angle1 += angularVelocity1;
    angle2 += angularVelocity2;
    float x1 = origin.x + L1 * sin(angle1);
    float y1 = origin.y + L1 * cos(angle1);
    Vector2 currentPos1 = { x1, y1 };
    float x2 = x1 + L2 * sin(angle2);
    float y2 = y1 + L2 * cos(angle2);
    Vector2 currentPos2 = { x2, y2 };
    DrawCircleV(currentPos1, 20.0f, BLUE);
    DrawCircleV(currentPos2, 20.0f, GREEN);

    prevPos1 = currentPos1;
    prevPos2 = currentPos2;
}