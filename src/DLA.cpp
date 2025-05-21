#include "DrawableParticle.h"
#include "Simulation.h"
#include "config.h"
#include <SDL.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

// main function
int main(int argc, char **args) {
    std::srand(static_cast<unsigned int>(time(nullptr)));
    cout << "RUN" << endl;
    Simulation sim = Simulation();
    DrawableParticle center = DrawableParticle(config::WINDOW_WIDTH / 2, config::WINDOW_HEIGHT / 2, 0, 0);
    // sim.generateCirclePreset(center);
    sim.generateRandomPreset(10);
    sim.render();

    return 0;
}
