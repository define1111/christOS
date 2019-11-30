#include <stdio.h>
#include <string.h>
#include <video.h>

static void console_flush(void);
static void console_scroll_up(void);

char console_screen[VIDEO_SCREEN_SIZE];
int console_cur_pos;

void
console_init()
{
    video_init();
    console_cur_pos = 0;
    memset(console_screen, ' ', VIDEO_SCREEN_SIZE);
}

void
printf(const char *format, ...)
{
    va_list list;
    va_start(list, format);

    vprintf(format, list);
}

void
vprintf(const char *format, va_list list)
{
    char buff[VIDEO_SCREEN_WIDTH];
    int len = vsprintf(buff, format, list);
    int i, j, k;

    if (console_cur_pos >= VIDEO_SCREEN_SIZE - VIDEO_SCREEN_WIDTH)
        console_scroll_up();

    for (i = 0, k = 0; i < len; ++i, ++k)
    {
        if (buff[i] == '\n')
        {   
            for (j = k; j < VIDEO_SCREEN_WIDTH; ++j)
            {
                console_screen[console_cur_pos] = ' ';
                console_cur_pos++;
            }
            
            k = -1;
        }
        else
        {
            console_screen[console_cur_pos] = buff[i];
            console_cur_pos++;
        }
    }

    console_flush();
}

static void
console_scroll_up()
{
    int i, j;

    for (i = 1; i < VIDEO_SCREEN_HEIGHT; ++i) 
        for (j = 0; j < VIDEO_SCREEN_WIDTH; ++j) 
            console_screen[(i - 1) * VIDEO_SCREEN_WIDTH + j] = console_screen[i * VIDEO_SCREEN_WIDTH + j];

    for (j = 0; j < VIDEO_SCREEN_WIDTH; ++j) 
        console_screen[(VIDEO_SCREEN_HEIGHT - 1) * VIDEO_SCREEN_WIDTH + j] = ' ';

    console_cur_pos -= VIDEO_SCREEN_WIDTH;
}

static void
console_flush()
{
    video_flush(console_screen);
}
