#include <dos.h>
#include "keyboard.h"

/*
 * Keyboard scanning + utils
 * http://www3.telus.net/alexander_russell/course/chapter_4.htm
 */

#define KB_INT 0x09
#define KEY_UP_MASK 0x80
#define KEY_ALL_MASK 0x7f

/* Original BIOS keyboard handler */
static void interrupt (far *bios_kb_handler)(void);

/* Circular queue for keyboard scan codes */
unsigned char kb_scan_q[256];
unsigned char kb_scan_temp;
unsigned char kb_scan_head;
unsigned char kb_scan_tail;


/*
 * Invoked by keyboard interrupt (KB_INT)
 * Inserts a scancode into kb_scan_q
*/
void interrupt scan_keyboard(void)
{
    asm  cli
    asm  in  al, 060h
    asm  mov kb_scan_temp, al
    asm  in  al, 061h
    asm  mov bl, al
    asm  or  al, 080h
    asm  out 061h, al
    asm  mov al, bl
    asm  out 061h, al
    asm  mov al, 020h
    asm  out 020h, al
    asm  sti

    kb_scan_q[kb_scan_tail++] = kb_scan_temp;
}


void init_keyboard(void)
{
    unsigned char far *bios_key_state;

    /* Save BIOS keyboard handler to restore later */
    bios_kb_handler = getvect(KB_INT);

    /* Set custom keyboard handler */
    kb_scan_head = 0;
    kb_scan_tail = 0;
    setvect(KB_INT, scan_keyboard);
}


void deinit_keyboard(void)
{
    /* Restore BIOS keyboard handler */
    setvect(KB_INT, bios_kb_handler);
}


int get_keyevent(KeyEvent *keyevent)
{
    unsigned char kb_scan;
    while (kb_scan_head != kb_scan_tail) {
        kb_scan = kb_scan_q[kb_scan_head++];
        
        /* Keypad keys may emit extra 0xe0 events - safe to ignore */
        if (kb_scan == 0xe0) {
            continue;
        }

        keyevent->key_code = kb_scan & KEY_ALL_MASK;
        keyevent->is_keydown = !(kb_scan & KEY_UP_MASK);

        return 1;
    }
    return 0;
}