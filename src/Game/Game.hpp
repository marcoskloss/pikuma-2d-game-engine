#pragma once

#include <SDL2/SDL.h>

constexpr int FPS = 60;
constexpr int MS_PER_FRAME = 1000 / FPS;

class Game {
    private:
        bool isRunning;
        int millisecsPreviousFrame = 0;
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Game();
        ~Game();
        void Initialize();
        void Run();
        void Setup();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

        int windowHeight;
        int windowWidth;
};

