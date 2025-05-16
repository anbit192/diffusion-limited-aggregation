#include "particle.h"
#include <math.h>
#include <sstream>

Particle::Particle(): x(0), y(0), staticState(false), size(2) {}


Particle::Particle(int x, int y, int spdX, int spdY) : x(x), y(y), spdX(spdX), spdY(spdY), staticState(false), size(10) {
    color[0] = 247;
    color[1] = 192;
    color[2] = 192;

}


void Particle::moveToTarget(const Particle &p) {
    int offsetMin = -30;
    int offsetMax = 30;

    int offsetVal = rand() % (offsetMax - offsetMin + 1) + offsetMin;

    if (this->staticState == false) {
        if (this->x > 1280 || this->x < 0) {
            this->spdX = -this->spdX;
            this->x += (spdX + 0.5 * offsetVal);     
        }
        if (this->y > 1280 || this->y < 0 ) {
            this->spdY = -this->spdY;
            this->y += (spdY + 0.5 * offsetVal);     
        }
        this->x += spdX;
        this->y += spdY;
    }
}


float Particle::calcDist(Particle &p) {
    float distX = (this->x - p.x)*(this->x - p.x);
    float distY = (this->y - p.y)*(this->y - p.y);

    return distX + distY;
}

std::string Particle::toString() const {
    std::ostringstream ss;
    ss << "Particle(x=" << x << ", y=" << y
       << ", static=" << (staticState ? "true" : "false")
       << ", size=" << size
       << ", color=(" << color[0] << "," << color[1] << "," << color[2] << "))";
    return ss.str();
}

// Getters
int Particle::getX() { return x; }
int Particle::getY() { return y; }
bool Particle::getStaticState() { return staticState; }
int Particle::getSize() { return size; }
int* Particle::getColor() { return color; }

// Setters
void Particle::setX(int val) { x = val; }
void Particle::setY(int val) { y = val; }
void Particle::setStaticState(bool state) {staticState = state;}
void Particle::setSpdX(int val) {spdX = val;}
void Particle::setSpdY(int val) {spdY = val;}
void Particle::setColor(int r, int g, int b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}
