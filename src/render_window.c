#include "rlcpong.h"

void create_window(RenderWindow *rw)
{
    if (!rw) 
    {
        die("fatal: render_window not initialized\n");
    }
    InitWindow(rw->m_width, rw->m_height, rw->m_title);
}

void close_window(RenderWindow *rw)
{
    if (!rw) 
    {
        die("fatal: render_window not initialized\n");
    }
    CloseWindow();
}

bool is_open_window(RenderWindow *rw)
{
    return !WindowShouldClose();
}


