#pragma once
#include <string>

class Particle {
    protected:
        int x, y;
        int spdX, spdY;
        bool staticState;
        int size;
        int color[3];

    public: Particle();
    public: Particle(int x, int y, int spdX, int spdY);
    public: Particle(int x, int y, int spdX, int spdY, int size);

    public: void move();
    public: float calcDist(Particle &p);
    public: std::string toString() const;


    public: int getX();
    public: int getY();
    public: bool getStaticState();
    public: int getSize();
    public: int* getColor();

    public: void setX(int val);
    public: void setY(int val);
    public: void setStaticState(bool state);
    public: void setSpdX(int val);
    public: void setSpdY(int val);
    
    public: void setColor(int r, int g, int b);

};
