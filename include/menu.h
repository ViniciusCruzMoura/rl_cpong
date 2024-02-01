#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef struct MenuButton {
    char *label;
    Rectangle recs;
} MenuButton;

typedef struct Menu {
    MenuButton option[5];
    int optionSelected;
    int mouseHoverRec;
} Menu;

void InitMenu(Menu *menu, int pos_x, int pos_y);
void UpdateMenu(Menu *menu);
void DrawMenu(const Menu menu);
void UnloadMenu(Menu *menu);

#endif // MENU_H