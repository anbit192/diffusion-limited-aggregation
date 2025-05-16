#include <iostream>
#include <SDL.h>

using namespace std;

void pause() {
    cout << "Press any key to continue" << endl;
    getchar();
}

int main(int argc, char** args) {

    // Pointers to window and surface
    SDL_Surface* winSurface = NULL;
    SDL_Window* window = NULL;

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    SDL_Event e;

    // Init SDL (return -1 if fails)
    {
        int res = SDL_Init(SDL_INIT_EVERYTHING);
        if (res < 0) {
            cout << "Error" << SDL_GetError() << endl;
            pause();
            return 1;
        }
    }

    window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Error Creating Window" << SDL_GetError() << endl;
        pause();
        return 1;
    }

    winSurface = SDL_GetWindowSurface(window);
	if ( !winSurface ) {
		cout << "Error getting surface: " << SDL_GetError() << endl;
		pause();
		return 1;
	}

    SDL_Rect rect1 = {100, 100, 100, 100};

    while (true) {
        while (SDL_PollEvent(&e)){
            if (e.type==SDL_QUIT || e.type==SDL_KEYDOWN) {
                return 0;
            }
        }


        SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface -> format, 0, 0, 0));
        SDL_FillRect(winSurface, &rect1, SDL_MapRGB(winSurface -> format, 255, 255, 255));
        SDL_UpdateWindowSurface(window);
        if (rect1.x + 10 >= WINDOW_WIDTH){
            rect1.x = -100;
        }

        rect1.x += 10;

        SDL_Delay(100);
    }



    pause();

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}