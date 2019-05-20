#ifndef GAME_H
#define GAME_H
#include "map.h"
void getkey(char* STATE1,char* STATE2);

struct Game{
    struct Point player1;
    struct Point player2;
    struct Point tele1;
    struct Point tele2;
    struct Point* wall;
    struct Point* block;
    struct Point* point;
    struct Point F;
};
#endif
