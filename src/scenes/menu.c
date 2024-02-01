#include "game.h"

void InitMenu(Menu *menu, int pos_x, int pos_y) {
    // Init menu
    char *menu_opts[] = {
        "FULLSCREEN",
        "WINDOWED",
    };
    menu->optionSelected = 0;
    menu->mouseHoverRec = -1;
    for (int i = 0; i < (sizeof(menu_opts) / sizeof(menu_opts[0])); i++) {
        menu->option[i].label = menu_opts[i];
        menu->option[i].recs = (Rectangle){ 
            pos_x - 150.0f/2,
            pos_y + 32*i,
            150.0f,
            30.0f
        };
    }
}

void UpdateMenu(Menu *menu) {
    // Mouse toggle group logic of menu options
    for (int i = 0; i < (sizeof(menu->option) / sizeof(menu->option[0])); i++) {
        if (CheckCollisionPointRec(GetMousePosition(), menu->option[i].recs))
        {
            menu->mouseHoverRec = i;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                menu->optionSelected = i;
            }
            break;
        }
        else menu->mouseHoverRec = -1;
    }
}

void DrawMenu(Menu menu) {
    // Draw menu options
    for (int i = 0; i < (sizeof(menu.option) / sizeof(menu.option[0])); i++) {
        DrawRectangleRec(menu.option[i].recs, ((i == menu.optionSelected) || (i == menu.mouseHoverRec)) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLines((int)menu.option[i].recs.x, (int) menu.option[i].recs.y, (int) menu.option[i].recs.width, (int) menu.option[i].recs.height, ((i == menu.optionSelected) || (i == menu.mouseHoverRec)) ? BLUE : GRAY);
        DrawText( menu.option[i].label, (int)( menu.option[i].recs.x + menu.option[i].recs.width/2 - MeasureText(menu.option[i].label, 10)/2), (int) menu.option[i].recs.y + 11, 10, ((i == menu.optionSelected) || (i == menu.mouseHoverRec)) ? DARKBLUE : DARKGRAY);
    }
}

void UnloadMenu(Menu *menu) {}