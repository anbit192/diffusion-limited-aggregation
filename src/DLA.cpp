#include <iostream>
#include <SDL.h>
#include <array>
#include <stdlib.h> 
#include <vector>

//#include "SDL_pixels.h"
//#include "SDL_timer.h"
#include "SDL_render.h"
#include "particle.h"

using namespace std;

// define variables
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 1280;

const int N_PARTICLES = 500;

SDL_Renderer* renderer;
SDL_Window* window;

struct DrawableParticle {
    Particle p;
    SDL_Rect rect;

    DrawableParticle() {};

    DrawableParticle(int x, int y, int spdX, int spdY) {
        this->p = Particle(x, y, spdX, spdY );
        this->rect = {p.getX(), p.getY(), p.getSize(), p.getSize()};
    };
    
    void move() {
        this->p.move();
        this->rect.x = this->p.getX();
        this->rect.y = this->p.getY();
    }
};

Particle CENTER_PARTICLE(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0, 0);
DrawableParticle centerDp = DrawableParticle(CENTER_PARTICLE.getX(), CENTER_PARTICLE.getY(), 0, 0);

// Init SDL things
void pause() {
    cout << "Press any key to continue" << endl;
    getchar();
}


bool initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << "Failed to initialize SDL :" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool createWindow() {
    window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == nullptr) {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }  
    return true;
}

bool createRenderer() {
    renderer = SDL_CreateRenderer(window,-1 ,0 );
    if (renderer == nullptr) {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }
    return true;
}

void setupRenderer() {
    SDL_RenderSetLogicalSize(renderer,WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

bool initEverything() {
    if (!initSDL() || !createWindow() || !createRenderer()) {

        pause();
        return false;
    }
    setupRenderer();

    return true;
}

// helper functions
void testParticles() {
    Particle p1(1280/2, 720/2,0,0);
    Particle p2(3, 3,0,0);

    cout << p1.toString() << endl;
    cout << "Moving to target" << endl;
    p1.move();
    cout << p1.toString() << endl;

    float dist_ = p1.calcDist(p2);
    cout << dist_ << endl; 
}



void setRandomColor(DrawableParticle &dp) {
    int* currentColor = dp.p.getColor(); 
    int offsetMin = -25;
    int offsetMax = 25;

    int offsetValR = rand() % (offsetMax - offsetMin + 1) + offsetMin;
    int offsetValG = rand() % (offsetMax - offsetMin + 1) + offsetMin;
    int offsetValB = rand() % (offsetMax - offsetMin + 1) + offsetMin;

    int offsetColor[3] = {currentColor[0] + offsetValR, currentColor[1] + offsetValG, currentColor[2] + offsetValB};

    for (int i = 0; i < 3; i++) {
        if (offsetColor[i] > 255) {
            offsetColor[i] = 255;
        } else if (offsetColor[i] < 0) {
            offsetColor[i] = 0;
        }
    } 

    dp.p.setColor(offsetColor[0], offsetColor[1], offsetColor[2]);
}

void generateCircleWalkers(array<DrawableParticle, N_PARTICLES> &drawableParticles, float bigRadius = 639, int steps=100) {

    for (int i = 0; i < drawableParticles.size(); i++) {
        int offsetMin = -10;
        int offsetMax = 10;

        int offsetVal = rand() % (offsetMax - offsetMin + 1) + offsetMin;

        float angle = static_cast<float>(rand()) / RAND_MAX * 2* M_PI;

        float x = bigRadius + bigRadius * cos(angle) + offsetVal;
        float y = bigRadius + bigRadius * sin(angle) + offsetVal;
        
        int spdX = (CENTER_PARTICLE.getX() - x) / steps + 2*offsetVal;  
        int spdY = (CENTER_PARTICLE.getY() - y) / steps + 1.5*offsetVal;  


        drawableParticles[i] = DrawableParticle(x, y, spdX, spdY);
        //cout << drawableParticles[i].p.toString() << endl;
    }
}


void generateRandomWalkers(array<DrawableParticle, N_PARTICLES> &drawableParticles,int spd=30, int limitX1=0, int limitX2=WINDOW_WIDTH, int limitY1=0, int limitY2=WINDOW_HEIGHT) {
    if (limitX1 > limitX2 || limitY1 > limitY2) {
        cout << "Invalid range" << endl;
        return;
    }
    for (int i = 0; i < drawableParticles.size(); i++) {
        int randomX = rand() % (limitX2 - limitX1 + 1) + limitX1;
        int randomY = rand() % (limitY2 - limitY1 + 1) + limitY1;

        int randomSpd = rand() % (2*spd + 1) - spd;
        if (abs(randomSpd - 0) <= 10) {
            randomSpd = 15;
        }

        drawableParticles[i] = DrawableParticle(randomX, randomY, randomSpd, randomSpd);
    }
}


bool checkConditions(vector<DrawableParticle*> &aggregated, DrawableParticle &dp) {
    for (DrawableParticle* ap:aggregated) {
        if (ap) {
            if (ap->p.calcDist(dp.p) <= (1.2 * dp.p.getSize()*dp.p.getSize()) && dp.p.getStaticState() == false) {
                //cout << "merged!" << endl;
                return true;

            }
        } 
         
    }
    return false;
}

// render frame
void render(array<DrawableParticle, N_PARTICLES> &walkers, vector<DrawableParticle*> &aggregates) {
    SDL_RenderClear(renderer);
    if (aggregates.size() > 0) {
        for (DrawableParticle* dp : aggregates) {
            if (dp) {

                int* color = dp->p.getColor();
                cout << dp->p.toString() << endl;
                SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
                SDL_RenderFillRect(renderer, &dp->rect);
                //cout << dp->p.toString() << endl;
            } 
        }
    }
    

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (DrawableParticle &dp : walkers) {
        if (!dp.p.getStaticState()) {
            SDL_RenderFillRect(renderer, &dp.rect);

            dp.move();

            if (checkConditions(aggregates, dp)) {
                dp.p.setStaticState(true);
                aggregates.push_back(&dp);
                setRandomColor(dp);

            }
        }
    }
    
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}

// main function
int main(int argc, char** args) {

    SDL_Event e;
    bool running = true;

    array<DrawableParticle, N_PARTICLES> drawableParticles;
    vector<DrawableParticle*> aggregatedParticles{&centerDp}; 

    initEverything();
    //generateRandomWalkers(drawableParticles);
    // cout << drawableParticles[0].p.toString() << endl;
    generateCircleWalkers(drawableParticles);
    while (running == true) {
        while (SDL_PollEvent(&e)) {
            if (e.type==SDL_QUIT || e.type==SDL_KEYDOWN) {
                running = false;
            }
        }
        
        render(drawableParticles, aggregatedParticles);
        
        SDL_Delay(16);

    }

    return 0;
}
