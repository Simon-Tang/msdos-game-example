#ifndef __MODULE_KEYBOARD__
#define __MODULE_KEYBOARD__

void init_keyboard(void);
void deinit_keyboard(void);

typedef struct {
    unsigned char key_code;
    int is_keydown;
} KeyEvent;

int get_keyevent(KeyEvent *keyevent);

#endif