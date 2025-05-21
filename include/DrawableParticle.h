#pragma once

#include "particle.h"
#include <SDL.h>

class DrawableParticle : public Particle {
  public:
    SDL_Rect rect;

  public:
    DrawableParticle();
    DrawableParticle(int x, int y, int spdX, int spdY);
    DrawableParticle(int x, int y, int spdX, int spdY, int size);

    void move();
};
