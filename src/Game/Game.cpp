#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

#include "Game.hpp"
#include "../Logger/Logger.hpp"
#include "../ECS/ECS.hpp"

Game::Game()
{
    isRunning = false;
}

Game::~Game()
{
}

void Game::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::Err("Error initializing SDL.");
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 800; //displayMode.w;
    windowHeight = 600; //displayMode.h;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        0 //SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        Logger::Err("Error creating SDL window.\n");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        Logger::Err("Error creating SDL renderer.\n");
        return;
    }

    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
}

void Game::Setup()
{
}

void Game::Update()
{
    int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // The difference in ticks since last frame, converted in seconds
    double dt = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

    millisecsPreviousFrame = SDL_GetTicks();
}

void Game::Run()
{
    Setup();
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        }
    }
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// TODO list
// - replace SDL by raylib
