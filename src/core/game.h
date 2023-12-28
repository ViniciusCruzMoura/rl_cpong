#define WIN_RES_W 256
#define WIN_RES_H 192

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

extern int currentScreen;
// extern const int TILE_SIZE;
// extern const int TILE_ROUND;  // Used in bitwise operation | TILE_SIZE - 1
extern float screenScale;
extern int screenWidth;
extern int screenHeight;
extern float delta;
extern Paddle paddleLeft;
extern Paddle paddleRight;
extern Ball ball;
extern int showRedScreen;
extern int showGreenScreen;
extern char winner[32];
extern int elementPositionY;
extern int framesCounter;
extern Texture2D texLogo;


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