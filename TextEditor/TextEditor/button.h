#pragma once
#include "../Dependencies/SDL2-2.0.5/include/SDL.h"

class button {
    private:
        SDL_Rect box;

        SDL_Rect* clip;

    public:
        button(int x, int y, int w, int h);

        void handle_events();

        void show();

        void setClips() {
            clips[1].x = 0;
            clips[1].y = 0;
            clips[1].w = 303;
            clips[1].h = 53;

            clips[0].x = 304;
            clips[0].y = 0;
            clips[0].w = 303;
            clips[0].h = 53;
        }
};