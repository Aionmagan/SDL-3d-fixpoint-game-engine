#include "pc1GFX.h"

pc1GFX::pc1GFX(int width, int height, int bytePerPixel)
{
    SDL_Init(SDL_INIT_VIDEO);
    
    g_screen = SDL_SetVideoMode(width, height, bytePerPixel, SDL_NOFRAME);
    g_offScreenBuffer = SDL_DisplayFormat(g_screen);
    
    SetDrawColor(0,0,0);
}

pc1GFX::~pc1GFX()
{
    SDL_Quit();
}

void pc1GFX::BlitBuffer()
{
    SDL_BlitSurface(g_offScreenBuffer, NULL, g_screen, NULL);
}

void pc1GFX::ClearScreen(Uint8 r, Uint8 g, Uint8 b)  
{
    Uint32 color = SDL_MapRGB(g_offScreenBuffer->format, r, g, b);
    SDL_FillRect(g_offScreenBuffer, NULL, color);
}

void pc1GFX::ClearScreen()  
{
    ClearScreen(0,0,0);
}

void pc1GFX::UpdateScreen()
{
    SDL_Flip(g_screen);
}

void pc1GFX::SetDrawColor(Uint8 r, Uint8 g, Uint8 b)
{
    color = SDL_MapRGB(g_screen->format, r, g, b);
}

void pc1GFX::PlotPixel(int x, int y)
{
    //printf("d%, d% hello world", x, y);
    Uint32 *buffp;
    buffp = (Uint32 *) g_offScreenBuffer->pixels;
    buffp[(y * g_offScreenBuffer->w) + x] = color;
}

void pc1GFX::HLine(int x1, int x2, int y)
{
    //make sure y is within screen
    if(y >= 0 && y < g_offScreenBuffer->h)
    {
        //make sure x1 < x2
        if(x1 > x2)
        {
            int temp = x1; 
            x1 = x2;
            x2 = temp;
        }
        
        //make sure part of the line is inside the screen
        if(!(x1 < 0 && x2 < 0) && 
           !(x1 > g_offScreenBuffer->w-1 && x2 > g_offScreenBuffer->w-1))
        {
            //clamp values horizontally
            if(x1 < 0) x1 = 0;
            if(x2 > g_offScreenBuffer->w-1) x2 = g_offScreenBuffer->w-1;
            
            //render line
            //this did not work
            //memset(surface->pixels + y * surface->w + x1, color, x2-x1+1);
            
            for(int i = x1; i < x2; ++i)
            {
                //PlotPixel(i, y, color);
                PlotPixel(i, y);
            }
        }
        
        pc1GFX::BlitBuffer();
    }
}

void pc1GFX::VLine(int y1, int y2, int x)
{
     //make sure line is inside screen 
    if(x >= 0 && x < g_offScreenBuffer->w)
    {
        //make sure y1 < y2
        if(y1 > y2)
        {
            int temp = y1; 
            y1 = y2; 
            y2 = temp;
        }
        
        //make sure the line is in screen
        if(!(y1 < 0 && y2 < 0) &&
           !(y1 > g_offScreenBuffer->h-1 && y2 > g_offScreenBuffer->h-1))
        {
            //clamp values veritcally
            if(y1 < 0) y1 = 0;
            if(y2 > g_offScreenBuffer->h-1) y2 =g_offScreenBuffer->h-1;
            
            //render
            for(int i = y1; i < y2; ++i)
            {
                //PlotPixel(x, i, color);
                PlotPixel(x, i);
            }
        }
        
        pc1GFX::BlitBuffer();
    }
}

void pc1GFX::FB_Triangle(int x1, int y1, int x2, int y23, int x3)
{
    FixedPoint_t dxLeft, dxRight;
    FixedPoint_t curxLeft, curxRight;
    FixedPoint_t height = y23 - y1;
    
    //printf("%d,%d,%d", height, y23, y1);
    if(height == 0){return;}
    
    //determine the slope for X for left and right sides
    dxLeft = ConvertToFix(x2 - x1) / height;
    dxRight = ConvertToFix(x3 - x1) / height;
    
    curxLeft = curxRight = ConvertToFix(x1);
    
    //draw each scan line from top to bottom
    if(y1 < y23)
    {
        for(int y = y1; y <= y23; y++)
        {
            HLine(ConvertToInt(curxLeft), ConvertToInt(curxRight), y);
            
            curxLeft += dxLeft;
            curxRight += dxRight;
        }
    }else{
        for(int y = y1; y >= y23; y--)
        {
            HLine(ConvertToInt(curxLeft), ConvertToInt(curxRight), y);
            
            curxLeft -= dxLeft;
            curxRight -= dxRight;
        }
    }
}

void pc1GFX::Triangle(const pc1VECTOR3 &a, const pc1VECTOR3 &b, const pc1VECTOR3 &c)
{
    //cache 
    int x1 = ConvertToInt(a.x), x2 = ConvertToInt(b.x), x3 = ConvertToInt(c.x);
    int y1 = ConvertToInt(a.y), y2 = ConvertToInt(b.y), y3 = ConvertToInt(c.x);
    int temp;
    
    //sort vertices from top to buttom 
    if(y3 < y1)
    {
        temp = y3;
        y3 = y1;
        y1 = temp;
        
        temp = x3;
        x3 = x1;
        x1 = temp;
    }
    
    if(y2 < y1)
    {
        temp = y2;
        y2 = y1;
        y1 = temp;
        
        temp = x2;
        x2 = x1;
        x1 = temp;
    }
    
    if(y3 < y2)
    {
        temp = y3;
        y3 = y2;
        y2 = temp;
        
        temp = x3;
        x3 = x2;
        x2 = temp;
    }

    //split triangle if no horizontal edges 
    if(y1 != y2 && y1 != y3 && y2 != y3)
    {
        int newX;
        FixedPoint_t ratio = 0;
        
        //determine new x value
        //newX = (x3 - x1) * ((y2 - y1) / (y3 - y1)) + x1;

        //precompute the ratio of (y2-y1)/(y3-y1)
        ratio = FixDivition(ConvertToFix(y2 - y1),
                            ConvertToFix(y3 - y1));
                           
        //new x = ((x3 - x1) * ratio) + x1
        newX = ConvertToInt(FixMultiply(ConvertToFix(x3 - x1), ratio)) + x1;
        //printf("%d,%d", newX, ratio);
        //draw two subtriangles 
        if(newX < x2)
        {
            FB_Triangle(x1, y1, newX, y2, x2);
            FB_Triangle(x3, y3, x2, y2, newX);
        }else{
            FB_Triangle(x1, y1, x2, y2, newX);
            FB_Triangle(x3, y3, x2, y2, newX);
        }
    }/*else if(y1 == y2)
    {
        if(x1 < x2)
        {
            FB_Triangle(x3, y3, x2, y2, x1);
        }else{
            FB_Triangle(x3, y3, x1, y2, x2);
        }
    }else if(y2 == y3)
    {
        if(x2 < x3)
        {
            FB_Triangle(x1, y1, x2, y2, x3);
        }else{
            FB_Triangle(x1, y1, x3, y2, x1);
        }
    }
    */
    
}