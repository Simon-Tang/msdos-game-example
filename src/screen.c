#include <stdlib.h>
#include <mem.h>
#include <dos.h>
#include "screen.h"

#define VIDEO_INT 0x10
#define SET_MODE 0x00
#define VGA_256_COLOR_MODE 0x13
#define INPUT_STATUS_1 0x03da
#define VRETRACE 0x08

unsigned char far *VGA_MEM = (unsigned char *)0xA0000000L;
unsigned char far *VGA_BUF;

int old_mode;


int enter_mode13h(void)
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

    /* Allocate memory for screen buffer */
    VGA_BUF = malloc(SCREEN_SIZE);
    if (VGA_BUF) {
        memset(VGA_BUF, 10, SCREEN_SIZE);
    } else {
        leave_mode13h();
        return 1;
    }

    return 0;
}


void leave_mode13h(void)
{
    union REGS in, out;

    /* Revert to old video mode */
    in.h.ah = 0;
    in.h.al = old_mode;
    int86(VIDEO_INT, &in, &out);
}  


void repaint(void)
{
    while ((inportb(INPUT_STATUS_1) & VRETRACE));
    while (!(inportb(INPUT_STATUS_1) & VRETRACE));
    memcpy(VGA_MEM, VGA_BUF, SCREEN_SIZE);
}

/* Bresenham's line drawing algorithm */
/* http://www3.telus.net/alexander_russell/course/chapter_2.htm */
void line(int x0, int y0, int x1, int y1, unsigned char color)
{
    int inc1, inc2, i;
    int cnt, y_adj, dy, dx, x_adj;
    unsigned char far *p;

    if (x0 == x1) {
        if (y0 > y1) {
            i = y0;
            y0 = y1;
            y1 = i;
        }

        p = VGA_BUF + get_pixel_offset(x0, y0);
        i = y1 - y0 + 1;
        while (i--) {
            *p = color;
            p += SCREEN_W;
        }
    } else {
        if (y0 == y1) {
            if (x0 > x1) {
                i = x0;
                x0 = x1;
                x1 = i;
            }
            p = VGA_BUF + get_pixel_offset(x0, y0);
            i = x1 - x0 + 1;
            memset(p, color, i);
        } else {
            dy = y1 - y0;
            dx = x1 - x0;
            if (abs(dy) < abs(dx)) {
                if (x0 > x1) {
                    i = x0;
                    x0 = x1;
                    x1 = i;
                    i = y0;
                    y0 = y1;
                    y1 = i;
                }
                dy = y1 - y0;
                dx = x1 - x0;
                if (dy < 0) {
                    dy = -dy;
                    y_adj = -SCREEN_W;
                }
                else {
                    y_adj = SCREEN_W;
                }
                    

                inc1 = dy << 1;
                inc2 = (dy - dx) << 1;
                cnt = (dy << 1) - dx;

                p = VGA_BUF + get_pixel_offset(x0, y0);
                dx++;
                while (dx--) {
                    *p++ = color;

                    if (cnt >= 0) {
                        cnt += inc2;
                        p += y_adj;
                    } else {
                        cnt += inc1;
                    }
                }
            } else {
                if (y0 > y1) {
                    i = x0;
                    x0 = x1;
                    x1 = i;
                    i = y0;
                    y0 = y1;
                    y1 = i;
                }

                dy = y1 - y0;
                dx = x1 - x0;

                if (dx < 0) {
                    dx = -dx;
                    x_adj = -1;
                } else {
                    x_adj = 1;
                }

                inc1 = dx << 1;
                inc2 = (dx - dy) << 1;
                cnt = (dx << 1) - dy;

                p = VGA_BUF + get_pixel_offset(x0, y0);
                dy++;

                while (dy--) {
                    *p = color;
                    p += SCREEN_W;

                    if (cnt >= 0) {
                        cnt += inc2;
                        p += x_adj;
                    } else {
                        cnt += inc1;
                    }
                }
            }
        }
    }
}


void rect_fill(int x, int y, int w, int h, unsigned char color)
{
    while (h--) {
        line_h(x, y, w, color);
        y++;
    }
}

