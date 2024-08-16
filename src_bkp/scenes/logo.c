#include "game.h"

void InitLogoScreen() {}

void UpdateLogoScreen() {
    // Update LOGO screen data here!
    game.framesCounter++;            
    if (game.framesCounter > 180) 
    {
        game.currentScreen = TITLE;    // Change to TITLE screen after 3 seconds
        game.framesCounter = 0;
    }
}

void DrawLogoScreen() {
    // Draw LOGO screen here!
    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
    game.elementPositionY += 3;
    if (game.elementPositionY > (game.screenHeight/3 - 64)) game.elementPositionY = game.screenHeight/3 - 64;
    DrawTexturePro(
        game.texLogo,
        (Rectangle){ 0, 0, game.texLogo.width, game.texLogo.height },
        (Rectangle){ game.screenWidth/2, game.screenHeight/2, game.texLogo.width, game.texLogo.height },
        (Vector2){ game.texLogo.width / 2, game.texLogo.height / 2 - game.elementPositionY /4 },
        0,
        WHITE
    );
}

void UnloadLogoScreen() {}