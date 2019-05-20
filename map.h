#ifndef MAP_H
#define MAP_H

int getnum();

char** makemap(int x,int y);


void tele(char** map,int i, int j);

void blocker(char** map,int i, int j,int n);

void pointer(char** map,int i, int j, int n);

void Fer(char** map,int i, int j);

void remap(char** map,int x,int y);


struct Point{
    int x;
    int y;
    char c;
};
#endif // MAP_H
