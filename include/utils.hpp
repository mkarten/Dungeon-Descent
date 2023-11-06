#pragma once


#include <SDL2/SDL.h>


namespace utils
{
    inline float hireTimeInSeconds() // Retourne le temps depuis le lancement du programme en secondes
    {
        float t = SDL_GetTicks(); // Récupère le temps depuis le lancement du programme en millisecondes
        t *= 0.001f; // Convertit le temps en secondes
        return t;
    }
}
