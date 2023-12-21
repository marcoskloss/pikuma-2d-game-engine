#include "Game/Game.hpp"
#include "Logger/Logger.hpp"

int main(int argc, char* argv[])
{
    Game game;

    Logger::Log("Hello world!");
    Logger::Err("Hello world!");
    Logger::Warn("Hello world!");

    // game.Initialize();
    // game.Run();
    // game.Destroy();

    return 0;
}
