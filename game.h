#ifndef GAME_H
#define GAME_H
#include "map.h"

void getkey(char* STATE1,char* STATE2);
typedef struct Game Game;
typedef struct Player Player;

struct Player{
    Point pos;
    int score;
};

struct Game{
    Player player1;
    Player player2;
};

Point* get_all_objs(Game *game);
#endif
