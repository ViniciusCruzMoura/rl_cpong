#ifndef GAME_H 
#define GAME_H 

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "raylib.h"
#include "types.h"
#include "utils.h"
#include "render_window.h"
#include "components.h"
#include "entity.h"
#include "entity_manager.h"
#include "inifile_parser.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FRAMERATE 30
#define SCREEN_TITLE "RlCPong"

#define RUNTESTS_ACTIVATED 0 //*experimental feature to run the 'tests/'
#define DEBUG_ACTIVATED 1 //*experimental feature to show prints in the console

#if defined(DEBUG_ACTIVATED) && DEBUG_ACTIVATED > 0
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
        __FILE__, __LINE__, __func__, ##args)
#else
#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif
#define SAFE_FREE(p) { if (p) { free(p); (p) = NULL; } }

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
