#ifndef MAP_H
#define MAP_H

#include <stdio.h>

typedef struct Point Point;

struct Point{
    int x;
    int y;
    char c;
};

int getnum(FILE* file);

char** makemap(int x,int y);


void tele(char** map,int i, int j);

void blocker(char** map,int i, int j,int n);

void pointer(char** map,int i, int j, int n);

void Fer(char** map,int i, int j);

void remap(char** map,int x,int y);

Point nearest_char(char** map, Point p, char c, int max_i, int max_j);

int dist(Point p1, Point p2);
int abs(int x);

#endif // MAP_H
