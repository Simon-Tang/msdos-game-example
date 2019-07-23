#include "engine.h"
#include "screen.h"
#include "keyboard.h"

/* Temporary - sound/nosound come from here */
#include <dos.h>

int main(void)
{
    unsigned int y, x;
    KeyEvent key_event;

    if (init_engine()) {
        return 1;
    }

    for (y = 0; y < SCREEN_H; y++) {
        line_h(0, y, SCREEN_W, 256 * y / SCREEN_H);
        if (y % (SCREEN_H / 16) == 0) {
            repaint();
        }
    }
    repaint();

    for (y = 0; y < 100; y++) {
        line_h(100, y, 5, 15);
    }
    repaint();

    for (y = 100; y < 160; y++) {
        line_h(150, y, 5, 13);
    }
    repaint();

    for (x = 40; x < 150; x+=2) {
        line(x, 50, x, 90, 12);
    }
    repaint();

    rect_fill(130, 80, 48, 64, 10);
    repaint();

    for (y = 50; y < SCREEN_H; y+=4) {
        x = y / 1.8 + 25;
        line(x, y, SCREEN_W - x, SCREEN_H - y, 30);
        repaint();
    }

    x = 0;
    y = 0;
    while (1) {
        if (get_keyevent(&key_event)) {
            if (key_event.key_code == 0x01) {
                /* ESC */
                break;
            } else if (key_event.key_code == 0x39) {
                /* Space */
                nosound();
            }
            if (key_event.is_keydown) {
                rect_fill(
                    x * SCREEN_W / 16,
                    y * SCREEN_H / 12,
                    SCREEN_W / 16,
                    (SCREEN_H + 11) / 12,
                    key_event.key_code
                );
                if (++x >= 16) {
                    x = 0;
                    y = (y + 1) % 12;
                }
                sound(key_event.key_code * 4);
            }
        }
        repaint();
    }
    exit_engine();
    return 0;
}
