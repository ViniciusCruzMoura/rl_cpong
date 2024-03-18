// #include "raylib.h"
// #include <iostream>
// #include <string>
// #include <vector>

// class MenuButton {
//   public:
//     std::string label;
//     Rectangle recs;

//     MenuButton(std::string text = "", float x = 0, float y = 0)
//         : label(text), recs((Rectangle){x, y, 150.0f, 30.0f}) {}
// };

// class Menu {
//   public:
//     std::vector<MenuButton> option;
//     int optionSelected;
//     int mouseHoverRec;

//     Menu(std::vector<std::string> options = {}, float pos_x = 0, float pos_y = 0)
//         : optionSelected(0), mouseHoverRec(-1) {
//         for (size_t i = 0; i < options.size(); ++i) {
//             option.push_back(MenuButton(options[i], pos_x - 150.0f / 2, pos_y + 32 * i));
//         }
//     }

//     void update() {
//         for (size_t i = 0; i < option.size(); ++i) {
//             if (CheckCollisionPointRec(GetMousePosition(), option[i].recs)) {
//                 mouseHoverRec = i;
//                 if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
//                     optionSelected = i;
//                 }
//                 break;
//             } else {
//                 mouseHoverRec = -1;
//             }
//         }
//     }
//     void draw() {
//         for (size_t i = 0; i < option.size(); ++i) {
//             DrawRectangleRec(
//                 option[i].recs,
//                 (i == optionSelected || i == mouseHoverRec) ? SKYBLUE : LIGHTGRAY
//             );
//             DrawRectangleLines(
//                 (int)option[i].recs.x,
//                 (int)option[i].recs.y,
//                 (int)option[i].recs.width,
//                 (int)option[i].recs.height,
//                 (i == optionSelected || i == mouseHoverRec) ? BLUE : GRAY
//             );
//             DrawText(
//                 option[i].label.c_str(),
//                 (int)(option[i].recs.x + option[i].recs.width / 2 - MeasureText(option[i].label.c_str(), 10) / 2),
//                 (int)(option[i].recs.y + 11),
//                 10,
//                 (i == optionSelected || i == mouseHoverRec) ? DARKBLUE : DARKGRAY
//             );
//         }
//     }
//     bool is_option_selected(std::string text) {
//         return text == option[optionSelected].label;
//     }
// };

// int main(void) {
//     int screenWidth = 800;
//     int screenHeight = 600;
//     InitWindow(screenWidth, screenHeight, "raylib - test");
//     SetTargetFPS(60);

//     Menu main_menu({"START", "SETTINGS", "EXIT"}, screenWidth / 2, screenHeight / 2);

//     Texture2D texture_bg_main_menu = LoadTexture("../assets/textures/bg_main_menu.jpg");
    
//     InitAudioDevice();
//     Sound sfx_main_menu = LoadSound("../assets/sounds/main_menu.wav");
//     PlaySound(sfx_main_menu);

//     // config background size
//     float aspect_ratio = texture_bg_main_menu.width / texture_bg_main_menu.height;
//     Rectangle imageRect = (Rectangle){
//         (screenWidth - screenWidth) / 2,
//         (screenHeight - screenWidth / aspect_ratio) / 2,
//         screenWidth,
//         screenWidth / aspect_ratio,
//     };

//     // Main game loop
//     while (!WindowShouldClose())    // Detect window close button or ESC key
//     {
//         // Update
//         //----------------------------------------------------------------------------------
//         main_menu.update();
//         if (!IsSoundPlaying(sfx_main_menu)) {
//             PlaySound(sfx_main_menu);
//         }
//         //----------------------------------------------------------------------------------
        
//         // Draw
//         //----------------------------------------------------------------------------------
//         BeginDrawing();
        
//         DrawTexturePro(
//             texture_bg_main_menu, 
//             (Rectangle){0,0, texture_bg_main_menu.width, texture_bg_main_menu.height}, 
//             imageRect, 
//             (Vector2){0, 0}, 0, WHITE
//         );
//         main_menu.draw();

//         EndDrawing();
//         //----------------------------------------------------------------------------------
//     }

//     StopSound(sfx_main_menu);
//     UnloadSound(sfx_main_menu);
//     CloseAudioDevice();

//     CloseWindow();        // Close window and OpenGL context

//     return 0;
// }



// #include "raylib.h"
// #include "raymath.h"
// #include <string>

// #define MAX(a, b) ((a)>(b)? (a) : (b))
// #define MIN(a, b) ((a)<(b)? (a) : (b))
// #define COLOUR_SIZE 10

// int main(void)
// {
//     SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
//     InitWindow(800, 450, "raylib [core] example - basic window");
//     SetWindowMinSize(320, 240);

//     int gameScreenWidth = 640;
//     int gameScreenHeight = 480;

//     RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
//     SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

//     Color colors[COLOUR_SIZE] = { 0 };
//     for (int i = 0; i < COLOUR_SIZE; i++) 
//     {
//         colors[i] = (Color){ 
//             .r = GetRandomValue(100, 250), 
//             .g = GetRandomValue(50, 150), 
//             .b = GetRandomValue(10, 100), 
//             .a = 255 
//         };
//     }

//     SetTargetFPS(60);
//     while (!WindowShouldClose())
//     {
//         float scale = MIN(
//             (float)GetScreenWidth()/gameScreenWidth, 
//             (float)GetScreenHeight()/gameScreenHeight
//         );

//         // TraceLog(LOG_INFO, std::to_string(scale).c_str());

//         Vector2 mouse = GetMousePosition();
//         Vector2 virtualMouse = Vector2Clamp(
//             (Vector2){ 
//                 .x = (mouse.x - (GetScreenWidth() - (gameScreenWidth*scale))*0.5f)/scale, 
//                 .y = (mouse.y - (GetScreenHeight() - (gameScreenHeight*scale))*0.5f)/scale
//             },
//             (Vector2){ .x = 0, .y = 0 }, 
//             (Vector2){ 
//                 .x = gameScreenWidth, 
//                 .y = gameScreenHeight 
//             }
//         );

//         BeginTextureMode(target);
//             ClearBackground(RAYWHITE);

//             for (int i = 0; i < COLOUR_SIZE; i++) 
//             {
//                 DrawRectangle(
//                     0, 
//                     (gameScreenHeight/10)*i, 
//                     gameScreenWidth, 
//                     gameScreenHeight/10, 
//                     colors[i]
//                 );
//             }

//             DrawText(
//                 "If executed inside a window,\nyou can resize the window,\nand see the screen scaling!", 
//                 10, 25, 
//                 20, WHITE
//             );
//             DrawText(
//                 TextFormat("Default Mouse: [%i , %i]", (int)mouse.x, (int)mouse.y), 
//                 350, 25, 
//                 20, GREEN
//             );
//             DrawText(
//                 TextFormat("Virtual Mouse: [%i , %i]", (int)virtualMouse.x, (int)virtualMouse.y), 
//                 350, 55, 
//                 20, YELLOW
//             );
//         EndTextureMode();

//         BeginDrawing();
//             ClearBackground(BLACK);
//             DrawTexturePro(
//                 target.texture, 
//                 (Rectangle){ 
//                     .x = 0.0f, 
//                     .y = 0.0f, 
//                     .width = (float)target.texture.width, 
//                     .height = (float)-target.texture.height 
//                 },
//                 (Rectangle){ 
//                     .x = (GetScreenWidth() - ((float)gameScreenWidth*scale))*0.5f, 
//                     .y = (GetScreenHeight() - ((float)gameScreenHeight*scale))*0.5f, 
//                     .width = (float)gameScreenWidth*scale, 
//                     .height = (float)gameScreenHeight*scale 
//                 }, 
//                 (Vector2){ .x = 0, .y = 0 },
//                 0.0f, WHITE
//             );
//         EndDrawing();
//     }
//     UnloadRenderTexture(target);
//     CloseWindow();
//     return 0;
// }

// #include "raylib.h"
// #include "raymath.h"

// #define G 400
// #define PLAYER_JUMP_SPD 350.0f
// #define PLAYER_HOR_SPD 200.0f
// #define MIN(a, b) ((a)<(b)? (a) : (b))

// typedef struct Player {
//     Vector2 position;
//     float speed;
//     bool canJump;
// } Player;

// typedef struct EnvItem {
//     Rectangle rect;
//     int blocking;
//     Color color;
// } EnvItem;

// //----------------------------------------------------------------------------------
// // Module functions declaration
// //----------------------------------------------------------------------------------
// void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta);
// void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
// void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
// void UpdateCameraCenterSmoothFollow(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
// void UpdateCameraEvenOutOnLanding(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
// void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);

// //------------------------------------------------------------------------------------
// // Program main entry point
// //------------------------------------------------------------------------------------
// int main(void)
// {
//     // Initialization
//     //--------------------------------------------------------------------------------------
//     int screenWidth = 800;
//     int screenHeight = 450;

//     SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
//     InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

//     Player player = { 0 };
//     player.position = (Vector2){ 400, 280 };
//     player.speed = 0;
//     player.canJump = false;
//     EnvItem envItems[] = {
//         {{ 0, 0, 1000, 400 }, 0, LIGHTGRAY },
//         {{ 0, 400, 1000, 200 }, 1, GRAY },
//         {{ 300, 200, 400, 10 }, 1, GRAY },
//         {{ 250, 300, 100, 10 }, 1, GRAY },
//         {{ 650, 300, 100, 10 }, 1, GRAY }
//     };

//     int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

//     Camera2D camera = { 0 };
//     camera.target = player.position;
//     camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
//     camera.rotation = 0.0f;
//     camera.zoom = 1.0f;

//     RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
//     // SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

//     // Store pointers to the multiple update camera functions
//     void (*cameraUpdaters[])(Camera2D*, Player*, EnvItem*, int, float, int, int) = {
//         UpdateCameraCenter,
//         UpdateCameraCenterInsideMap,
//         UpdateCameraCenterSmoothFollow,
//         UpdateCameraEvenOutOnLanding,
//         UpdateCameraPlayerBoundsPush
//     };

//     int cameraOption = 0;
//     int cameraUpdatersLength = sizeof(cameraUpdaters)/sizeof(cameraUpdaters[0]);

//     char *cameraDescriptions[] = {
//         "Follow player center",
//         "Follow player center, but clamp to map edges",
//         "Follow player center; smoothed",
//         "Follow player center horizontally; update player center vertically after landing",
//         "Player push camera on getting too close to screen edge"
//     };

//     SetTargetFPS(60);
//     //--------------------------------------------------------------------------------------

//     // Main game loop
//     while (!WindowShouldClose())
//     {
//         // Update
//         //----------------------------------------------------------------------------------
//         float deltaTime = GetFrameTime();
//         // screenWidth = GetScreenWidth();
//         // screenHeight = GetScreenHeight();
//         // camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
//         float scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

//         UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

//         camera.zoom += ((float)GetMouseWheelMove()*0.05f);

//         if (camera.zoom > 3.0f) camera.zoom = 3.0f;
//         else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

//         if (IsKeyPressed(KEY_R))
//         {
//             camera.zoom = 1.0f;
//             player.position = (Vector2){ 400, 280 };
//         }

//         if (IsKeyPressed(KEY_C)) cameraOption = (cameraOption + 1)%cameraUpdatersLength;

//         // Call update camera function by its pointer
//         cameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
//         //----------------------------------------------------------------------------------

//         // Draw
//         //----------------------------------------------------------------------------------
//         BeginDrawing();
//             BeginTextureMode(target);

//                 ClearBackground(LIGHTGRAY);

//                 BeginMode2D(camera);

//                     for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

//                     Rectangle playerRect = { player.position.x - 20, player.position.y - 40, 40, 40 };
//                     DrawRectangleRec(playerRect, RED);
                    
//                     DrawCircle(player.position.x, player.position.y, 5, GOLD);

//                 EndMode2D();

//                 DrawText("Controls:", 20, 20, 10, BLACK);
//                 DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
//                 DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
//                 DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, DARKGRAY);
//                 DrawText("- C to change camera mode", 40, 100, 10, DARKGRAY);
//                 DrawText("Current camera mode:", 20, 120, 10, BLACK);
//                 DrawText(cameraDescriptions[cameraOption], 40, 140, 10, DARKGRAY);
            
//             EndTextureMode();

//             ClearBackground(BLACK);
//             DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
//                            (Rectangle){ (GetScreenWidth() - ((float)screenWidth*scale))*0.5f, (GetScreenHeight() - ((float)screenHeight*scale))*0.5f,
//                            (float)screenWidth*scale, (float)screenHeight*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);

//         EndDrawing();
//         //----------------------------------------------------------------------------------
//     }

//     // De-Initialization
//     //--------------------------------------------------------------------------------------
//     CloseWindow();        // Close window and OpenGL context
//     //--------------------------------------------------------------------------------------

//     return 0;
// }

// void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta)
// {
//     if (IsKeyDown(KEY_LEFT)) player->position.x -= PLAYER_HOR_SPD*delta;
//     if (IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HOR_SPD*delta;
//     if (IsKeyDown(KEY_SPACE) && player->canJump)
//     {
//         player->speed = -PLAYER_JUMP_SPD;
//         player->canJump = false;
//     }

//     bool hitObstacle = false;
//     for (int i = 0; i < envItemsLength; i++)
//     {
//         EnvItem *ei = envItems + i;
//         Vector2 *p = &(player->position);
//         if (ei->blocking &&
//             ei->rect.x <= p->x &&
//             ei->rect.x + ei->rect.width >= p->x &&
//             ei->rect.y >= p->y &&
//             ei->rect.y <= p->y + player->speed*delta)
//         {
//             hitObstacle = true;
//             player->speed = 0.0f;
//             p->y = ei->rect.y;
//             break;
//         }
//     }

//     if (!hitObstacle)
//     {
//         player->position.y += player->speed*delta;
//         player->speed += G*delta;
//         player->canJump = false;
//     }
//     else player->canJump = true;
// }

// void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
// {
//     camera->offset = (Vector2){ width/2.0f, height/2.0f };
//     camera->target = player->position;
// }

// void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
// {
//     camera->target = player->position;
//     camera->offset = (Vector2){ width/2.0f, height/2.0f };
//     float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

//     for (int i = 0; i < envItemsLength; i++)
//     {
//         EnvItem *ei = envItems + i;
//         minX = fminf(ei->rect.x, minX);
//         maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
//         minY = fminf(ei->rect.y, minY);
//         maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
//     }

//     Vector2 max = GetWorldToScreen2D((Vector2){ maxX, maxY }, *camera);
//     Vector2 min = GetWorldToScreen2D((Vector2){ minX, minY }, *camera);

//     if (max.x < width) camera->offset.x = width - (max.x - width/2);
//     if (max.y < height) camera->offset.y = height - (max.y - height/2);
//     if (min.x > 0) camera->offset.x = width/2 - min.x;
//     if (min.y > 0) camera->offset.y = height/2 - min.y;
// }

// void UpdateCameraCenterSmoothFollow(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
// {
//     static float minSpeed = 30;
//     static float minEffectLength = 10;
//     static float fractionSpeed = 0.8f;

//     camera->offset = (Vector2){ width/2.0f, height/2.0f };
//     Vector2 diff = Vector2Subtract(player->position, camera->target);
//     float length = Vector2Length(diff);

//     if (length > minEffectLength)
//     {
//         float speed = fmaxf(fractionSpeed*length, minSpeed);
//         camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*delta/length));
//     }
// }

// void UpdateCameraEvenOutOnLanding(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
// {
//     static float evenOutSpeed = 700;
//     static int eveningOut = false;
//     static float evenOutTarget;

//     camera->offset = (Vector2){ width/2.0f, height/2.0f };
//     camera->target.x = player->position.x;

//     if (eveningOut)
//     {
//         if (evenOutTarget > camera->target.y)
//         {
//             camera->target.y += evenOutSpeed*delta;

//             if (camera->target.y > evenOutTarget)
//             {
//                 camera->target.y = evenOutTarget;
//                 eveningOut = 0;
//             }
//         }
//         else
//         {
//             camera->target.y -= evenOutSpeed*delta;

//             if (camera->target.y < evenOutTarget)
//             {
//                 camera->target.y = evenOutTarget;
//                 eveningOut = 0;
//             }
//         }
//     }
//     else
//     {
//         if (player->canJump && (player->speed == 0) && (player->position.y != camera->target.y))
//         {
//             eveningOut = 1;
//             evenOutTarget = player->position.y;
//         }
//     }
// }

// void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
// {
//     static Vector2 bbox = { 0.2f, 0.2f };

//     Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2){ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, *camera);
//     Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2){ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, *camera);
//     camera->offset = (Vector2){ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

//     if (player->position.x < bboxWorldMin.x) camera->target.x = player->position.x;
//     if (player->position.y < bboxWorldMin.y) camera->target.y = player->position.y;
//     if (player->position.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->position.x - bboxWorldMax.x);
//     if (player->position.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->position.y - bboxWorldMax.y);
// }


#include "raylib.h"
#include <string>
#include "raymath.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define TILE_SIZE 32
#define TILEMAP_SIZE_W 16
#define TILEMAP_SIZE_H 15
#define WIN_RES_W (TILE_SIZE * TILEMAP_SIZE_W)
#define WIN_RES_H (TILE_SIZE * TILEMAP_SIZE_H)
#define TILE_NULL -1
#define TILE_GRASS_ID 1
#define TILE_GRASS_PATH "../assets/textures/tile_1.png"
#define TILE_DIRT_ID 0
#define TILE_DIRT_PATH "../assets/textures/tile_0.png"
#define SPRITE_PLAYER_PATH "../assets/textures/player.png"
#define TILEMAP_PATH "../assets/map/map1.csv"

// typedef enum Tile { 
//     GRASS = 1, 
//     DIRT = 2
// } Tile;

// typedef struct Player {
//     Vector2 position;
//     Vector2 direction;
//     Rectangle collision;
//     int speed;
//     Texture2D sprite;
// } Player;

std::vector<std::vector<std::string>> map1;

class Player { 
    public:
        Vector2 position;
        Vector2 direction;
        Rectangle collision;
        int speed;
        Texture2D sprite;

        void update();
    private:
        void input();
        void move();
        void collision_obj(std::vector<std::vector<std::string>> collision_map, std::string dir);
};

void Player::input() {
    if (IsKeyDown(KEY_S)) {
        direction.y = 1;
    } else if(IsKeyDown(KEY_W)) { 
        direction.y = -1;
    } else {
        direction.y = 0;
    }
    if (IsKeyDown(KEY_D)) {
        direction.x = 1;
    } else if (IsKeyDown(KEY_A)) {
        direction.x = -1;
    } else {
        direction.x = 0;
    }
}

void Player::move() {
    Vector2 pos = Vector2Add(position, Vector2Scale(direction, speed));
    position.x = pos.x;
    collision.x = pos.x;
    collision_obj(map1, "horizontal");
    position.y = pos.y;
    collision.y = pos.y;
    collision_obj(map1, "vertical");
}

void Player::collision_obj(std::vector<std::vector<std::string>> collision_map, std::string dir) {
    Rectangle m_collision;
    bool m_is_colliding;
    for (int i = 0; i < collision_map.size(); i++)
        {
            for (int j = 0; j < collision_map[i].size(); j++)
            {
                m_collision = (Rectangle){
                    .x = TILE_SIZE * j,
                    .y = TILE_SIZE * i,
                    .width = TILE_SIZE,
                    .height = TILE_SIZE
                };
                switch (std::stoi(collision_map[i][j])) 
                {
                    case TILE_GRASS_ID:
                    case TILE_NULL:
                        m_is_colliding = CheckCollisionRecs(collision, m_collision);
                        if (m_is_colliding)
                        {
                            if (dir == "horizontal") 
                            {
                                if (direction.x > 0) {
                                    position.x = m_collision.x - m_collision.width;
                                    collision.x = m_collision.x - m_collision.width;
                                }
                                if (direction.x < 0) {
                                    position.x = m_collision.x + m_collision.width;
                                    collision.x = m_collision.x + m_collision.width;
                                }
                            }
                            if (dir == "vertical") 
                            {
                                if (direction.y > 0) {
                                    position.y = m_collision.y - m_collision.height;
                                    collision.y = m_collision.y - m_collision.height;
                                }
                                if (direction.y < 0) {
                                    position.y = m_collision.y + m_collision.height;
                                    collision.y = m_collision.y + m_collision.height;
                                }
                            }
                        }
                        break;
                    case TILE_DIRT_ID:
                        break;
                    default:
                        break;
                }
            }
        }
}

void Player::update() {
    input();
    move();
}

Texture2D grass;
Texture2D dirt;

Player player;

// int map1[TILEMAP_SIZE_H][TILEMAP_SIZE_W] = { 
//     {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0},
// };



// void player_collision(Player *player, std::vector<std::vector<std::string>> collision_map, int dir)
// {
//     Rectangle m_collision;
//     bool m_is_colliding;
//     for (int i = 0; i < collision_map.size(); i++)
//         {
//             for (int j = 0; j < collision_map[i].size(); j++)
//             {
//                 m_collision = (Rectangle){
//                     .x = TILE_SIZE * j,
//                     .y = TILE_SIZE * i,
//                     .width = TILE_SIZE,
//                     .height = TILE_SIZE
//                 };
//                 switch (std::stoi(collision_map[i][j])) 
//                 {
//                     case TILE_GRASS_ID:
//                     case TILE_NULL:
//                         m_is_colliding = CheckCollisionRecs(player->collision, m_collision);
//                         if (m_is_colliding)
//                         {
//                             if (dir == 0) 
//                             {
//                                 if (player->direction.x > 0) {
//                                     player->position.x = m_collision.x - m_collision.width;
//                                     player->collision.x = m_collision.x - m_collision.width;
//                                 }
//                                 if (player->direction.x < 0) {
//                                     player->position.x = m_collision.x + m_collision.width;
//                                     player->collision.x = m_collision.x + m_collision.width;
//                                 }
//                             }
//                             if (dir == 1) 
//                             {
//                                 if (player->direction.y > 0) {
//                                     player->position.y = m_collision.y - m_collision.height;
//                                     player->collision.y = m_collision.y - m_collision.height;
//                                 }
//                                 if (player->direction.y < 0) {
//                                     player->position.y = m_collision.y + m_collision.height;
//                                     player->collision.y = m_collision.y + m_collision.height;
//                                 }
//                             }
//                         }
//                         break;
//                     case TILE_DIRT_ID:
//                         break;
//                     default:
//                         break;
//                 }
//             }
//         }
// }




/**
void player_input() {}
void player_move() {}
void player_update() {
    player_input();
    player_move();
}
*/

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::vector<std::string>> load_csv(const std::string path)
{
    // Open the .csv file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        std::vector<std::vector<std::string>> err;
        return err;
    }

    // Read the .csv file line by line
    std::vector<std::vector<std::string>> data;
    std::string line;
    while (std::getline(file, line)) {
        // Split each line by comma and store it in the 2D vector
        std::vector<std::string> row = split(line, ',');
        data.push_back(row);
    }

    // Display the data (optional)
    std::cout << "CSV Data." << std::endl;
    for (const auto& row : data) {
        for (const auto& value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    // Close the file
    file.close();

    return data;

    // // Check if the dimensions of data match the dimensions of map
    // if (data.size() != TILEMAP_SIZE_H || (data.size() > 0 && data[0].size() != TILEMAP_SIZE_W)) {
    //     std::cerr << "Vector dimensions do not match array dimensions\n";
    //     return;
    // }

    // // Convert to 2D array
    // for (int i = 0; i < TILEMAP_SIZE_H; ++i) {
    //     for (int j = 0; j < TILEMAP_SIZE_W; ++j) {
    //         map[i][j] = std::stoi(data[i][j]);
    //     }
    // }
}

int main(void)
{
    InitWindow(WIN_RES_W, WIN_RES_H, "raylib example - tilemap");
    SetTargetFPS(30);

    grass = LoadTexture(TILE_GRASS_PATH);
    dirt = LoadTexture(TILE_DIRT_PATH);

    player.position = (Vector2){ .x = 200, .y = 200 };
    player.collision = (Rectangle){ 
        .x = 200, 
        .y = 200, 
        .width = TILE_SIZE, 
        .height = TILE_SIZE 
    };
    player.direction = (Vector2){ .x = 0, .y = 0 };
    player.speed = 5;
    player.sprite = LoadTexture(SPRITE_PLAYER_PATH);

    map1 = load_csv(TILEMAP_PATH);

    while (!WindowShouldClose())
    {
        // if (IsKeyDown(KEY_S)) {
        //     player.direction.y = 1;
        // } else if(IsKeyDown(KEY_W)) { 
        //     player.direction.y = -1;
        // } else {
        //     player.direction.y = 0;
        // }
        // if (IsKeyDown(KEY_D)) {
        //     player.direction.x = 1;
        // } else if (IsKeyDown(KEY_A)) {
        //     player.direction.x = -1;
        // } else {
        //     player.direction.x = 0;
        // }

        // Vector2 pos = Vector2Add(player.position, Vector2Scale(player.direction, player.speed));
        // player.position.x = pos.x;
        // player.collision.x = pos.x;
        // player_collision(&player, map1, 0);
        // player.position.y = pos.y;
        // player.collision.y = pos.y;
        // player_collision(&player, map1, 1);
        
        /**
        if (IsKeyDown(KEY_S)) {
            player.y -= speed * direction.y;
        } else if(IsKeyDown(KEY_W)) { 
            player.y -= speed * direction.y;
        }
        if (IsKeyDown(KEY_D)) {
            player.x -= speed * direction.x;
        } else if (IsKeyDown(KEY_A)) {
            player.x -= speed * direction.x;
        }*/
        /** 
        for (int i = 0; i < TILEMAP_SIZE_H; i++)
        {
            for (int j = 0; j < TILEMAP_SIZE_W; j++)
            {
                collision = (Rectangle){
                    .x = 0 + TILE_SIZE * j,
                    .y = 0 + TILE_SIZE * i,
                    .width = TILE_SIZE,
                    .height = TILE_SIZE
                };
                switch (map1[i][j]) 
                {
                    case TILE_GRASS_ID:
                        is_colliding = CheckCollisionRecs(player, collision);
                        if (is_colliding)
                        {
                            if (direction.x > 0) {
                                player.x = collision.x - collision.width;
                            }
                            if (direction.x < 0) {
                                player.x = collision.x + collision.width;
                            }
                            if (direction.y > 0) {
                                player.y = collision.y - collision.height;
                            }
                            if (direction.y < 0) {
                                player.y = collision.y + collision.height;
                            }
                        }
                        break;
                    case TILE_DIRT_ID:
                        break;
                    default:
                        break;
                }
            }
        }*/

        player.update();

        BeginDrawing();
            // ClearBackground(RAYWHITE);

            for (int i = 0; i < map1.size(); i++)
            {
                for (int j = 0; j < map1[i].size(); j++)
                {
                    switch (std::stoi(map1[i][j])) 
                    {
                        case TILE_GRASS_ID: 
                            DrawTextureV(grass, (Vector2){.x = 0 + 32 * j, .y = 0 + 32 * i}, WHITE);
                            break;
                        case TILE_DIRT_ID: 
                            DrawTextureV(dirt, (Vector2){.x = 0 + 32 * j, .y = 0 + 32 * i}, WHITE);
                            break;
                        default:
                            DrawRectangleV(
                                (Vector2){.x = 0 + 32 * j, .y = 0 + 32 * i}, 
                                (Vector2){.x = 32, .y = 32}, 
                                BLACK
                            );
                            break;
                    }
                }
            }

            DrawTextureV(player.sprite, player.position, WHITE);
            DrawRectangleLinesEx(player.collision, 3.0f, PURPLE);

            DrawText("demo_test", 0, 0, 20, WHITE);
            DrawText(std::to_string(player.direction.x).c_str(), 0, 32, 20, WHITE);
            DrawText(std::to_string(player.direction.y).c_str(), 0, 64, 20, WHITE);
            
            // DrawTextureV(grass, (Vector2){.x = 0, .y = 0}, WHITE);
            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
