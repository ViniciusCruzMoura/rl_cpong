#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef struct MenuButton {
    char *label;
    Rectangle recs;
} MenuButton;

typedef struct CMenu {
    MenuButton option[5];
    int optionSelected;
    int mouseHoverRec;
} CMenu;

void InitMenu(CMenu *menu, int pos_x, int pos_y);
void UpdateMenu(CMenu *menu);
void DrawMenu(const CMenu menu);
void UnloadMenu(CMenu *menu);

#endif // MENU_H