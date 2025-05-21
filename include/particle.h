#pragma once
#include <string>

class Particle {
  protected:
    int x, y;
    int spdX, spdY;
    bool staticState;
    int size;
    int color[3];

  public:
    Particle();
    Particle(int x, int y, int spdX, int spdY);
    Particle(int x, int y, int spdX, int spdY, int size);

    void move();
    float calcDist(Particle &p);

    std::string toString() const;
    int getX();
    int getY();

    bool getStaticState();
    int getSize();
    int *getColor();

    void setX(int val);
    void setY(int val);
    void setStaticState(bool state);
    void setSpdX(int val);
    void setSpdY(int val);
    void setColor(int r, int g, int b);
};
