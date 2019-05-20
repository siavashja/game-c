#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

int getnum(){

    int a=0;
    int b;
    while((b=getchar())!='\n' && b!= ' '&& b!= EOF)
        a=a*10+(b-'0');
    return a;
}

char** makemap(int x,int y){

    //int x=getnum();
    //int y=getnum();

    //char map[x+1][y+1];
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
void getkey(char* STATE1,char* STATE2){
    char c;
    while(!kbhit())
        c=getch();
    switch(c){
        case 'a':
            STATE1="left";
            break;
        case 'd':
            STATE1="right";
            break;
        case 'w':
            STATE1="up";
            break;
        case 's':
            STATE1="down";
            break;
        case 65:
            STATE2="up";
            break;
        case 66:
            STATE2="down";
            break;
        case 67:
            STATE2="right";
            break;
        case 68:
            STATE2="left";
            break;
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
