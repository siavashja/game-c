#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "game.h"

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
int main(){
    FILE *file;
    file = fopen("map.txt", "r");
    int x, y;
    float time;
    Player player1, player2;
    if(file == NULL) {
        printf("Cant open the file.(I dunno why !? :)");
        return 0;
    }

    init(file, &x, &y, &time);
    makemap(x,y);
    refresh(time,x,y);
    submit_game(&player1, &player2);
    printf("\n");
}
