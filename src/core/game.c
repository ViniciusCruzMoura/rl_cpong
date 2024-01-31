#include "game.h"

void InitGame() 
{
    game.currentScreen = LOGO;
    game.screenScale = 3.0;
    game.screenWidth = WIN_RES_W*game.screenScale;
    game.screenHeight = WIN_RES_H*game.screenScale;
    game.fullscreen = false; //IsWindowFullscreen()
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(game.screenWidth, game.screenHeight, "raylib - CPong");
    if (game.fullscreen) {
        game.screenWidth = GetMonitorWidth(GetCurrentMonitor());
        game.screenHeight = GetMonitorHeight(GetCurrentMonitor());
        game.screenScale = game.screenHeight/WIN_RES_H;
        // game.screenScale = game.screenWidth/WIN_RES_W;
        SetWindowSize(game.screenWidth, game.screenHeight);
        ToggleFullscreen();
    }

    game.gamePaused = false;  // Game paused state toggle
    game.gameOver = false;
    game.elementPositionY = -128;
    game.framesCounter = 0;  // General pourpose frames counter
    
    InitPlayer(&game.player, game.screenWidth - 50, game.screenHeight / 2, game.screenScale);

    InitBall(&game.ball, game.screenScale);

    InitMenu(&game.menu, game.screenWidth/2, game.screenHeight/2.5f);

    // Textures loading
    game.texLogo = LoadTexture("../assets/raylib_logo.png");
    
    // Sounds loading
    InitAudioDevice();      // Initialize audio device
    game.soundArray[0] = LoadSound("../assets/pong.wav");

    SetTargetFPS(60);
}

void UpdateGame()
{
    switch(game.currentScreen)
    {
        case LOGO: 
        {
            update_logo_screen();
        } break;
        case TITLE: 
        {   
            update_title_screen();
        } break;
        case GAMEPLAY:
        { 
            update_gameplay_screen();
        } break;
        case ENDING: 
        {
            update_ending_screen();
        } break;
        default: break;
    }
}

void DrawGame()
{
    BeginDrawing();

        // ClearBackground(RAYWHITE);
        ClearBackground(BLACK);
        
        switch(game.currentScreen) 
        {
            case LOGO: 
            {
                draw_logo_screen();
            } break;
            case TITLE: 
            {
                draw_title_screen();                
            } break;
            case GAMEPLAY:
            {
                draw_gameplay_screen();   
            } break;
            case ENDING: 
            {
                draw_ending_screen();                
            } break;
            default: break;
        }
         
        char buf[1024];
        snprintf(
            buf, 1024, 
            "Debug:\n" \
            "- GetMonitorWidth: (%d)\n" \
            "- GetMonitorHeight: (%d)\n" \
            "- game.currentScreen (%d)\n" \
            "- game.framesCounter (%d)\n" \
            "- game.elementPositionY (%d)\n" \
            "- game.winner (%s)\n"
            , GetMonitorWidth(GetCurrentMonitor())
            , GetMonitorHeight(GetCurrentMonitor())
            , game.currentScreen
            , game.framesCounter
            , game.elementPositionY
            , game.winner
        );
        /** */
        int text_size = 10;
        // DrawRectangle(0, 0, MeasureText(buf, text_size), GetScreenHeight()/2, Fade(SKYBLUE, 0.4f));
        // DrawRectangleLines(0, 0, MeasureText(buf, text_size), GetScreenHeight()/2, BLUE);
        DrawText(TextFormat(buf), 0, 0, text_size, WHITE);
        // TraceLog(LOG_INFO, buf);
        
        // const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J"; //clearScreen
        // write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);    //clearScreen
        // fprintf(stderr, "testing debug print.\n");
        // printf("\r%s\n", buf);
        
    EndDrawing();
}

void UnloadGame()
{
    // Unload textures
    UnloadTexture(game.texLogo);        // Unload texture from GPU memory (VRAM)
    UnloadSound(game.soundArray[0]);        // Unload source sound data
    CloseAudioDevice();     // Close audio device
}