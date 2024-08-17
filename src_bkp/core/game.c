#include "game.h"

void InitGame() {
    SetInitialScreenParams();
    SetWindowConfig();
    SetFullscreenMode();
    InitializeGameElements();
    LoadAssets();
    LoadSounds();
    ConfigureFrameRate();
}

void UpdateGame()
{
    switch (game.currentScreen) {
        case LOGO: 
            UpdateLogoScreen();
            break;
        case TITLE: 
            UpdateTitleScreen();
            break;
        case GAMEPLAY:
            UpdateGameplayScreen();
            break;
        case ENDING: 
            UpdateEndingScreen();
            break;
        default: 
            break;
    }
}

void DrawGame()
{
    BeginDrawing();

        // ClearBackground(RAYWHITE);
        ClearBackground(BLACK);
        
        switch(game.currentScreen) {
            case LOGO:
                DrawLogoScreen();
                break;
            case TITLE:
                DrawTitleScreen();
                break;
            case GAMEPLAY:
                DrawGameplayScreen();
                break;
            case ENDING:
                DrawEndingScreen();
                break;
            default: 
                break;
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