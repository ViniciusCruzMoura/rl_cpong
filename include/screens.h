#ifndef SCREENS_H
#define SCREENS_H

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

// Logo Screen Functions Declaration
void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);

// Title Screen Functions Declaration
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);

// Gameplay Screen Functions Declaration
void InitGameplayScreen(void);
void UpdateGameplayScreen(void);
void DrawGameplayScreen(void);
void UnloadGameplayScreen(void);

// Ending Screen Functions Declaration
void InitEndingScreen(void);
void UpdateEndingScreen(void);
void DrawEndingScreen(void);
void UnloadEndingScreen(void);

#endif // SCREENS_H