#ifndef PC1GFX_H
#define PC1GFX_H

#include <SDL.h>
#include "pc1FIXPOINTMATH.h"

//temp
#include "pc1VECTORMATH.h"

class pc1GFX
{
private:
   SDL_Surface *g_offScreenBuffer;
   SDL_Surface *g_screen;
   Uint32 color; 
   
   //const pc1TEXTUREMAP *curent_map;
   //void SetCurrentMap( const pc1TEXTUREMAP *map);
   
   void TMHLine(FixedPoint_t x1, FixedPoint_t x2,
                FixedPoint_t u1, FixedPoint_t u2,
                FixedPoint_t v1, FixedPoint_t v2, int y);
                
    void FB_Triangle(int x1, int y1, int x2, int y23, int x3);
    
   /*void FB_TMTriangle(int x1, int y1,  int u1, int v1,
                      int x2, int y23, int u2, int v2,
                      int x3, int ,    int u3, int v3,
                      const pc1TEXTUREMAP &map); */
public:
    pc1GFX(int width, int height, int bytePerPixel);
    ~pc1GFX();

    //basic surface modifications
    void BlitBuffer();
    void ClearScreen(Uint8 r, Uint8 g, Uint8 b);
    void ClearScreen();
    void UpdateScreen();
    
    //algorithm for drawing
    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b);
    void PlotPixel(int x, int y);
    void HLine(int x1, int x2, int y);
    void VLine(int y1, int y2, int x);
    
    //suptitude with pc1ScreenVertex
    void Triangle(const pc1VECTOR3 &a, const pc1VECTOR3 &b, const pc1VECTOR3 &c);
};

#endif // PC1GFX_H
