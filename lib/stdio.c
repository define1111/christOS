#include <stdio.h>
#include <string.h>
#include <video.h>

char console_screen[VIDEO_SCREEN_SIZE];

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
    char buff[VIDEO_SCREEN_SIZE];
    
    vsprintf(buff, format, list);

    int len = strlen(buff);
    int i;

    for (i = len; i < VIDEO_SCREEN_SIZE; ++i)
    {
        buff[i] = ' ';
    }

    video_flush(buff);
}
