#include <video.h>
#include <string.h>
#include <x86.h>

char *video_memory = (char*) VIDEO_MEMORY_ADDR;

void
video_init()
{
    char buff[VIDEO_SCREEN_SIZE];

    video_disable_cursor();
    video_clear(buff);
    video_flush(buff);
}

void
video_disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void
video_clear(char *video_buff)
{
    int i;

    for (i = 0; i < VIDEO_SCREEN_SIZE; ++i)
        *video_buff++ = ' ';
}

void
video_flush(char *video_buff)
{
    char buff[2 * VIDEO_SCREEN_SIZE];

    memext(buff, VIDEO_SCREEN_SIZE, video_buff, 0x7);
    memcpy((void*)video_memory, buff, 2 * VIDEO_SCREEN_SIZE);
}



