#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include <stddef.h>

typedef struct MenuButton {
    char *label;
    Rectangle recs;
} MenuButton;

typedef struct Menu {
    MenuButton *option;
    int optionSelected;
    int mouseHoverRec;
    size_t size;
} Menu;

void Menu_init(Menu *menu, char **options, size_t size, float pos_x, float pos_y);
void Menu_destroy(Menu *menu);
void Menu_update(Menu *menu);
void Menu_draw(Menu *menu);
bool Menu_is_option_selected(Menu *menu, char *text);

void MenuButton_init(MenuButton *button, char *text, float x, float y);
void MenuButton_destroy(MenuButton *button);

// void InitMenu(Menu *menu, Vector2 position);
// void UpdateMenu(Menu *menu);
// void DrawMenu(const Menu menu);
void UnloadMenu(Menu *menu);

#endif // MENU_H