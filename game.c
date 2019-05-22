#include "game.h"
//#include <conio.h>
#include <stdlib.h>


void init(FILE *file, int *x, int *y, float *time) {
    *x = getnum(file);
    *y = getnum(file);
    *time = getnum(file);
}

void submit_game(Player *player1, Player *player2) {
    FILE *leader_file = fopen(LEADERBOARD_FILE, "r");
    char c, content[1000];
    int n = 0;
    for (int i = 0; (c = getc(leader_file)) != EOF && i < 1000; i++) {
        content[i] = c;
        if (c == '\n')
            n += 1;
    }
    Game *games = (Game *) malloc(sizeof(Game) * n);
    int nn = 0;
    for(int i = 0; i < len(content);){
        while(content[i] != '\n'){
            int s1, s2;
            char n1[20], n2[20];
            getname(content,&i, n1);
            s1 = getnum(content, &i);
            s2 = getnum(content, &i);
            getname(content, &i, n2);
            games[nn++] = (Game){{{0,0}, s1, ' ', n1}, {{0,0}, s2, ' ', n2}};
        }
    }
}

int len(char *c) {
    int n = 0;
    while(c[n++]);
    return n-1;
}

//Point *get_all_objs(Game *game) {
//    Point *objs = (Point *) malloc(sizeof(Point) * (5 + game->n_wall + game->n_block + game->n_point));
//    objs[0] = game->player1;
//    objs[1] = game->player2;
//    objs[2] = game->tele1;
//    objs[3] = game->tele2;
//    objs[4] = game->F;
//
//    for (int i = 0; i < game->n_wall; i++)
//        objs[i + 5] = game->wall[i];
//
//    for (int i = 0; i < game->n_block; i++)
//        objs[i + 5 + game->n_wall] = game->block[i];
//
//    for (int i = 0; i < game->n_point; i++)
//        objs[i + 5 + game->n_wall + game->n_block] = game->point[i];
//
//    return objs;
//}
//
//void getkey(char *STATE1, char *STATE2) {
//    char c;
//    if (kbhit()) {
//        c = getch();
//        switch (c) {
//            case 'a':
//                STATE1 = "left";
//                break;
//            case 'd':
//                STATE1 = "right";
//                break;
//            case 'w':
//                STATE1 = "up";
//                break;
//            case 's':
//                STATE1 = "down";
//                break;
//            case 65:
//                STATE2 = "up";
//                break;
//            case 66:
//                STATE2 = "down";
//                break;
//            case 67:
//                STATE2 = "right";
//                break;
//            case 68:
//                STATE2 = "left";
//                break;
//        }
//    }
//}
