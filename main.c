#include "raylib.h"

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
// Defined map size
#define TILE_MAP_WIDTH  20
#define TILE_MAP_HEIGHT 12

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------
typedef struct Ball {
    float radius;
    Vector2 position;
    Vector2 speed;
} Ball;

typedef struct Paddle {
    float speed;
    Rectangle rec;
} Paddle;

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
//----------------------------------------------------------------------------------
const int TILE_SIZE = 16;
const int TILE_ROUND = 15;  // Used in bitwise operation | TILE_SIZE - 1
float screenScale;
static int screenWidth;
static int screenHeight;
static float delta;
static Paddle paddleLeft = { 0 };
static Paddle paddleRight = { 0 };
static Ball ball = { 0 };

//temp
int showRedScreen;
int showGreenScreen;

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
// Module Functions Declaration (local)
//----------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)


//------------------------------------------------------------------------------------
// Tile Functions Declaration (local)
//------------------------------------------------------------------------------------
static int DrawBall(Ball ball);
static int DrawPaddle(Paddle paddle);
static Paddle PaddleInit(int x, int y);
static Ball BallInit(int x, int y);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    screenScale = 3.0;
    screenWidth = TILE_SIZE*TILE_MAP_WIDTH*(int)screenScale;
    screenHeight = TILE_SIZE*TILE_MAP_HEIGHT*(int)screenScale;
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "raylib - CPong");
    
    InitGame();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------  

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition (local)
//----------------------------------------------------------------------------------
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
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------
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
    // if (ball.position.x < 0) {
        // ball.position.x = 0;
        // ball.speed.x *= -1;
    // }
    // if (ball.position.x > GetScreenWidth()) {
        // ball.speed.x *= -1;
    // }
    
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
    
    // if (paddleLeft.rec.y < 0) paddleLeft.speed = 0;
    // if (paddleLeft.rec.y > GetScreenHeight()-paddleLeft.rec.y/2.6f) paddleLeft.speed = 0;
    
    showRedScreen = 0;
    showGreenScreen = 0;
    if (CheckCollisionPointRec(GetMousePosition(), paddleLeft.rec)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) showGreenScreen = 1;
        else showRedScreen = 1;
    }
    
}

// Draw game (every frame)
void DrawGame(void) 
{
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
        ClearBackground(BLACK);
        if (showGreenScreen) ClearBackground(GREEN);
        if (showRedScreen) ClearBackground(RED);
        
        // Coloca os elementos na tela
        DrawBall(ball);
        DrawPaddle(paddleLeft);
        DrawPaddle(paddleRight);
        
        if (ball.position.x < 0) {
            DrawText(
                "Congrats! The right player win the game!",
                GetScreenHeight()/4.0f, 
                GetScreenHeight()/4.0f, 
                12*screenScale, 
                LIGHTGRAY
            );
        }
        else if (ball.position.x > GetScreenWidth()) {
            DrawText(
                "Congrats! The left player win the game!",
                GetScreenHeight()/4.0f, 
                GetScreenHeight()/4.0f, 
                12*screenScale, 
                LIGHTGRAY
            );
        }
        
        // DrawCircle((int) ball.x, (int) ball.y, ball.radius, WHITE);
        // DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100, WHITE);

        // ClearBackground(RAYWHITE);

        // char str1[20] = "Hello ";
        // char str2[] = "World!";
        // strcat(str1, str2);
        // DrawText(str1, 190, 200, 20, LIGHTGRAY);
        
        // printf("%d\n", GetScreenHeight());
        // printf("%d\n", GetFrameTime());
        
        // char buf[1024];
        // snprintf(buf, 1024, "screen_width: %d\nscreen_height: %d", screenWidth, screenHeight);
        // DrawText(buf, 0, 0, 16, LIGHTGRAY);
        
        DrawFPS(GetRenderWidth()*0.9, 0);
        
    EndDrawing();
    //----------------------------------------------------------------------------------
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
    // TODO: Unload required assets here
}

int DrawBall(Ball ball) 
{
    DrawCircle((int) ball.position.x, (int) ball.position.y, ball.radius, WHITE);
    return 0;
}

int DrawPaddle(Paddle paddle) 
{
    DrawRectangleRec(paddle.rec, WHITE);
    return 0;
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
    ball.speed.x = 150 * screenScale;
    ball.speed.y = 150 * screenScale;
    ball.radius = 3 * screenScale;
    return ball;
}

//----------------------------------------------------------------------------------
// Global Functions Definition (used by several modules)
//----------------------------------------------------------------------------------

