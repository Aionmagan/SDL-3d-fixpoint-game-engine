#ifndef PC1INPUT_H
#define PC1INPUT_H

#include <SDL.h>

enum KEYCODE
{
    KEY_UKWN= 0,
    
    A = 0x61,
    B = 0x62,
    C = 0x63,
    D = 0x64,
    E = 0x65,
    F = 0x66,
    G = 0x67,
    H = 0x68,
    I = 0x69,
    J = 0x6A,
    K = 0x6B,
    L = 0x6C,
    M = 0x6D,
    N = 0x6E,
    O = 0x6F,
    P = 0x70,
    Q = 0x71,
    R = 0x72,
    S = 0x73,
    T = 0x74,
    U = 0x75,
    V = 0x76,
    W = 0x77,
    X = 0x78,
    Y = 0x79,
    Z = 0x7A,

    KEY_1 = 0x30,
    KEY_2 = 0x31,
    KEY_3 = 0x32,
    KEY_4 = 0x33,
    KEY_5 = 0x34,
    KEY_6 = 0x35,
    KEY_7 = 0x36,
    KEY_8 = 0x37,
    KEY_9 = 0x38,
    KEY_0 = 0x39,

    RETURN = 0x0D ,
    ESCAPE = 0x1B,
    BACKSPACE = 0x08,
    TAB = 0x09 ,
    SPACE = 0x20,

    RIGHT = 0x4000004F,
    LEFT = 0x40000050,
    DOWN = 0x40000051,
    UP = 0x40000052,
};

class pc1INPUT
{
private:
    const Uint8 *keyboard_State;
    SDL_Event e;
public:
    pc1INPUT(void);
    ~pc1INPUT();
    
    bool IsKeyPress(KEYCODE key);

};

#endif // PC1INPUT_H
