#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

/*enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};*/

class texture
{
    public:
        SDL_Window *window;
        SDL_Surface *windowSurface;
        SDL_Surface *windowImage;
        SDL_Renderer *renderer;
        TTF_Font *font = NULL;
        texture();

        ~texture();

        bool loadFromFile(std::string path);

    #ifdef _SDL_TTF_H
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
    #endif

        void free();

        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        void setBlendMode(SDL_BlendMode blending);

        void setAlpha(Uint8 alpha);

        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* mTexture;

        int m_W;
        int m_H;
};