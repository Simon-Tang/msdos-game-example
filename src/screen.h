#ifndef __MODULE_SCREEN__
#define __MODULE_SCREEN__

#define SCREEN_W 320
#define SCREEN_H 200
#define SCREEN_SIZE 64000
#define NUM_COLORS 256

extern unsigned char far *VGA_BUF;

int enter_mode13h(void);
void leave_mode13h(void);

void repaint(void);

#define get_pixel_offset(x, y) (y << 8) + (y << 6) + x
#define put_pixel(x, y, color) VGA_BUF[get_pixel_offset(x, y)] = color
#define line_h(x, y, w, color) memset(VGA_BUF + get_pixel_offset(x, y), color, w)
void line(int x0, int y0, int x1, int y1, unsigned char color);
void rect_fill(int x, int y, int w, int h, unsigned char color);

#endif