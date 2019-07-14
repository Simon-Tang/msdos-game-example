#include <dos.h>

#define VIDEO_INT 0x10
#define SET_MODE 0x00
#define VGA_256_COLOR_MODE 0x13
#define SCREEN_W 320
#define SCREEN_H 200
#define NUM_COLORS 256

#define put_pixel(x, y, color) VGA[(y << 8) + (y << 6) + x] = color

int old_mode;

unsigned char far *VGA = (unsigned char *)0xA0000000L;
unsigned short *CLOCK = (unsigned short *)0x0000046C;

void enter_mode13h(void)
{
    union REGS in, out;

    /* Save old video mode */
    in.h.ah = 0xf;
    int86(VIDEO_INT, &in, &out);
    old_mode = out.h.al;

    /* Enter mode 13h */
    in.h.ah = 0;
    in.h.al = VGA_256_COLOR_MODE;
    int86(VIDEO_INT, &in, &out);
}

void leave_mode13h(void)
{
    union REGS in, out;

    /* Revert to old video mode */
    in.h.ah = 0;
    in.h.al = old_mode;
    int86(VIDEO_INT, &in, &out);
}

int main(int argc, char const *argv[])
{
    unsigned int y, x;

    enter_mode13h();

    for (y = 0; y < SCREEN_H; y++)
    {
        for (x = 0; x < SCREEN_W; x++)
        {
            put_pixel(x, y, 256 * y / SCREEN_H);
        }
    }

    sleep(5);
    leave_mode13h();
    return 0;
}
