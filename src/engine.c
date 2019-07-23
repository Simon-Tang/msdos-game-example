#include "engine.h"
#include "screen.h"
#include "keyboard.h"


int init_engine(void)
{
    if (enter_mode13h()) {
        return 1;
    }

    init_keyboard();
    
    return 0;
}


int exit_engine(void)
{
    deinit_keyboard();
    leave_mode13h();
    return 0;
}
