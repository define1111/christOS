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

/* char *
video_scroll(char *video_buff, char *pos)
{
    int i, j;

    for (i = 1; i < VIDEO_SCREEN_HEIGHT; ++i)
        for (j = 0; j < VIDEO_SCREEN_WIDTH; ++j)
            video_buff[(i - 1) * VIDEO_SCREEN_WIDTH + j] = video_buff[i * VIDEO_SCREEN_WIDTH + j];

    for (j = 0; j < VIDEO_SCREEN_WIDTH; ++j)
        video_buff[(VIDEO_SCREEN_HEIGHT - 1) * VIDEO_SCREEN_WIDTH + j] = ' ';

    return pos;
} */

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



