#pragma once

#include <SDL.h>
#include "particle.h"
   
class DrawableParticle : public Particle {
    public: SDL_Rect rect;

    public: DrawableParticle();
    public: DrawableParticle(int x, int y, int spdX, int spdY);
    public: DrawableParticle(int x, int y, int spdX, int spdY, int size);

    public: void move();
};
