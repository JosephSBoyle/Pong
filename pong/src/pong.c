/*******************************************************************************************
*
*   raylib [other] example - Singleplayer Pong
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example contributed by Joseph S. Boyle (@JosephSBoyle) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022 Joseph S. Boyle (@JosephSBoyle)
*
********************************************************************************************/

#include "raylib.h"

#define SCREEN_WIDTH            800
#define SCREEN_HEIGHT           450

#define BALL_RADIUS             20
#define BALL_Y_INITIAL          20
#define BALL_X_INITIAL          SCREEN_WIDTH / 2
#define BALL_XVEL_INITIAL       10
#define BALL_YVEL_INITIAL       6
#define BALL_ACCEL_FACTOR       1.0001

#define PLAT_WIDTH              150
#define PLAT_HEIGHT             15
#define PLAT_X_INITIAL          (SCREEN_WIDTH - PLAT_WIDTH) / 2
#define PLAT_Y_INITIAL          SCREEN_HEIGHT - 50
#define PLAT_Y                  SCREEN_HEIGHT - PLAT_HEIGHT
#define PLAT_SPEED_INITIAL      10

#define PLAT_LEFT_BOUND         0
#define PLAT_RIGHT_BOUND        SCREEN_WIDTH - PLAT_WIDTH


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Singleplayer Pong");

    // Initialize the ball's position and velocity.
    Vector2  ball  = {BALL_X_INITIAL, BALL_Y_INITIAL};
    int xvel_ball = GetRandomValue(-BALL_XVEL_INITIAL, BALL_XVEL_INITIAL);
    int yvel_ball = BALL_YVEL_INITIAL;
    
    // Initialize the platform at the bottom centre of the screen.
    Rectangle platform = {PLAT_X_INITIAL, PLAT_Y_INITIAL, PLAT_WIDTH, PLAT_HEIGHT};
    int speed_platform = PLAT_SPEED_INITIAL;

    int  score     = 0;
    int  hi_score  = 0;
    bool game_over = false;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if (game_over) {
            DrawText(TextFormat("GAME OVER"), 280, 100, 40, RED);
            DrawText(TextFormat("Press space to continue\n  Press escape to exit "), 275, 200, 20, BLUE);

            if (IsKeyPressed(KEY_SPACE)) {
                // Restart
                game_over = false;

                xvel_ball = GetRandomValue(-BALL_XVEL_INITIAL, BALL_XVEL_INITIAL);
                yvel_ball = BALL_YVEL_INITIAL;
            }
        }
        
        // Move the platform whilst ensuring it doesn't leave the screen's borders
        if (IsKeyDown(KEY_LEFT)  && platform.x > PLAT_LEFT_BOUND)  platform.x -= speed_platform;
        if (IsKeyDown(KEY_RIGHT) && platform.x < PLAT_RIGHT_BOUND) platform.x += speed_platform;

        if (ball.y >= SCREEN_HEIGHT) {
            game_over = true;
            if (score > hi_score) {
                hi_score = score;
            }
                // reset the ball & current score
                ball.x = BALL_X_INITIAL;
                ball.y = BALL_Y_INITIAL;

                xvel_ball = 0;
                yvel_ball = 0;
                score = 0;
        }

        // Check for vertical collisions: between the ball and either the top wall or the platform 
        if (ball.y <= 0 || CheckCollisionCircleRec(ball, BALL_RADIUS, platform))
            yvel_ball *= -1;

        // Check for horizontal collisions: between the left and right edges of the screen.
        if (ball.x <= 0 || ball.x >= SCREEN_WIDTH)
            xvel_ball *= -1;

        // Translate the ball in space.
        ball.x += xvel_ball;
        ball.y += yvel_ball;

        xvel_ball *= BALL_ACCEL_FACTOR;
        yvel_ball *= BALL_ACCEL_FACTOR;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();
        ClearBackground(WHITE);

        // Draw the ball and the platform.
        DrawCircle(ball.x, ball.y, BALL_RADIUS, RED);
        DrawRectangle(platform.x, platform.y, platform.width, platform.height, BLUE);

        // Draw the UI in the top left hand corner of the screen
        DrawFPS(40, 20);
        DrawText(TextFormat("Score:    %d", score), 40, 40, 20, BLUE);
        DrawText(TextFormat("Hi Score: %d", hi_score),    40, 60, 20, RED);
        EndDrawing();
        //----------------------------------------------------------------------------------

    }

    // De-initialization
    //----------------------------------------------------------------------------------

    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------------------------------
    return 0;
}