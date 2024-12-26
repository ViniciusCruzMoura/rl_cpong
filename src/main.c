#include "rlcpong.h"

int main(void) 
{
    struct game_instance g;
    initialize_game(&g);

    struct ini_file_config *conf = create_config();
    parse_ini_file(CONF_INIFILE_PATH, conf);
    /**
    const char* m_language = get_value_ini_file(conf, "General", "sLanguage");
    const char* m_fullscreen_enabled = get_value_ini_file(conf, "RenderWindow", "bFullscreen");
    const char* m_res_width = get_value_ini_file(conf, "RenderWindow", "iResWidth");
    const char* m_res_height = get_value_ini_file(conf, "RenderWindow", "iResHeight");
    const char* m_difficulty = get_value_ini_file(conf, "Gameplay", "iDifficulty");
    */
    const char* m_runtests_enabled = get_value_ini_file(conf, "DevTools", "bRunTestsEnabled");
    const bool tests_enabled = !strcmp(m_runtests_enabled, "1");
    if (tests_enabled) {
        execute_test_suite();
    }
    free_config(conf);

    /**
    struct ini_file_config *lang = create_config();
    if (strcmp(tmp_language, "ENG")) {
        parse_ini_file("assets/strings/en-us.ini", conf);
    }
    free_config(lang);
    */

    DEBUG_PRINT("Initialization: game_instance \n");
    game_loop(&g);
    return 0;
}
