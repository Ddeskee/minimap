#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

int main()
{

    SDL_Surface *screen = SDL_SetVideoMode(1920, 358, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_Event event;

    SDL_Surface *bg = IMG_Load("level1 final.png");

    SDL_Surface *masque = IMG_Load("masque1920.png");

    SDL_Surface *perso = IMG_Load("perso.png");

    SDL_Rect posPerso;

    posPerso.x = 0;
    posPerso.y = 300;

    //! boucle de jeu
    int gamerunning = 1;
    int direction = -1;

    int counter = 0;

    Uint32 start;
    const int FPS = 15;

    //! Declaration des entetes

    minimap m;
    initmap(&m);

    time t;
    inittime(&t);
    //! Boucle de jeu
    while (gamerunning)
    {

        start = SDL_GetTicks();

        SDL_BlitSurface(masque, NULL, screen, NULL);
        SDL_BlitSurface(bg, NULL, screen, NULL);
        SDL_BlitSurface(perso, NULL, screen, &posPerso);

        afficherminimap(m, screen);

        // affichertemps(temp, screen);
        afftime(&t, screen);
        refreshMinimap(&m, posPerso);

        if (collisionmap(masque, posPerso, direction) == 0)
        {
            if (direction == 1)
                posPerso.x += 10;
            if (direction == 0)
                posPerso.x -= 10;
            if (direction == 2)
                posPerso.y -= 10;
            if (direction == 3)
                posPerso.y += 10;
        }

        //! prendre l'input
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gamerunning = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_e:
                    gamerunning = 0;
                    break;
                case SDLK_RIGHT:
                    direction = 1;
                    break;
                case SDLK_LEFT:
                    direction = 0;
                    break;
                case SDLK_UP:
                    direction = 2;
                    break;
                case SDLK_DOWN:
                    direction = 3;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_e:
                    gamerunning = 0;
                    break;
                case SDLK_RIGHT:
                    direction = -1;
                    break;
                case SDLK_LEFT:
                    direction = -1;
                    break;
                case SDLK_UP:
                    direction = -1;
                    break;
                case SDLK_DOWN:
                    direction = -1;
                    break;
                }
                break;
            }
        }

        //! collision avec Ennemi
        // if collision
        //! Game Over

        SDL_Flip(screen);

        counter++;

        if (counter == FPS)
        {
            counter = 0;
            t.sec++;
        }

        if (1000 / FPS > SDL_GetTicks() - start)
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
    }
    freeMinimap(&m);
    return 0;
}
