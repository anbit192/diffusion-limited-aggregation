#pragma once
#include <SDL.h>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "DrawableParticle.h"
#include "config.h"

using namespace std;
class Simulation {
  protected:
    SDL_Renderer *renderer;
    SDL_Window *window;
    array<DrawableParticle, config::N_PARTICLES> walkers;
    vector<DrawableParticle *> aggregates;

  public:
    Simulation();

    bool initSDL();
    bool createWindow();
    bool createRenderer();
    void setupRenderer();
    bool initEverything();

    array<DrawableParticle, config::N_PARTICLES> &getWalkers();
    array<DrawableParticle *, config::N_PARTICLES> &getAggregates();

    void setWalkers(array<DrawableParticle, config::N_PARTICLES> &walkers);
    void setAggregates(array<DrawableParticle *, config::N_PARTICLES> &aggregates);

    int *offsetParticleColor(DrawableParticle &dp, int min = -15, int max = 15);
    void clearParticles();
    bool checkAggregate(DrawableParticle &dp);

    void generateCirclePreset(DrawableParticle &center, int circleRadius = config::WINDOW_WIDTH / 2, int steps = 100);
    void generateRandomPreset(int numAggregator = 4, int limitX1 = 10, int limitX2 = config::WINDOW_WIDTH, int limitY1 = 10, int limitY2 = config::WINDOW_HEIGHT, int spdMin = 10, int spdMax = 50);

    void render();
};
