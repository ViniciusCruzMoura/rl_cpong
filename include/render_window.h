#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

typedef struct RenderWindow {
    char *m_title;
    size_t m_width;
    size_t m_height;
    size_t m_framerate_limit;
} RenderWindow;

void create_window(RenderWindow *rw);
void close_window(RenderWindow *rw);
bool is_open_window(RenderWindow *rw);

#endif // RENDER_WINDOW_H
