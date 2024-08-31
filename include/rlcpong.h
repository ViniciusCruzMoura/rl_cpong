#ifndef GAME_H 
#define GAME_H 

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "raylib.h"
#include "utils.h"
#include "render_window.h"
#include "components.h"
#include "entity.h"
#include "entity_manager.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FRAMERATE 30
#define SCREEN_TITLE "RlCPong"

typedef struct Game {
    RenderWindow m_windows;
    EntityManager m_entities;
    bool m_paused;
    bool m_running;
    int m_current_frame;
} Game;

void init_game(Game *g);
void run(Game *g);
void sys_render(Game *g);
void sys_user_input(Game *g);
void spawn_player(EntityManager *em);

#endif //GAME_H
