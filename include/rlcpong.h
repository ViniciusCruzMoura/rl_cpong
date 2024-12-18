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

// Compile-time control (this can be set by the compiler/build system)
#define SCREEN_WIDTH 4*200
#define SCREEN_HEIGHT 3*200
#define SCREEN_FRAMERATE 30
#define SCREEN_TITLE "RlCPong"
#define CONF_INIFILE_PATH "conf.ini"
#define DEBUG_ENABLED 1

#define SAFE_FREE(p) { if (p) { free(p); (p) = NULL; } }

#if defined(DEBUG_ENABLED) && DEBUG_ENABLED > 0
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
        __FILE__, __LINE__, __func__, ##args)
#else
#define DEBUG_PRINT(fmt, args...) /* No debug printing in release builds */
#endif

typedef struct Game {
    RenderWindow m_windows;
    EntityManager m_entities;
    bool m_paused;
    bool m_running;
    uint32_t m_current_frame;
} Game;

void init_game(Game *g);
void run(Game *g);
void sys_render(Game *g);
void sys_user_input(Game *g);

void spawn_player(EntityManager *em);

#endif //GAME_H
