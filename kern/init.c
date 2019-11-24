void
i386_init(void)
{
    char *screen_buffer = (void*) 0xB8000;
    char *msg = "And kernel become";
    unsigned int i = 24 * 80;

    while (*msg)
    {
        screen_buffer[i * 2] = *msg;
        msg++;
        i++;
    }
}
