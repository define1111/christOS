#ifndef INC_VIDEO_H
#define INC_VIDEO_H

#include <stdint.h>
#include <stdbool.h>

#define VIDEO_SCREEN_WIDTH (80)
#define VIDEO_SCREEN_HEIGHT (25)
#define VIDEO_SCREEN_SIZE (VIDEO_SCREEN_WIDTH * VIDEO_SCREEN_HEIGHT)

#define VIDEO_MEMORY_ADDR (0xB8000)

/* copy buffer to screen */
void video_flush(char *video_buff);

void video_init(void);
void video_disable_cursor(void);
void video_clear(char *video_buff);

#endif
