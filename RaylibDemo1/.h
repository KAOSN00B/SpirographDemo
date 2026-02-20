#pragma once
#include "Ball.h"
#include "raylib.h"
#include "Wall.h"
#include <vector>

struct Pendulum
{
    float length;
    float angle;
    float angularVelocity;
    float angularAcceleration;
    Vector2 origin;
};

class BallBounce
{
public:
#define MAX_BALLS 40
    std::vector<Wall> walls;
    std::vector<Ball> balls;
    void Main();
    void Start();
    void Update();
    void SpirographEffect();
    void PendulumEffect();
    void DoublePendulumEffect();
    bool CheckCollisionOnBalls(Ball ball1, Ball ball2)
    {
        if (!ball1.collideWith || !ball2.collideWith)
            return false;
        if (CheckCollisionCircles(ball1.center, ball1.radius, ball2.center, ball2.radius))
            return true;
        return false;
    }

private:
    // Spirograph UI controls
    struct ColorButton {
        Rectangle rect;
        Color color;
    };

    struct Slider {
        Rectangle rect;
        float* value;
        float minValue;
        float maxValue;
        const char* label;
        bool dragging = false;
    };

    struct ToggleButton {
        Rectangle rect;
        const char* label;
        bool* state;
    };

    enum ColorMode {
        PEN_MODE,
        BACKGROUND_MODE
    };

    std::vector<ColorButton> colorButtons;
    std::vector<Slider> sliders;
    std::vector<ToggleButton> toggleButtons;

    Color currentPenColor = BLACK;
    Color currentBgColor = GRAY;
    ColorMode currentMode = PEN_MODE;
    bool isPaused = false;
    bool uiInitialized = false;

    void InitializeUI();
    void HandleUIInput();
    void DrawUI();
    bool ClearButtonPressed();
};