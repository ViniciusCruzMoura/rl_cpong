#include "rlcpong.h"

int main(void) 
{
    //ativar o debug via config.ini
    //ativar os tests via config.ini
    DEBUG_PRINT("Hello World !! \n");
#if RUNTESTS_ACTIVATED
    tests_run();
#else
    Game g;
    init_game(&g);
    run(&g);
    return 0;
#endif
}
