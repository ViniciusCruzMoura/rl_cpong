#include "rlcpong.h"

void create_window(struct render_window *rw)
{
    InitWindow(rw->m_width, rw->m_height, rw->m_title);
}

void close_window(struct render_window *rw)
{
    CloseWindow();
}

bool is_open_window(struct render_window *rw)
{
    return !WindowShouldClose();
}


