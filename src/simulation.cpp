#include "Simulation.h"
#include "DrawableParticle.h"
#include "SDL_events.h"
#include "config.h"
#include <time.h>

Simulation::Simulation() {
    aggregates.reserve(config::N_PARTICLES + config::N_PARTICLES / 2);
    initEverything();
}
bool Simulation::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << "Failed to initialize SDL :" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Simulation::createWindow() {
    window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config::WINDOW_WIDTH, config::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }
    return true;
}

bool Simulation::createRenderer() {
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }
    return true;
}

void Simulation::setupRenderer() {
    SDL_RenderSetLogicalSize(renderer, config::WINDOW_WIDTH, config::WINDOW_HEIGHT);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

bool Simulation::initEverything() {
    if (!initSDL() || !createWindow() || !createRenderer()) {

        return false;
    }
    setupRenderer();

    return true;
}

void Simulation::clearParticles() {
    this->walkers = array<DrawableParticle, config::N_PARTICLES>();
    this->aggregates = vector<DrawableParticle *>();
}

int *Simulation::offsetParticleColor(DrawableParticle &dp, int min, int max) {
    int *currentColor = dp.getColor();

    int offsetValR = rand() % (max - min + 1) + min;
    int offsetValG = rand() % (max - min + 1) + min;
    int offsetValB = rand() % (max - min + 1) + min;

    int offsetColor[3] = {currentColor[0] + offsetValR, currentColor[1] + offsetValG, currentColor[2] + offsetValB};

    for (int i = 0; i < 3; i++) {
        if (offsetColor[i] > 255) {
            offsetColor[i] = 255;
        } else if (offsetColor[i] < 0) {
            offsetColor[i] = 0;
        }
    }

    dp.setColor(offsetColor[0], offsetColor[1], offsetColor[2]);
    return dp.getColor();
}

void Simulation::generateCirclePreset(DrawableParticle &center, int radius, int steps) {
    clearParticles();
    aggregates.push_back(&center);

    for (int i = 0; i < this->walkers.size(); i++) {
        int offsetMin = -10;
        int offsetMax = 10;

        int offsetVal = rand() % (offsetMax - offsetMin + 1) + offsetMin;

        float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;

        float x = radius + radius * cos(angle) + offsetVal;
        float y = radius + radius * sin(angle) + offsetVal;

        int spdX = (aggregates[0]->getX() - x) / steps + 2 * offsetVal;
        int spdY = (aggregates[0]->getY() - y) / steps + 1.5 * offsetVal;

        this->walkers[i] = DrawableParticle(x, y, spdX, spdY, center.getSize() - 2);
        // cout << drawableParticles[i].p.toString() << endl;
    }
}

int random(int min, int max) {
    // srand(192 );
    return rand() % (max - min + 1) + min;
}

void Simulation::generateRandomPreset(int numAggregator, int limitX1, int limitX2, int limitY1, int limitY2, int spdMin, int spdMax) {
    clearParticles();
    for (int i = 0; i < numAggregator; i++) {
        this->aggregates.push_back(new DrawableParticle(random(limitX1, limitX2), random(limitY1, limitY2), 0, 0));
        this->aggregates[i]->setColor(random(0, 255), random(0, 255), random(0, 255));
    }

    for (int i = 0; i < this->walkers.size(); i++) {
        int randomX = rand() % (limitX2 - limitX1 + 1) + limitX1;
        int randomY = rand() % (limitY2 - limitY1 + 1) + limitY1;

        int randomSpd = random(spdMin, spdMax);

        this->walkers[i] = DrawableParticle(randomX, randomY, randomSpd, randomSpd);
    }
}

bool Simulation::checkAggregate(DrawableParticle &dp) {
    for (DrawableParticle *ap : this->aggregates) {
        if (ap) {
            if (ap->calcDist(dp) <= (1.2 * dp.getSize() * dp.getSize()) && dp.getStaticState() == false) {
                // cout << "merged!" << endl;
                int *curr_color = ap->getColor();
                dp.setColor(curr_color[0], curr_color[1], curr_color[2]);
                return true;
            }
        }
    }
    return false;
}

void Simulation::render() {
    SDL_Event e;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN) {
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        if (this->aggregates.size() > 0) {
            for (DrawableParticle *dp : aggregates) {
                if (dp) {
                    int *color = dp->getColor();
                    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
                    SDL_RenderFillRect(renderer, &dp->rect);
                    // cout << dp->toString() << endl;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (DrawableParticle &dp : walkers) {
            if (!dp.getStaticState()) {
                SDL_RenderFillRect(renderer, &dp.rect);

                dp.move();
                if (checkAggregate(dp)) {
                    dp.setStaticState(true);
                    offsetParticleColor(dp);
                    aggregates.push_back(&dp);

                    cout << "AGGREGATED!!!" << endl;
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_Delay(config::DELAY);
    }
}
