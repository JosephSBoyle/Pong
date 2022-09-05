#include "raylib.h"

// Screen configuration
const int FRAME_HEIGHT = 480;
const int FRAME_WIDTH  = 640;
const int TARGET_FPS = 60;
// Ball configuration
const int DEFAULT_BALL_X_POS = FRAME_WIDTH / 2;
const int DEFAULT_BALL_Y_POS = 20;
// Difficulty
const int DEFAULT_BALL_X_VEL = 6;
const int DEFAULT_BALL_Y_VEL = 6;


int main()
{
    // Ball variables
    int   bxPos      = DEFAULT_BALL_X_POS;
    int   byPos      = DEFAULT_BALL_Y_POS;

    float bxVel      = DEFAULT_BALL_X_VEL;
    float byVel      = DEFAULT_BALL_Y_VEL;
    const int radius = 20;

    // Platform variables
    // Start with the platform at the centre bottom of the screen.
    int pWidth      = 150;
    int pHeight     = 15;
    int pxPos       = (FRAME_WIDTH - pWidth) / 2;
    const int pyPos = FRAME_HEIGHT - pHeight - 15;

    int pSpeed      = 10;

    // Score variables
    int currentScore  = 0;
    int highScore     = 0;
    
    // Initialize the window    
    InitWindow(FRAME_WIDTH, FRAME_HEIGHT, "");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()){
        // Update the gamestate
        
        // Move the ball
        bxPos += bxVel;
        byPos += byVel;

        // Accelerate the ball
        bxVel *= 1.0001;
        byVel *= 1.0001;

        // Move the platform
        if (IsKeyDown(KEY_LEFT)){
            pxPos -= pSpeed;
        } else if (IsKeyDown(KEY_RIGHT)){
            pxPos += pSpeed;
        }

        // Check for deaths
        if (byPos >= FRAME_HEIGHT){
            if (currentScore > highScore){
                highScore = currentScore;
            }
            // reset the ball position and velocities
            bxPos = FRAME_WIDTH / 2;
            byPos = DEFAULT_BALL_Y_POS;
            bxVel = DEFAULT_BALL_X_VEL;
            byVel = DEFAULT_BALL_Y_VEL;
            currentScore = 0;
        }

        // Check for collisions with the top wall
        if (byPos <= 0 ){
            byVel *= -1;
        }
    
        // Check for collisions with the left and right walls
        if (bxPos <= 0 || bxPos >= FRAME_WIDTH){
            bxVel *= -1;
        }
        
        // Check for collisions between the ball and the platform
        // 1. Check that the center of the ball is within the x-range of the platform
        // 2. Check that the y pos of the ball is within the range of the platform

        // FIXME this is crude and can be improved.
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

        // Draw the UI in the top left hand corner of the screen
        DrawFPS(10, 20);
        DrawText(TextFormat("Current Score: %d", currentScore), 40, 40, 20, BLUE);
        DrawText(TextFormat("High Score: %d", highScore), 40, 60, 20, RED);
        EndDrawing();
    }
    return 0;
}