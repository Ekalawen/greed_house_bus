
#include "includes.h"

void initInput(Input *in) 
{
}

void updateEvents (Input *in)
{
    SDL_Event event;
	in->button[SDL_BUTTON_WHEELUP] = 0;
	in->button[SDL_BUTTON_WHEELDOWN] = 0;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            in->key[event.key.keysym.sym]=1;
            break;
        case SDL_KEYUP:
            in->key[event.key.keysym.sym]=0;
            in->cooldownActive[event.key.keysym.sym]=0;
            in->cooldownTemps[event.key.keysym.sym]=0;
            break;
        case SDL_MOUSEMOTION:
            in->mouseX=event.motion.x;
            in->mouseY=event.motion.y;
            in->mouseRelX=event.motion.xrel;
            in->mouseRelY=event.motion.yrel;
            break;
        case SDL_MOUSEBUTTONDOWN:
            in->button[event.button.button]=1;
            break;
        case SDL_MOUSEBUTTONUP:
                        if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELDOWN)
               in->button[event.button.button]=0;
            break;
        case SDL_QUIT:
            in->quit = 1;
            break;
        default:
            break;
        }
    }
    repetitionDeTouche(in);
}

void repetitionDeTouche(Input *in)
{
    int i;
    for(i=0;i<SDLK_LAST;i++)
    {
        if(in->cooldownActive[i] == 1
           && in->cooldownTemps[i] != 0
           && in->cooldownTemps[i] <= SDL_GetTicks() - ATTENTE)
        {
            in->key[i] = 1;
            in->cooldownActive[i] = 2;
            in->cooldownTemps[i] = SDL_GetTicks();
        }
        if(in->cooldownActive[i] == 2
           && in->cooldownTemps[i] <= SDL_GetTicks() - REPETITION)
        {
            in->key[i] = 1;
            in->cooldownTemps[i] = SDL_GetTicks();
        }
        else if(in->cooldownActive[i] == 2
                && in->cooldownTemps[i] > SDL_GetTicks() - REPETITION)
        {
            in->key[i] = 0;
        }
    }
}

