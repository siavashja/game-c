#ifndef GAME_H
#define GAME_H

#include "map.h"
#include <stdio.h>

#define LEADERBOARD_FILE "leaderboard.txt"

void getkey(char* STATE1,char* STATE2);
typedef struct Game Game;
typedef struct Player Player;

struct Player{
    Point pos;
    int score;
    char c;
    char name[20];
};

struct Game{
    Player player1;
    Player player2;
};

Point* get_all_objs(Game *game);

void init(FILE* file, int* x, int* y, float* time);
void submit_game(Player* player1, Player* player2);
int len(char* c);
#endif
