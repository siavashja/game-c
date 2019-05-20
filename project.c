#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include "map.h"
#include "game.h"


int get_time(){
    float second=getnum();
    return second;
}

clock_t start;
void refresh(time,map,i,j){

    while(time>0){
        fflush(stdout);


        if(clock()-start>200){
            remap(map,i,j);
            time-=0.2;
            printf("\n%.1f",time);
            start=clock();
        }
    }
}

//void move(char** map,char STATE1,char STATE2)
main(){
    int x=getnum();
    int y=getnum();
    int max_i=x;
    int max_j=y;
    float time=get_time();
    makemap(x,y);
    refresh(time,max_i,max_j);
}