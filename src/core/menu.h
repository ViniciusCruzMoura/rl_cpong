#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef struct CMenuOption {
    char *label;
    Rectangle recs;
} CMenuOption;

typedef struct CMenu {
    CMenuOption option[5];
    int optionSelected;
    int mouseHoverRec;
} CMenu;

void init_menu(CMenu *menu);
void update_menu(CMenu *menu);
void draw_menu(CMenu *menu);

#endif // MENU_H