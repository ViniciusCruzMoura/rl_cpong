#ifndef SCREENS_H
#define SCREENS_H

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

// Logo Screen Functions Declaration
void init_logo_screen(void);
void update_logo_screen(void);
void draw_logo_screen(void);
void unload_logo_screen(void);

// Title Screen Functions Declaration
void init_title_screen(void);
void update_title_screen(void);
void draw_title_screen(void);
void unload_title_screen(void);

// Gameplay Screen Functions Declaration
void init_gameplay_screen(void);
void update_gameplay_screen(void);
void draw_gameplay_screen(void);
void unload_gameplay_screen(void);

// Ending Screen Functions Declaration
void init_ending_screen(void);
void update_ending_screen(void);
void draw_ending_screen(void);
void unload_ending_screen(void);

#endif // SCREENS_H