#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>

class MenuButton {
  public:
    std::string label;
    Rectangle recs;

    MenuButton(std::string text = "", float x = 0, float y = 0)
        : label(text), recs((Rectangle){x, y, 150.0f, 30.0f}) {}
};

class Menu {
  public:
    std::vector<MenuButton> option;
    int optionSelected;
    int mouseHoverRec;

    Menu(std::vector<std::string> options = {}, float pos_x = 0, float pos_y = 0)
        : optionSelected(0), mouseHoverRec(-1) {
        for (size_t i = 0; i < options.size(); ++i) {
            option.push_back(MenuButton(options[i], pos_x - 150.0f / 2, pos_y + 32 * i));
        }
    }

    void update() {
        for (size_t i = 0; i < option.size(); ++i) {
            if (CheckCollisionPointRec(GetMousePosition(), option[i].recs)) {
                mouseHoverRec = i;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    optionSelected = i;
                }
                break;
            } else {
                mouseHoverRec = -1;
            }
        }
    }
    void draw() {
        for (size_t i = 0; i < option.size(); ++i) {
            DrawRectangleRec(
                option[i].recs,
                (i == optionSelected || i == mouseHoverRec) ? SKYBLUE : LIGHTGRAY
            );
            DrawRectangleLines(
                (int)option[i].recs.x,
                (int)option[i].recs.y,
                (int)option[i].recs.width,
                (int)option[i].recs.height,
                (i == optionSelected || i == mouseHoverRec) ? BLUE : GRAY
            );
            DrawText(
                option[i].label.c_str(),
                (int)(option[i].recs.x + option[i].recs.width / 2 - MeasureText(option[i].label.c_str(), 10) / 2),
                (int)(option[i].recs.y + 11),
                10,
                (i == optionSelected || i == mouseHoverRec) ? DARKBLUE : DARKGRAY
            );
        }
    }
    bool is_option_selected(std::string text) {
        return text == option[optionSelected].label;
    }
};

int main(void) {
    int screenWidth = 800;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "raylib - test");
    SetTargetFPS(60);

    Menu main_menu({"START", "SETTINGS", "EXIT"}, screenWidth / 2, screenHeight / 2);

    Texture2D texture_bg_main_menu = LoadTexture("../assets/textures/bg_main_menu.png");
    
    InitAudioDevice();
    Sound sfx_main_menu = LoadSound("../assets/sounds/main_menu.wav");
    PlaySound(sfx_main_menu);

    // config background size
    float aspect_ratio = texture_bg_main_menu.width / texture_bg_main_menu.height;
    Rectangle imageRect = (Rectangle){
        (screenWidth - screenWidth) / 2,
        (screenHeight - screenWidth / aspect_ratio) / 2,
        screenWidth,
        screenWidth / aspect_ratio,
    };

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        main_menu.update();
        if (!IsSoundPlaying(sfx_main_menu)) {
            PlaySound(sfx_main_menu);
        }
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
        DrawTexturePro(
            texture_bg_main_menu, 
            (Rectangle){0,0, texture_bg_main_menu.width, texture_bg_main_menu.height}, 
            imageRect, 
            (Vector2){0, 0}, 0, WHITE
        );
        main_menu.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    StopSound(sfx_main_menu);
    UnloadSound(sfx_main_menu);
    CloseAudioDevice();

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

