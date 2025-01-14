#include "rlcpong.h"

void initialize_game(struct game_instance *g)
{
    g->m_paused = false;
    g->m_running = true;
    g->m_current_frame = 0;
    g->m_windows = (struct render_window){ .m_width=SCREEN_WIDTH, 
        .m_height=SCREEN_HEIGHT, 
        .m_framerate_limit=30,
        .m_title=(char*)"RlCPong" };
    g->m_entities = (struct entity_manager){ .m_total_entities=0};
    g->m_windows.m_fullscreen_enabled = false;
}

void game_loop(struct game_instance *g)
{
    create_window(&g->m_windows);
    spawn_player(&g->m_entities);
    //spawn_ball(&g->m_entities);
    //spawn_enemy(&g->m_entities);
    while (g->m_running) {
        update_game_state(g);
        handle_input(g);
        render_frame(g);
        ++g->m_current_frame;
    }
    close_window(&g->m_windows);
}

void update_game_state(struct game_instance *g)
{
    update_entities(&g->m_entities);
    if (!g->m_paused) {
        //movement();
        //collision();
    }
}

void spawn_player(struct entity_manager *em)
{
    struct entity *player;
    struct Rectangle shape;
    struct Vector2 pos;
    struct Vector2 vel;
    
    player = get_entities(em, ENTITY_TYPE_PLAYER);
    if (player) {
        return;
    }
    player = add_entity(em, ENTITY_TYPE_PLAYER);
    
    shape.x = (SCREEN_WIDTH/12)*1;
    shape.y = SCREEN_HEIGHT/2 - SCREEN_HEIGHT/12;
    shape.width = 10;
    shape.height = 100;

    pos.x = (SCREEN_WIDTH/12)*1;
    pos.y = SCREEN_HEIGHT/2;

    vel.x = 30;
    vel.y = 30;

    player->shape.rec = shape;
    player->transform.pos = pos;
    player->transform.velocity = vel;
    player->flags.is_rectangle = true;
    player->flags.is_visible = true;
    player->score.value = 0;

    DEBUG_PRINT("spawn player : \n");
    DEBUG_PRINT("id : %li \n", player->m_id);
    DEBUG_PRINT("id tag : %d \n", player->m_tag);
    DEBUG_PRINT("is rectangle : %d \n", player->flags.is_rectangle);
}

void render_frame(struct game_instance *g)
{
    struct entity *player;
    struct entity *enemy;
    struct entity *ball;

    player = get_entities(&g->m_entities, ENTITY_TYPE_PLAYER);
    uint32_t half_col = ((SCREEN_WIDTH/12)*1)/2;
    uint32_t one_col = (SCREEN_WIDTH/12)*1;
    uint32_t five_col = one_col * 5;
    uint32_t six_col = one_col * 6;
    uint32_t seven_col = one_col * 7;
    uint32_t half_row = ((SCREEN_HEIGHT/12)*1)/2;
    uint32_t one_row = (SCREEN_HEIGHT/12)*1;

    BeginDrawing();
    ClearBackground(BLACK);
    
    //
    //draw_background()
    //
    for (int x = 0; x <=SCREEN_HEIGHT; ++x) {
        if (x % 2 == 1) continue;
        struct Vector2 start_pos = (Vector2){six_col, (SCREEN_HEIGHT/32)*x};
        struct Vector2 end_pos = (Vector2){six_col, (SCREEN_HEIGHT/32)*(x+1)};
        float thickness = 5.0;
        DrawLineEx(start_pos, end_pos, thickness, GRAY);
    }
    
    //
    //draw_score()
    //
    DrawText("0", five_col, one_row, 50, GRAY);
    DrawText("0", seven_col - half_col, one_row, 50, GRAY);
    
    //
    //draw_ball()
    //
    DrawRectangleRec((Rectangle){SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 10, 10}, WHITE);
    
    //
    //draw_player()
    //
    DrawRectangleRec(player->shape.rec, WHITE);
    
    //
    //draw_enemy()
    //
    DrawRectangleRec((Rectangle){(SCREEN_WIDTH/12)*11, SCREEN_HEIGHT/2 - SCREEN_HEIGHT/12, 10, 100}, WHITE);

    //
    //draw_grades()
    //
    for (int x = 0; x <= 12; ++x) {
        DrawLineEx((Vector2){(SCREEN_WIDTH/12)*x, 0}, (Vector2){(SCREEN_WIDTH/12)*x+1, SCREEN_HEIGHT}, 2.0, GREEN);
    }
    for (int y = 0; y <= 12; ++y) {
        DrawLineEx((Vector2){0, (SCREEN_HEIGHT/12)*y}, (Vector2){SCREEN_WIDTH, (SCREEN_HEIGHT/12)*y+1}, 2.0, GREEN);
    }

    //
    //draw_debug()
    //
    char buf[1024];
    snprintf(buf, 1024,
            "Frame: %d \n"
            , g->m_current_frame);
    DrawText(TextFormat(buf), 0, 0, 10, RED);

    EndDrawing();
}

void handle_input(struct game_instance *g)
{
    //menu_handle_input()
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        DEBUG_PRINT(
                "MOUSE_LEFT Key Pressed at ( %i , %i )\n", 
                GetMouseX(), GetMouseY());
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        DEBUG_PRINT(
                "MOUSE_RIGHT Key Pressed at ( %i , %i )\n", 
                GetMouseX(), GetMouseY());
    }

    //
    //window_handle_input()
    //
    g->m_running = is_open_window(&g->m_windows);
    if (IsKeyPressed(KEY_SPACE)) {
        DEBUG_PRINT("SPACE Key Released\n");
        g->m_paused = !g->m_paused;
    }

    //
    //player_handle_input()
    //
    struct entity *player;
    struct entity_manager *entities;

    entities = &g->m_entities;
    player = get_entities(entities, ENTITY_TYPE_PLAYER);
    
    if(IsKeyPressed(KEY_W)) { 
        player->transform.pos.y -= player->transform.velocity.y;
        player->shape.rec.y = player->transform.pos.y;
    }
    if (IsKeyPressed(KEY_S)) {
        player->transform.pos.y += player->transform.velocity.y;
        player->shape.rec.y = player->transform.pos.y;
    } 

}


