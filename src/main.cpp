#include <stdio.h>
#include <cstring>
#include <cmath>
//#include <SDL.h>
#include <time.h>
#include "pc1.h"

int main(int argc, char **argv)
{
    pc1GFX g_graphics(640, 480, 32);
    g_graphics.ClearScreen(255,255,255);
    g_graphics.SetDrawColor(0,255,255);
    
    pc1INPUT input;
    
    pc1MATRIX4X3 matrix, rm;
    pc1VECTOR3 vec1, vec2, vec3;

    //vec1.SetPosition(2.0f, 100.0f, 67.0f);
   // vec2.SetPosition(54.0f, 78.0f, 90.0f);
   // vec3.SetPosition(102.0f, 234.0f, 234.0f);
    
    srand (time(NULL));
    int random = rand() % 10 + 1;
    int rot = 1;
    
    while(input.IsKeyPress(ESCAPE)!= true)
    {
        \
       
        
        vec1.SetPosition(2.0f+rot, 100.0f+10*sin(rot), 67.0f);
        vec2.SetPosition(54.0f+rot, 78.0f, 90.0f);
        vec3.SetPosition(102.0f, 234.0f, 234.0f);
        
        g_graphics.Triangle(vec1, vec2, vec3);
        //random = rand() % 10 + 1;
        //for(int i = 0; i < 240; ++i)
        //{
            //color = SDL_MapRGB(g_surface->format, 640*480%rot * sin(i / rot), 640*480/rot * sin(i % rot), 640*480%rot * sin(i / rot));
            //pixel_data [i] = color;
            //color = SDL_MapRGB(g_surface->format, 255, 256 * sin(rot / 8.0f), 255);
            //pixels[i][i] = &color;
            //SetPixel(i, 2 * sin(i), g_surface, color);
            
            //pixel_data[i] = color;
        //}
        
        //color = SDL_MapRGB(g_surface->format, 255, 256 * sin(rot / 8.0f), 0);
        //g_graphics.SetDrawColor(255, 256*sin(rot/8.0f), 0);
       
        //SetPixel(rot,240 + sqrt(rot*rot + sin(rot)),g_surface,color);
        //SetPixel(rot, 240 + sin( rot - 2) + 1/4,g_surface,color);
        //SetPixel(rot, 240 + (5/3.5f * sqrt((rot * rot))), g_surface, color);
        //SDL_Flip(g_surface);240 + 120 * sin(rot)
        //if(rot % 2 == 0)
        //g_graphics.HLine(vec1.x, vec1.y, rot);
        //if(rot % 2 == 0)
        //g_graphics.VLine(14, 450, rot);
        //DrawLine(rot, 460, 0, rot, g_surface, color);
        //SDL_Flip(g_surface);
        g_graphics.UpdateScreen();
        
        //if(input.IsKeyPress(A))
        g_graphics.ClearScreen();
        printf("%d \n", rot);
        //SDL_FillRect(g_surface, NULL, 0x000000);
        SDL_Delay(10);
        ++rot;
        if(rot >= 470) {rot = 1;}
    }
    
    //SDL_Quit();
    
	return 0;
}


/*void SetPixel(int x, int y, SDL_Surface *surface, Uint32 color)
{
     Uint32 *buffp;
     buffp = (Uint32 *) surface->pixels;
     buffp[(y * surface->w) + x] = color;
}

void HLine(int x1, int x2, int y, SDL_Surface *surface, Uint32 color)
{
    //make sure y is within screen
    if(y >= 0 && y < surface->h)
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
           !(x1 > surface->w-1 && x2 > surface->w-1))
        {
            //clamp values horizontally
            if(x1 < 0) x1 = 0;
            if(x2 > surface->w-1) x2 = surface->w-1;
            
            //render line
            //this did not work
            //memset(surface->pixels + y * surface->w + x1, color, x2-x1+1);
            
            for(int i = x1; i < x2; ++i)
            {
                SetPixel(i, y, surface, color);
            }
        }
    }
}

void VLine(int y1, int y2, int x, SDL_Surface *surface, Uint32 color)
{
    //make sure line is inside screen 
    if(x >= 0 && x < surface->w)
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
           !(y1 > surface->h-1 && y2 > surface->h-1))
        {
            //clamp values veritcally
            if(y1 < 0) y1 = 0;
            if(y2 > surface->h-1) y2 =surface->h-1;
            
            //render
            for(int i = y1; i < y2; ++i)
            {
                SetPixel(x, i, surface, color);
            }
        }
    }
}

void DrawLine(int x, int y, int XX, int YY, SDL_Surface *surface, Uint32 color)
{
    int putX = x > XX ? XX : x;
    int putY = y > YY ? YY : y; 
    int endX = x < XX ? XX : x;
    int endY = y < YY ? YY : y; 
    
    for(int i = putX; i < endX; ++i)
    {
        for(int j = putY; j < endY; ++j)
        {
            //SetPixel(i, j, surface, color);
        }
    }
    
    while(putX < endX)
    {
        SetPixel(putX, putY, surface, color);
        putY ++; 
        putX ++;
        
        if(putY >= endY) {putY = endY;}
        if(putX >= endX) {putX = endX;}
    }
    
    /*double putX = XX - x;
    double putY = YY - y;
    double length = sqrt(putX*putY + putY*putY);
    double addX = putX/length; 
    double addY = putY/length;
    putX = x; 
    putX = y;
    
    for(int i = 0; i < length; ++i)
    {
        SetPixel(putX, putY, surface, color);
        putX += addX;
        putY += addY;
    }*/
//}
