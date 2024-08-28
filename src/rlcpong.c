#include "rlcpong.h"

void init_game(Game *g)
{
    g->m_paused = false;
    g->m_running = true;
    g->m_current_frame = 0;
    g->m_windows = (RenderWindow){ .m_width=SCREEN_WIDTH, 
        .m_height=SCREEN_HEIGHT, 
        .m_framerate_limit=SCREEN_FRAMERATE,
        .m_title=SCREEN_TITLE };
    g->m_entities = (EntityManager){ .m_total_entities=0};
}

void run(Game *g)
{
    if (!g)
    {
        die("fatal: game not initialized\n");
    }
    create_window(&g->m_windows);
    spawn_player(&g->m_entities);
    while (g->m_running)
    {
        update_entities(&g->m_entities);
        if (!g->m_paused)
        {
            //spawn_enemy();
            //movement();
            //collision();
        }
        sys_user_input(g);
        sys_render(g);
        ++g->m_current_frame;
    }
    close_window(&g->m_windows);
}

void spawn_player(EntityManager *em)
{
    Entity *e = add_entity(em, "player", ENTITY_TYPE_PLAYER);
    //printf("%li : %s \n", e->m_id, e->m_tag);
}

void sys_render(Game *g)
{
    if (!g)
    {
        die("fatal: game not initialized\n");
    }
    BeginDrawing();

    ClearBackground(BLACK);
    DrawText("Render: OpenGL screen", 190, 200, 30, WHITE);

    char buf[1024];
    snprintf(buf, 1024,
            "Debug:\n" \
            "- GetMonitorWidth: (%d)\n" \
            "- GetMonitorHeight: (%d)\n"
            , GetMonitorWidth(GetCurrentMonitor())
            , GetMonitorHeight(GetCurrentMonitor()));
    DrawText(TextFormat(buf), 0, 0, 10, WHITE);

    EndDrawing();
}

void sys_user_input(Game *g)
{
    if (!g)
    {
        die("fatal: game not initialized\n");
    }
    if (!is_open_window(&g->m_windows))
    {
        g->m_running = false;
    }

    for (int i=0; i <= MAX_ENTITY_MAP_COLUMNS; ++i)
    {
        Entity *e = g->m_entities.m_map[ENTITY_TYPE_PLAYER][i];
        if (!e) continue;
        //printf("%s : %li\n", e->m_tag, e->m_id);
    }

    if (IsKeyPressed(KEY_S)) {
        printf("S Key Pressed\n");
    } 
    if(IsKeyPressed(KEY_W)) { 
        printf("W Key Pressed\n");
    }
    if (IsKeyPressed(KEY_D)) {
        printf("D Key Pressed\n");
    } 
    if (IsKeyPressed(KEY_A)) {
        printf("A Key Pressed\n");
    }

    if (IsKeyReleased(KEY_S)) {
        printf("S Key Released\n");
    } 
    if(IsKeyReleased(KEY_W)) { 
        printf("W Key Released\n");
    }
    if (IsKeyReleased(KEY_D)) {
        printf("D Key Released\n");
    } 
    if (IsKeyReleased(KEY_A)) {
        printf("A Key Released\n");
    }

    if (IsKeyPressed(KEY_SPACE)) {
        printf("SPACE Key Released\n");
        g->m_paused = !g->m_paused;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        printf("MOUSE_BUTTON_LEFT Key Pressed");
        printf(" at ( %i , %i )\n", GetMouseX(), GetMouseY());
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        printf("MOUSE_BUTTON_RIGHT Key Pressed");
        printf(" at ( %i , %i )\n", GetMouseX(), GetMouseY());
    }
}


