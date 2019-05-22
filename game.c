#include "game.h"
#include <conio.h>
#include <stdlib.h>


Point *get_all_objs(Game *game) {
    Point *objs = (Point *) malloc(sizeof(Point) * (5 + game->n_wall + game->n_block + game->n_point));
    objs[0] = game->player1;
    objs[1] = game->player2;
    objs[2] = game->tele1;
    objs[3] = game->tele2;
    objs[4] = game->F;

    for (int i = 0; i < game->n_wall; i++)
        objs[i + 5] = game->wall[i];

    for (int i = 0; i < game->n_block; i++)
        objs[i + 5 + game->n_wall] = game->block[i];

    for (int i = 0; i < game->n_point; i++)
        objs[i + 5 + game->n_wall + game->n_block] = game->point[i];

    return objs;
}
void tel(char** map,Player *player1,Player *player2,Point *objs,int max_i,int max_j){

    if(player1.pos==objs[2]){
        player1.pos=objs[3];
        objs[2]=' ';
        objs[3]=' ';
        tele(map,max_i,max_j);
        return;

    }
    if(player1.pos==objs[3]){
        player1.pos=objs[2];
        objs[2]=' ';
        objs[3]=' ';
        tele(map,max_i,max_j);
        return;

    }
    if(player2.pos=objs[2]){
        player2.pos=objs[3];
        objs[2]=' ';
        objs[3]=' ';
        tele(map,max_i,max_j);
        return;

    }
    if(player2.pos=objs[3]){
        player2.pos=objs[2];
        objs[2]=' ';
        objs[3]=' ';
        tele(map,max_i,max_j);
        return;

    }
}
void getkey(char *STATE1, char *STATE2) {
    char c;
    if (kbhit()) {
        c = getch();
        switch (c) {
            case 'a':
                STATE1 = "left";
                break;
            case 'd':
                STATE1 = "right";
                break;
            case 'w':
                STATE1 = "up";
                break;
            case 's':
                STATE1 = "down";
                break;
            case 65:
                STATE2 = "up";
                break;
            case 66:
                STATE2 = "down";
                break;
            case 67:
                STATE2 = "right";
                break;
            case 68:
                STATE2 = "left";
                break;
        }
    }
}
void repoint(char** map,int i,int j,int max_i,int,max_j){
    int x;
    int y;
    int n=1;
    map[i][j]=' ';
    while(n>0){
        x=rand()%max_i;
        y=rand()%max_j;
        if(map[x][y]==' '){
            map[x][y]=='.';
            n--;
        }
    }

}
void ref(char** map,int i,int j,int max_i,int,max_j){
    int x;
    int y;
    int n=1;
    map[i][j]=' ';
    while(n>0){
        x=rand()%max_i;
        y=rand()%max_j;
        if(map[x][y]==' '){
            map[x][y]=='F';
            n--;
        }
    }

}
void move(char** map,char *STATE1,char *STATE2,Player *player1,Player *player2){
    int x=player1.pos.x;
    int y=player1.pos.y;
    int i=player2.pos.x;
    int j=player2.pos.y;

    switch(STATE1){
        case "right":
            if(map[player1.pos.x+1]==' '){
                player1.pos.x+=1;
                break;
            }
            if(map[player1.pos.x+1]=='B'|| map[player1.pos.x+1]=='!')
                break;
            if(map[player1.pos.x+1]=='T'){
                tel();
                break;
            }
            if(map[player1.pos.x+1]=='.'){
                player1.score+=1;
                repoint(map,x+1,y,max_i,max_j);
                player1.pos.x+=1;
                break;
            }
            if(map[player1.pos.x+1]=='F'){
                player1.score+=5;
                ref(map,x+1,y,max_i,max_j);
                player1.pos.x+=1;
                break;
            }
            break;
        case "left":
            if(map[player1.pos.x-1]==' '){
                player1.pos.x-=1;
                break;
            }
            if(map[player1.pos.x-1]=='B'|| map[player1.pos.x-1]=='!')
                break;
            if(map[player1.pos.x-1]=='T'){
                tel();
                break;
            }
            if(map[player1.pos.x-1]=='.'){
                player1.score+=1;
                repoint(map,x-1,y,max_i,max_j);
                player1.pos.x-=1;
                break;
            }
            if(map[player1.pos.x-1]=='F'){
                player1.score+=5;
                ref(map,x-1,y,max_i,max_j);
                player1.pos.x-=1;
                break;
            }
            break;
        case "up":
            if(map[player1.pos.y+1]==' '){
                player1.pos.y+=1;
                break;
            }
            if(map[player1.pos.y+1]=='B'|| map[player1.pos.y+1]=='!')
                break;
            if(map[player1.pos.y+1]=='T'){
                tel();
                break;
            }
            if(map[player1.pos.y+1]=='.'){
                player1.score+=1;
                repoint(map,x,y+1,max_imax_j);
                player1.pos.y+=1;
                break;
            }
            if(map[player1.pos.y+1]=='F'){
                player1.score+=5;
                ref(map,x,y+1,max_i,max_j);
                player1.pos.y+=1;
                break;
            }
            break;
        case "down":
            if(map[player1.pos.y-1]==' '){
                player1.pos.y-=1;
                break;
            }
            if(map[player1.pos.y-1]=='B'|| map[player1.pos.y-1]=='!')
                break;
            if(map[player1.pos.y-1]=='T'){
                tel();
                break;
            }
            if(map[player1.pos.y-1]=='.'){
                player1.score+=1;
                repoint(map,x,y-1,max_i,max_j);
                player1.pos.y-=1;
                break;
            }
            if(map[player1.pos.y-1]=='F'){
                player1.score+=5;
                ref(map,x,y-1,max_i,max_j;
                player1.pos.y-=1;
                break;
            }
            break;
    }
    switch(STATE2){
        case "right":
            if(map[player2.pos.x+1]==' '){
                player2.pos.x+=1;
                break;
            }
            if(map[player2.pos.x+1]=='B'|| map[player2.pos.x+1]=='!')
                break;
            if(map[player2.pos.x+1]=='T'){
                tel();
                break;
            }
            if(map[player2.pos.x+1]=='.'){
                player2.score+=1;
                repoint(map,i+1,j,max_i,max_j);
                player2.pos.x+=1;
                break;
            }
            if(map[player.pos.x+1]=='F'){
                player2.score+=5;
                ref(map,i+1,j,max_i,max_j);
                player2.pos.x+=1;
                break;
            }
            break;
        case "left":
            if(map[player2.pos.x-1]==' '){
                player2.pos.x-=1;
                break;
            }
            if(map[player2.pos.x-1]=='B'|| map[player2.pos.x-1]=='!')
                break;
            if(map[player2.pos.x-1]=='T'){
                tel();
                break;
            }
            if(map[player2.pos.x-1]=='.'){
                player2.score+=1;
                repoint(map,i-1,j,max_i,max_j);
                player2.pos.x-=1;
                break;
            }
            if(map[player2.pos.x-1]=='F'){
                player2.score+=5;
                ref(map,i-1,j,max_i,max_j);
                player2.pos.x-=1;
                break;
            }
            break;
        case "up":
            if(map[player2.pos.y+1]==' '){
                player2.pos.y+=1;
                break;
            }
            if(map[player2.pos.y+1]=='B'|| map[player2.pos.y+1]=='!')
                break;
            if(map[player2.pos.y+1]=='T'){
                tel();
                break;
            }
            if(map[player2.pos.y+1]=='.'){
                player2.score+=1;
                repoint(map,i,j+1,max_i,max_j);
                player2.pos.y+=1;
                break;
            }
            if(map[player2.pos.y+1]=='F'){
                player2.score+=5;
                ref(map,i,j+1,max_i,max_j);
                player2.pos.y+=1;
                break;
            }
            break;
        case "down":
            if(map[player2.pos.y-1]==' '){
                player2.pos.y-=1;
                break;
            }
            if(map[player2.pos.y-1]=='B'|| map[player2.pos.y-1]=='!')
                break;
            if(map[player2.pos.y-1]=='T'){
                tel();
                break;
            }
            if(map[player2.pos.y-1]=='.'){
                player2.score+=1;
                repoint(map,i,j-1,max_i,max_j);
                player2.pos.y-=1;
                break;
            }
            if(map[player2.pos.y-1]=='F'){
                player2.score+=5;
                ref(map,i,j-1,max_i,max_j);
                player2.pos.y-=1;
                break;
            }
            break;
        }
}
