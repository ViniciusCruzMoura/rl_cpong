#include "raylib.h"
#include <string.h>


#define TILE_MAP_WIDTH  20
#define TILE_MAP_HEIGHT 12


typedef enum GameScreen { LOGO = 0, TITLE, CREDITS, GAMEPLAY, ENDING } GameScreen;

typedef struct Ball {
    float radius;
    Vector2 position;
    Vector2 speed;
} Ball;

typedef struct Paddle {
    float speed;
    Rectangle rec;
} Paddle;


int currentScreen = LOGO;
const int TILE_SIZE = 16;
const int TILE_ROUND = 15;  // Used in bitwise operation | TILE_SIZE - 1
float screenScale;
int screenWidth;
int screenHeight;
float delta;
Paddle paddleLeft = { 0 };
Paddle paddleRight = { 0 };
Ball ball = { 0 };
int showRedScreen;
int showGreenScreen;
char winner[32];
int elementPositionY = -128;
int framesCounter = 0;
Texture2D texLogo = { 0 };

Paddle PaddleInit(int x, int y);
Ball BallInit(int x, int y);

void DrawBall(Ball ball);
void DrawPaddle(Paddle paddle);
void DrawVictoryMessage(void);

void InitGame(void);         // Initialize game
void UpdateGame(void);       // Update game (one frame)
void DrawGame(void);         // Draw game (one frame)
void UnloadGame(void);       // Unload game
void UpdateDrawFrame(void);  // Update and Draw (one frame)

int main(void)
{
    screenScale = 3.0;
    screenWidth = TILE_SIZE*TILE_MAP_WIDTH*(int)screenScale;
    screenHeight = TILE_SIZE*TILE_MAP_HEIGHT*(int)screenScale;
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "raylib - CPong");
    
    // Textures loading
    texLogo = LoadTexture("resources/raylib_logo.png");
    InitGame();

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    UnloadGame();         // Unload loaded data (textures, sounds, models...)
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

// Initialize game variables
void InitGame(void) 
{
    paddleLeft = PaddleInit(50, screenHeight / 2);
    paddleRight = PaddleInit(screenWidth - 50, screenHeight / 2);
    ball = BallInit(GetRenderWidth() / 2.0f, GetScreenHeight() / 2.0f);
}

// Update game (one frame)
void UpdateGame(void) 
{    
    switch (currentScreen)
        {
            case LOGO:
            {

            } break;
            case TITLE:
            {

            } break;
            case GAMEPLAY: 
            {
                // Get time since last frame
                delta = GetFrameTime();
                
                ball.position.x += ball.speed.x * delta;
                ball.position.y += ball.speed.y * delta;
                if (ball.position.y < 0) {
                    ball.position.y = 0;
                    ball.speed.y *= -1;
                }
                if (ball.position.y > GetScreenHeight()) {
                    ball.speed.y *= -1;
                }
                
                if (IsKeyDown(KEY_W)) paddleLeft.rec.y -= paddleLeft.speed * delta;
                if (IsKeyDown(KEY_S)) paddleLeft.rec.y += paddleLeft.speed * delta;
                if (IsKeyDown(KEY_UP)) paddleRight.rec.y -= paddleRight.speed * delta;
                if (IsKeyDown(KEY_DOWN)) paddleRight.rec.y += paddleRight.speed * delta;
                
                // IsBallColliding
                if (CheckCollisionCircleRec(ball.position, ball.radius, paddleLeft.rec) && ball.speed.x < 0) {
                    ball.speed.x *= -1.1f;
                    ball.speed.y = (ball.position.y - paddleLeft.rec.y) / (paddleLeft.rec.height / 2) * ball.speed.x;
                }
                if (CheckCollisionCircleRec(ball.position, ball.radius, paddleRight.rec) && ball.speed.x > 0) {
                    ball.speed.x *= -1.1f;
                    ball.speed.y = (ball.position.y - paddleRight.rec.y) / (paddleRight.rec.height / 2) * -ball.speed.x;
                }

                if (ball.position.x < 0) {
                    strcpy(winner, "RIGHT_PADDLE_WIN");
                }
                else if (ball.position.x > GetScreenWidth()) {
                    strcpy(winner, "LEFT_PADDLE_WIN");
                }                
                
                showRedScreen = 0;
                showGreenScreen = 0;
                if (CheckCollisionPointRec(GetMousePosition(), paddleLeft.rec)) {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) showGreenScreen = 1;
                    else showRedScreen = 1;
                }
            } break;
            case CREDITS: 
            {

            } break;
            default: break;
        }
    
}

// Draw game (every frame)
void DrawGame(void) 
{
    BeginDrawing();
        DrawFPS(GetRenderWidth()*0.9, 0);

        ClearBackground(BLACK);

        switch (currentScreen)
        {
            case LOGO:
            {
                // Update LOGO screen
                framesCounter++;
                // Logo moving down logic (animation)
                elementPositionY += 3;
                if (elementPositionY > (screenHeight/3 - 64)) elementPositionY = screenHeight/3 - 64;

                if (framesCounter > 300)
                {
                    framesCounter = 0;
                    currentScreen = TITLE;
                }
                // Draw LOGO screen
                // DrawTexture(texLogo, (screenWidth/2)-((screenWidth/12)*2), elementPositionY, WHITE);

                DrawTexturePro(
                    texLogo,
                    (Rectangle){ 0, 0, texLogo.width, texLogo.height },
                    (Rectangle){ screenWidth/2, screenHeight/2, texLogo.width, texLogo.height },
                    (Vector2){ texLogo.width / 2, texLogo.height / 2 - elementPositionY /4 },
                    0,
                    WHITE
                );
            } break;
            case TITLE:
            {
                currentScreen = GAMEPLAY;
            } break;
            case GAMEPLAY: 
            {
                if (showGreenScreen) ClearBackground(GREEN);
                if (showRedScreen) ClearBackground(RED);
                
                DrawPaddle(paddleLeft);
                DrawPaddle(paddleRight);
                DrawBall(ball);
                
                if (strcmp(winner, "RIGHT_PADDLE_WIN") == 0 || strcmp(winner, "LEFT_PADDLE_WIN") == 0) {
                    currentScreen = CREDITS;
                }
            } break;
            case CREDITS: 
            {
                DrawVictoryMessage();
            } break;
            default: break;
        }        

        // char str1[20] = "Hello ";
        // char str2[] = "World!";
        // strcat(str1, str2);
        // DrawText(str1, 190, 200, 20, LIGHTGRAY);
        
        // char buf[1024];
        // snprintf(buf, 1024, "screen_width: %d\nscreen_height: %d", screenWidth, screenHeight);
        // DrawText(buf, 0, 0, 16, LIGHTGRAY);
        
    EndDrawing();
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

// Unload game variables
void UnloadGame(void)
{
    // Unload textures
    UnloadTexture(texLogo);
}

void DrawBall(Ball ball) 
{
    DrawCircle((int) ball.position.x, (int) ball.position.y, ball.radius, WHITE);
}

void DrawPaddle(Paddle paddle) 
{
    DrawRectangleRec(paddle.rec, WHITE);
}

void DrawVictoryMessage(void)
{
    if (strcmp(winner, "RIGHT_PADDLE_WIN") == 0) {
        char msg[] = "Congrats! The right player win the game!";
        DrawText(
            msg,
            GetScreenWidth()/2.0f - MeasureText(msg, 12*screenScale)/2,
            GetScreenHeight()/4.0f, 
            12*screenScale, 
            LIGHTGRAY
        );
    }
    else if (strcmp(winner, "LEFT_PADDLE_WIN") == 0) {
        char msg[] = "Congrats! The left player win the game!";
        DrawText(
            msg,
            GetScreenWidth()/2.0f - MeasureText(msg, 12*screenScale)/2, 
            GetScreenHeight()/4.0f, 
            12*screenScale, 
            LIGHTGRAY
        );
    }
}

Paddle PaddleInit(int x, int y) 
{
    Paddle paddle;
    paddle.rec.x = x;
    paddle.rec.y = y;
    paddle.rec.width = 5 * screenScale;
    paddle.rec.height = 50 * screenScale;
    paddle.speed = 300 * screenScale;
    return paddle;
}

Ball BallInit(int x, int y) 
{
    Ball ball;
    ball.position.x = x;
    ball.position.y = y;
    ball.speed.x = 100 * screenScale;
    ball.speed.y = 100 * screenScale;
    ball.radius = 3 * screenScale;
    return ball;
}
