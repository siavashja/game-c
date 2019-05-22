#ifndef GAME_H
#define GAME_H

#include "map.h"
#include <stdio.h>

#define LEADERBOARD_FILE "leaderboard.txt"

void getkey(char *STATE1, char *STATE2);

typedef struct Game Game;
typedef struct Player Player;

struct Player {
    Point pos;
    int score;
    char name[20];
    char draw;
};

struct Game {
    Player player1;
    Player player2;
};

Point *get_objs(char** map, char c, Point max);

void init(FILE *file, int *x, int *y, float *time);

void submit_game(Game* game);

int len(char *c);

void move(char **map,Point max, char *STATE1, char *STATE2, Player *player1, Player *player2);

void teleport(char **map, Player *player, Point *teleports, Point max);

void move_player(char **map, Player *player, Point r, Point max);

void reobj(char **map, Point p, Point max);

int getnum2(char* str, int* i);

void getname(char* str, int* i, char* n);

int find_game(Game* games, Game *game, int size);

#endif
