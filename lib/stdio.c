#include <stdio.h>
#include <string.h>
#include <video.h>

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
    int i;

    for (i = 0; i < VIDEO_SCREEN_SIZE; i += 2)
        buff[i] = 0x0;
    
    vsprintf(buff, format, list);

    video_flush(buff);
}
