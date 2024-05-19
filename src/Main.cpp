#include "Game/Game.hpp"
#include "Logger/Logger.hpp"
#include "ECS/ECS.hpp"
#include <stdio.h>


int main(int argc, char* argv[])
{
    // Game game;

    // game.Initialize();
    // game.Run();
    // game.Destroy();

    System s;

    Entity e(1);
    Entity e2(777);
    Entity e3(6969);

    s.AddEntity(e);
    s.AddEntity(e2);
    s.AddEntity(e3);

    s.RemoveEntity(e2);
    auto entities = s.GetEntities();

    for (Entity it : entities) {
        int id = it.GetId();
        printf("ID: %d\n", id);
    }

    // s.RequireComponent<int>();
    // s.RequireComponent<char>();
    // s.RequireComponent<float>();
    // s.RequireComponent<bool>();

    // s.RequireComponent<int>();
    // s.RequireComponent<char>();
    // s.RequireComponent<float>();
    // s.RequireComponent<bool>();

    return 0;
}
