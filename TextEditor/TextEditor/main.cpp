#include "main.h"
#include "../Dependencies/SDL2-2.0.5/include/SDL.h"

/*#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t int32;
typedef int64_t int64;

int main(int argc, char *argv[]) {
	glfwInit();
	glfwSetErrorCallback(error_callback);

	GLFWwindow* window = glfwCreateWindow(640, 480, "TextEditor", NULL, NULL);
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		
	}

	glfwDestroyWindow(window);
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}*/

int main(int argc, char *argv[]) { //SDL renames main to SDL_main, so it's not actually the main function
    /*std::string input;
    std::cin >> input;
    std::cout << std::endl;
    std::cin >> input;*/
    
    SDL_Window *window = NULL;
    SDL_Surface *windowSurface = nullptr;

    window = SDL_CreateWindow("CAS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    bool isRunning = true;
    SDL_Event ev;

    while (isRunning) {
        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        SDL_UpdateWindowSurface(window);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}