#include "raylib.h"

int main()
{
    // Screen configuration
    const int height = 480;
    const int width  = 640;
    const int target_fps = 60;

    // Ball variables
    int   bxPos      = width  / 2;
    int   byPos      = 20;
    float bxVel      = 6;
    float byVel      = 6;
    const int radius = 20;

    // Platform variables
    // Start with the platform at the centre bottom of the screen.
    int pWidth      = 150;
    int pHeight     = 15;
    int pxPos       = (width - pWidth) / 2;
    const int pyPos = height - pHeight - 15;

    int pSpeed      = 10;

    // Score variables
    int currentScore  = 0;
    int highScore     = 0;
    
    // Initialize the window    
    InitWindow(width, height, "");
    SetWindowState(FLAG_VSYNC_HINT); // Helps prevent screen tearing
    SetTargetFPS(target_fps);

    while (!WindowShouldClose()){
        // Update the gamestate
        
        bxPos += bxVel;
        byPos += byVel;

        // Accelerate the ball
        bxVel *= 1.0001;
        byVel *= 1.0001;

        // Platform movement
        if (IsKeyDown(KEY_LEFT)){
            pxPos -= pSpeed;
        } else if (IsKeyDown(KEY_RIGHT)){
            pxPos += pSpeed;
        }

        // Check for deaths
        if (byPos >= height){
            DrawText("GAME OVER", width * 0.3, height * 0.2 , 30, RED);
            if (currentScore > highScore){
                highScore = currentScore;
            }

            // reset the ball position and velocities
            bxPos = width / 2;
            byPos = 20;
            bxVel = 3;
            byVel = 3;
            currentScore = 0;
        }

        // Check for collisions with the top wall
        if (byPos <= 0 ){
            byVel *= -1;
        }
    
        // Check for collisions with the left and right walls
        if (bxPos <= 0 || bxPos >= width){
            bxVel *= -1;
        }
        
        // Check for collisions between the ball and the platform
        // 1. Check that the center of the ball is within the x-range of the platform
        // 2. Check that the y pos of the ball is within the range of the platform

        // FIXME this is not technically correct since it doesn't account for hitting the edge of the platform!
        if (bxPos          >= pxPos &&
            pxPos + pWidth >= bxPos &&
            byPos + radius >= pyPos)
        {
            byVel *= -1;
            currentScore++;
        }

        // Draw a frame
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw the ball and the platform.        
        DrawCircle(bxPos, byPos, radius, RED);
        DrawRectangle(pxPos, pyPos, pWidth, pHeight, BLUE);

        // Draw the UI
        DrawFPS(10, 20);
        DrawText(TextFormat("Current Score: %d", currentScore), 40, 40, 20, BLUE);
        DrawText(TextFormat("High Score:    %d", highScore), 40, 60, 20, RED);

        EndDrawing();
    }
    return 0;
}