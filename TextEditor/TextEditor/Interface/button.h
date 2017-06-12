#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "texture.h"

class button {
    private:
    
    public:
        int m_X, m_Y, m_W, m_H;
        std::string m_text;

        button(int x, int y, int w, int h, std::string text);
        ~button();

        texture m_texture;
        bool inButton(int x, int y);

        void render();
        /*private:
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
        }*/
};