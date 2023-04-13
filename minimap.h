
#ifndef ENTETE_H_INCLUDED
#define ENTETE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

typedef struct
{
    SDL_Surface *map;
    SDL_Surface *joueur;
    SDL_Rect posmap;
    SDL_Rect posjoueur;

} minimap;

typedef struct
{
    SDL_Surface *time;
    SDL_Rect position;
    TTF_Font *font;
    SDL_Color color;
    int sec;
    int min
} time;

// Declaration Des FonctionS
void initmap(minimap *m);
void afficherminimap(minimap m, SDL_Surface *screen);
void Liberer(minimap *m);
void affichertemps(int temps, SDL_Surface *screen);
int collisionmap(SDL_Surface *masque, SDL_Rect posPerso, int direction);

void refreshMinimap(minimap *m, SDL_Rect posPerso);
void freeMinimap(minimap *m);
void checkpixel(int x, int y, SDL_Surface *masque);

void inittime(time *m);
void afftime(time *m, SDL_Surface *screen);
#endif
