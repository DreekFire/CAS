#include "main.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *window = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Surface *windowImage = NULL;
SDL_Renderer *renderer = NULL;
SDL_Rect screenRect;
Uint32 clearColor;
std::vector<node> functionList;

/*bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        window = SDL_CreateWindow("CAS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Could not create window! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            windowSurface = SDL_GetWindowSurface(window);
            screenRect.x = screenRect.y = 0;
            screenRect.w = windowSurface->w;
            screenRect.h = windowSurface->h;
            clearColor = SDL_MapRGB(windowSurface->format, 255, 255, 255);
        }
    }

    return success;
}

bool load() {
    bool success = true;
    windowImage = SDL_LoadBMP("res/tomato.bmp");
    if (windowImage == NULL)
    {
        std::cout << ("Unable to load image %s! SDL Error: %s", "tomato.bmp", SDL_GetError()) << std::endl;
        success = false;
    }

    return success;
}

void stop() {
    SDL_FreeSurface(windowImage);
    windowImage = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

#ifdef _SDL_TTF_H
    if (!TTF_WasInit()) {
        TTF_Quit();
    }
#endif

    SDL_Quit();
}

void run() {
    bool isRunning = true;

    SDL_Event ev;

    while (isRunning) {
        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        SDL_FillRect(windowSurface, &screenRect, clearColor);
        SDL_BlitSurface(windowImage, NULL, windowSurface, NULL);
        SDL_UpdateWindowSurface(window);
    }
}*/

int main(int argc, char *argv[]) { //SDL renames main to SDL_main, so it's not actually the main function
    /*if (!init()) {
        std::cout << "Failed to initialize!" << std::endl;
    }
    else {
        if (!load()) {
            std::cout << "Failed to load media!" << std::endl;
        }
        else {
            run();
        }
    }

    stop();
    */
    int x;
    node tree(shuntingYardAlg(tokenize("2*x+1")));
    std::cout << tree.toString() << std::endl;
    std::cout << derivative::deriv(tree)->toString() << std::endl;
    std::cin >> x;
    return 0;
}