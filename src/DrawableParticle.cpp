#include "DrawableParticle.h"
#include "particle.h"

DrawableParticle::DrawableParticle() : Particle() {}
DrawableParticle::DrawableParticle(int x, int y, int spdX, int spdY) : Particle(x, y, spdX, spdY)
{
        this->rect = {x, y, size, size};
}

DrawableParticle::DrawableParticle(int x, int y, int spdX, int spdY, int size) : Particle(x, y, spdX, spdY, size), rect{x, y, size, size} {}

void DrawableParticle::move() {
    if (!this->staticState) {
        Particle::move();
        this->rect.x = x;
        this->rect.y = y;

    }
}


