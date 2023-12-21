set -xe

FLAGS="-Wall -Wfatal-errors -std=c++17"
LIBS="-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3"
INCLUDE="-I./libs/"
OBJ="gameengine"
SOURCE_FILES="src/Main.cpp src/Game/Game.cpp src/Logger/Logger.cpp"

g++ -o $OBJ $SOURCE_FILES $FLAGS $LIBS $INCLUDE
