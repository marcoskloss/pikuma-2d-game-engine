set -xe

FLAGS="-Wall -std=c++17"
LIBS="-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3"
INCLUDE="-I./libs/"
OBJ="gameengine"

g++ -o $OBJ src/Main.cpp $FLAGS $LIBS $INCLUDE
