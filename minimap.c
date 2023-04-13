#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

void inittime(time *m)
{

    m->position.x = 0;
    m->position.y = 100;
    TTF_Init();
    m->font = TTF_OpenFont("font.ttf", 40);

    m->color.r = 0;
    m->color.g = 0;
    m->color.b = 0;

    int sec = 0;
    int min = 0;
}

void afftime(time *m, SDL_Surface *screen)
{
    if (m->sec >= 60)
    {
        m->sec -= 60;
        m->min++;
    }

    char holder[20];

    sprintf(holder, "Time: %d|%d", m->min, m->sec);

    m->time = TTF_RenderText_Blended(m->font, holder, m->color);

    SDL_BlitSurface(m->time, NULL, screen, &m->position);
}

void initmap(minimap *m)
{
    m->map = IMG_Load("level1 minifinal.png");
    m->joueur = IMG_Load("point.png");
    m->posmap.x = 0;
    m->posmap.y = 0;
    m->posjoueur.x = 400;
    m->posjoueur.y = 50;
}

void refreshMinimap(minimap *m, SDL_Rect posPerso)
{
    m->posjoueur.x = posPerso.x * 0.2 + m->posmap.x;
    m->posjoueur.y = posPerso.y * 0.2;
}

void afficherminimap(minimap m, SDL_Surface *screen)
{
    SDL_BlitSurface(m.map, NULL, screen, &(m.posmap));
    SDL_BlitSurface(m.joueur, NULL, screen, &(m.posjoueur));
}

void freeMinimap(minimap *m)
{
    SDL_FreeSurface(m->map);
    SDL_FreeSurface(m->joueur);
}

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y)
{
    SDL_Color color;
    Uint32 col = 0;
    if (x >= 0 && y >= 0)
    {
        // determine position
        char *pPosition = (char *)pSurface->pixels;

        // offset by y
        pPosition += (pSurface->pitch * y);

        // offset by x
        pPosition += (pSurface->format->BytesPerPixel * x);

        // copy pixel data
        memcpy(&col, pPosition, pSurface->format->BytesPerPixel);

        // convert color
    }
    SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
    return (color);
}

void checkpixel(int x, int y, SDL_Surface *masque)
{
    SDL_Color col;
    col = GetPixel(masque, x, y);
    printf("r;%d|g:%d|b:%d\n", col.r, col.g, col.b);
}

int collisionmap(SDL_Surface *masque, SDL_Rect posPerso, int direction)
{
    SDL_Color col, col2, col3;

    if (direction == 1) // imin
    {
        col = GetPixel(masque, posPerso.x + 47, posPerso.y + 47);
        col2 = GetPixel(masque, posPerso.x + 47, posPerso.y + 23);
        col3 = GetPixel(masque, posPerso.x + 47, posPerso.y);
    }

    else if (direction == 0) // issarr
    {
        col = GetPixel(masque, posPerso.x, posPerso.y + 47);
        col2 = GetPixel(masque, posPerso.x, posPerso.y + 23);
        col3 = GetPixel(masque, posPerso.x, posPerso.y);
    }
    else if (direction == 2) // lfou9
    {
        col = GetPixel(masque, posPerso.x + 47, posPerso.y);
        col2 = GetPixel(masque, posPerso.x + 23, posPerso.y);
        col3 = GetPixel(masque, posPerso.x, posPerso.y);
    }
    else if (direction == 3) // louta
    {
        col = GetPixel(masque, posPerso.x + 47, posPerso.y + 47);
        col2 = GetPixel(masque, posPerso.x + 23, posPerso.y + 47);
        col3 = GetPixel(masque, posPerso.x, posPerso.y + 47);
    }

    if (col.r == 255 && col.g == 40 && col.b == 242)
        return 1;

    else if (col2.r == 255 && col2.g == 40 && col2.b == 242)
        return 1;

    else if (col3.r == 255 && col3.g == 40 && col3.b == 242)
        return 1;

    else
        return 0;
}
