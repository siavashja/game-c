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

void getkey(char *STATE1, char *STATE2) {
    char c;
    while (!kbhit())
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
