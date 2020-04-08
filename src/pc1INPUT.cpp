#include "pc1INPUT.h"
 
pc1INPUT::pc1INPUT()
{
    //SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    keyboard_State = SDL_GetKeyState(NULL);
}

pc1INPUT::~pc1INPUT()
{
}

bool pc1INPUT::IsKeyPress(KEYCODE key)
{
    SDL_PumpEvents();
    return keyboard_State[key];
}