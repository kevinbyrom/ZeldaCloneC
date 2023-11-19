#include <Allegro.h>
#include "Input.h"


INPUT Input;


INPUT::INPUT()
    {
    key_left    = KEY_LEFT;
    key_right   = KEY_RIGHT;
    key_up      = KEY_UP;
    key_down    = KEY_DOWN;
    }


void INPUT::Poll()
    {
    poll_joystick();
    }


int INPUT::A()
    {
    if (key[key_A] || joy_b1)
       return 1;

    return 0;
    }


int INPUT::B()
    {
    return 0;
    }


int INPUT::Left()
    {
    if (key[key_left] || joy_left)
       return 1;

    else return 0;
    }


int INPUT::Right()
    {
    if (key[key_right] || joy_right)
       return 1;

    else return 0;
    }


int INPUT::Up()
    {
    if (key[key_up] || joy_up)
       return 1;

    else return 0;
    }


int INPUT::Down()
    {
    if (key[key_down] || joy_down)
       return 1;

    else return 0;
    }
