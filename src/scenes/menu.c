#include "game.h"

void MenuButton_init(MenuButton *button, char *text, float x, float y) {
    button->label = strdup(text);
    button->recs.x = x;
    button->recs.y = y;
    button->recs.width = 150.0f;
    button->recs.height = 30.0f;
}

void MenuButton_destroy(MenuButton *button) {
    free(button->label);
}

void Menu_init(Menu *menu, char **options, size_t size, float pos_x, float pos_y) {
    menu->option = malloc(size * sizeof(MenuButton));
    menu->size = size;
    menu->optionSelected = 0;
    menu->mouseHoverRec = -1;
    for (size_t i = 0; i < size; ++i) {
        MenuButton_init(&menu->option[i], options[i], pos_x - 150.0f / 2, pos_y + 32 * i);
    }
}

void Menu_destroy(Menu *menu) {
    for (size_t i = 0; i < menu->size; ++i) {
        MenuButton_destroy(&menu->option[i]);
    }
    free(menu->option);
}

void Menu_update(Menu *menu) {
    for (size_t i = 0; i < menu->size; ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), menu->option[i].recs)) {
            menu->mouseHoverRec = i;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                menu->optionSelected = i;
            }
            break;
        } else {
            menu->mouseHoverRec = -1;
        }
    }
}

void Menu_draw(Menu *menu) {
    for (size_t i = 0; i < menu->size; ++i) {
        DrawRectangleRec(menu->option[i].recs, (i == menu->optionSelected || i == menu->mouseHoverRec) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLines((int)menu->option[i].recs.x, (int)menu->option[i].recs.y, (int)menu->option[i].recs.width, (int)menu->option[i].recs.height, (i == menu->optionSelected || i == menu->mouseHoverRec) ? BLUE : GRAY);
        DrawText(menu->option[i].label, (int)(menu->option[i].recs.x + menu->option[i].recs.width / 2 - MeasureText(menu->option[i].label, 10) / 2), (int)(menu->option[i].recs.y + 11), 10, (i == menu->optionSelected || i == menu->mouseHoverRec) ? DARKBLUE : DARKGRAY);
    }
}

bool Menu_is_option_selected(Menu *menu, char *text) {
    return strcmp(text, menu->option[menu->optionSelected].label) == 0;
}



// void InitMenu(Menu *menu, Vector2 position) {
//     // Init menu
//     char *menu_opts[] = {
//         "NEW GAME",
//         "OPTIONS",
//         "CREDITS",
//         "EXIT",
//     };
//     menu->optionSelected = 0;
//     menu->mouseHoverRec = -1;
//     for (int i = 0; i < (sizeof(menu_opts) / sizeof(menu_opts[0])); i++) {
//         menu->option[i].label = menu_opts[i];
//         menu->option[i].recs = (Rectangle){ 
//             position.x - 150.0f/2,
//             position.y + 32*i,
//             150.0f,
//             30.0f
//         };
//     }
// }

// void UpdateMenu(Menu *menu) {
//     // Mouse toggle group logic of menu options
//     for (int i = 0; i < (sizeof(menu->option) / sizeof(menu->option[0])); i++) {
//         if (CheckCollisionPointRec(GetMousePosition(), menu->option[i].recs))
//         {
//             menu->mouseHoverRec = i;

//             if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
//             {
//                 menu->optionSelected = i;
//             }
//             break;
//         }
//         else menu->mouseHoverRec = -1;
//     }
// }

// void DrawMenu(Menu menu) {
//     // Draw menu options
//     for (int i = 0; i < (sizeof(menu.option) / sizeof(menu.option[0])); i++) {
//         DrawRectangleRec(menu.option[i].recs, ((i == menu.optionSelected) || (i == menu.mouseHoverRec)) ? SKYBLUE : LIGHTGRAY);
//         DrawRectangleLines((int)menu.option[i].recs.x, (int) menu.option[i].recs.y, (int) menu.option[i].recs.width, (int) menu.option[i].recs.height, ((i == menu.optionSelected) || (i == menu.mouseHoverRec)) ? BLUE : GRAY);
//         DrawText( menu.option[i].label, (int)( menu.option[i].recs.x + menu.option[i].recs.width/2 - MeasureText(menu.option[i].label, 10)/2), (int) menu.option[i].recs.y + 11, 10, ((i == menu.optionSelected) || (i == menu.mouseHoverRec)) ? DARKBLUE : DARKGRAY);
//     }
// }

void UnloadMenu(Menu *menu) {
    Menu_destroy(&menu);
}
