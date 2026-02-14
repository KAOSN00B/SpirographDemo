#include "Particles.h"

void Particles::Main()
{
    Start();

    InitWindow(800, 800, "Particles System");
    SetTargetFPS(60);

   

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(Color{ 25, 25, 25 });

        Update();
       
        Draw();
        EndDrawing();
    }

    CloseWindow();
}

void Particles::Start()
{
    for (int p = 0; p < POOL_SIZE; p++)
    {
        pool.push_back(SingleParticle());
    }
}

void Particles::Update()
{    // something between 10 to 19 particles have to be emitted
    // where are they going to be?


     // so how do we amit a particles?
    // have to go to the pool, find as many as 10 - 19 that aren't active and activate them

    if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) return;
    // how many particles we want to emit per frame

    Vector2 pos = GetMousePosition();

    int rate = 10 + rand() % 10; // emit 15

    for (int r = 0; r < rate; r++)
    {
        for (int p = 0; p < pool.size(); p++)
        {
            if (!pool[p].active)
            {
                float ang = (float)(rand() % 360);
                float sp = (float)(1.5f + (rand() % 10) / 10);
                float r = 5 + rand() % 16;
                pool[p].Activate(pos, ang, ORANGE, r, sp); // ang goes into the active for random explosion type effect
                break;
            }
        }
    }

}

void Particles::Draw()
{
    BeginBlendMode(BLEND_MULTIPLIED);
    for (int p = 0; p < POOL_SIZE; p++)
    {
        pool[p].Draw();
    }
}