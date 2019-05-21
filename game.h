#ifndef GAME_H
#define GAME_H
#include "map.h"

void getkey(char* STATE1,char* STATE2);
typedef struct Game Game;

struct Game{
    struct Point player1;
    struct Point player2;
    struct Point tele1;
    struct Point tele2;
    struct Point* wall;
    struct Point* block;
    struct Point* point;
    int n_wall;
    int n_block;
    int n_point;
    struct Point F;
};

Point* get_all_objs(Game *game);
#endif
