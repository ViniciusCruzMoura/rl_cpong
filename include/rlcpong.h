#ifndef GAME_H 
#define GAME_H 

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "raylib.h"
#include "raymath.h"
#include "entity.h"
#include "entity_manager.h"
#include "inifile_parser.h"

/*
=============================================================================

                            MACROS

=============================================================================
*/

#define DEBUG_ENABLED 1
#define SAFE_FREE(p) { if (p) { free(p); (p) = NULL; } }
#if defined(DEBUG_ENABLED) && DEBUG_ENABLED > 0
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
        __FILE__, __LINE__, __func__, ##args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

/*
=============================================================================

                         GLOBAL CONSTANTS

=============================================================================
*/

#define SCREEN_FACTOR 200
#define SCREEN_WIDTH 4 * SCREEN_FACTOR
#define SCREEN_HEIGHT 3 * SCREEN_FACTOR
#define CONF_INIFILE_PATH "conf.ini"

/*
=============================================================================

                           GLOBAL TYPES

=============================================================================
*/

struct game_config {
    char *m_language;
    bool m_fullscreen;
    bool m_fxaa_enabled;
    uint32_t m_width;
    uint32_t m_height;
    bool m_debug_enabled;
    bool m_runtests_enabled;
    uint32_t m_difficulty;
};

struct render_window {
    char *m_title;
    size_t m_width;
    size_t m_height;
    size_t m_framerate_limit;
    bool m_fullscreen_enabled;
};

struct game_instance {
    struct render_window m_windows;
    struct entity_manager m_entities;
    bool m_paused;
    bool m_running;
    uint32_t m_current_frame;
    struct game_config m_config;
};

/*
=============================================================================

                         render_window DEFINITIONS

=============================================================================
*/

void create_window(struct render_window *rw);
void close_window(struct render_window *rw);
bool is_open_window(struct render_window *rw);

/*
=============================================================================

                         rlcpong DEFINITIONS

=============================================================================
*/

void execute_test_suite(void);
void initialize_game(struct game_instance *g);
void game_loop(struct game_instance *g);
void render_frame(struct game_instance *g);
void handle_input(struct game_instance *g);
void update_game_state(struct game_instance *g);

void spawn_player(struct entity_manager *em);
void spawn_enemy(struct entity_manager *em);
void spawn_ball(struct entity_manager *em);

#endif //GAME_H
