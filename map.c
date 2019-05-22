#include "map.h"
#include <stdio.h>
#include <stdlib.h>

int getnum(FILE* file){
    char c;
    int res = 0;
    while((c = fgetc(file)) >= '0' && c <= '9')
        res = 10*res + c - '0';
    return res;
}

char** makemap(int x,int y){

    char** map = (char**)malloc(sizeof(char*)*(x+1));
    for(int i=0;i<x+1;i++){
        map[i] = (char*)malloc(sizeof(char)*(y+1));
        for(int j=0;j<y+1;j++){
            if(i==0 || i==x || j==0 || j==y){
                map[i][j]='!';
            }
            else
                map[i][j]=' ';
        }
    }
    remap(map,x,y);
    return map;
}

void tele(char** map,int i, int j){
    int x;
    int y;
    int m=2;
    while(m>0){
        x=rand()%i;
        y=rand()%j;
        if(map[x][y]==' '){
            map[x][y]='T';
            m--;
        }
    }
}

void blocker(char** map,int i, int j,int n){
    int x;
    int y;
    while(n>0){
        x=rand()%i;
        y=rand()%j;
        if(map[x][y]==' '){
            map[x][y]='B';
            n--;
        }
    }
}

void pointer(char** map,int i, int j, int n){
    int x;
    int y;
    while(n>0){
        x=rand()%i;
        y=rand()%j;
        if(map[x][y]==' '){
            map[x][y]='.';
            n--;
        }
    }
}

void Fer(char** map,int i, int j){
    int x;
    int y;
    x=rand()%i;
    y=rand()%j;
    if(map[x][y]==' '){
        map[x][y]='F';
        return;
    }
    else
        Fer(map,i,j);
}

void remap(char** map,int x,int y){
    for(int i=0;i<x+1;i++){
        for(int j=0;j<y+1;j++){
            printf(" %c ",map[i][j]);
        }
        printf("\n");
    }
}

Point nearest_char(char **map, Point p, char c, int max_i, int max_j) {
    Point nearest = {-1, -1};
    int min_dist = 1000;
    for(int i = 0; i < max_i; i++){
        for(int j = 0; j < max_j; j++){
            if(map[i][j] != c)
                continue;

            int d = dist(p, (Point){i,j});
            if(d < min_dist){
                min_dist = d;
                nearest = (Point){i,j};
            }
        }
    }
    return nearest;
}

int dist(Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y + p2.y);
}

int abs(int x) {
    if(x < 0)
        return -x;
    return x;
}
