#ifndef MAP_H
#define MAP_H

#include <stdio.h>

struct Game;
struct Player;
struct Point {
    int x;
    int y;
    char c;
};
typedef struct Point Point;

int is_equal(Point *f, Point *s);

int getnum(FILE *file);

char **makemap(int x, int y, int points);

void tele(char **map, int i, int j);

void blocker(char **map, int i, int j, int n);

void pointer(char **map, int i, int j, int n);

void Fer(char **map, int i, int j);

void remap(char** map, struct Game* game, int x, int y);

Point nearest_char(char **map, Point p, char c, int max_i, int max_j);

int dist(Point p1, Point p2);

int abs(int x);

int find_around(char **map, Point p, char c, Point max);

#endif // MAP_H
