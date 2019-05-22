#include "game.h"
#include <conio.h>
#include <stdlib.h>


void init(FILE *file, int *x, int *y, float *time) {
    *x = getnum(file);
    *y = getnum(file);
    *time = getnum(file);
}

void submit_game(Player *player1, Player *player2) {
    FILE *leader_file = fopen(LEADERBOARD_FILE, "r");
    char content[1000];
    int n = 0, c;
    for (int i = 0; (c = getc(leader_file)) != EOF && i < 1000; i++) {
        content[i] = (char)c;
        if (c == '\n')
            n += 1;
    }
    Game *games = (Game *) malloc(sizeof(Game) * n);
    int nn = 0;
    for (int i = 0; i < len(content);) {
        while (content[i] != '\n') {
            int s1, s2;
            char n1[20], n2[20];
            getname(content, &i, n1);
            s1 = getnum(content, &i);
            s2 = getnum(content, &i);
            getname(content, &i, n2);
            games[nn++] = (Game) {{{0, 0}, s1, ' ', n1},
                                  {{0, 0}, s2, ' ', n2}};
        }
    }
}

int len(char *c) {
    int n = 0;
    while (c[n++]);
    return n - 1;
}

Point *get_objs(char** map, char c, Point max) {
    int n = 0;
    for(int i = 0; i < max.x; i++)
        for(int j = 0; j < max.y; j++)
            if(map[i][j] == c)
                n += 1;
    Point* objs = (Point*)malloc(sizeof(Point)*n);
    int k = 0;
    for(int i = 0; i < max.x; i++)
        for(int j = 0; j < max.y; j++)
            if(map[i][j] == c)
                objs[k++] = (Point){i, j};
    return objs;
}

void getkey(char *STATE1, char *STATE2) {
    char c;
    if (kbhit()) {
        c = getch();
        switch (c) {
            case 'a':
                *STATE1 = 'l';
                break;
            case 'd':
                *STATE1 = 'r';
                break;
            case 'w':
                *STATE1 = 'u';
                break;
            case 's':
                *STATE1 = 'd';
                break;
            case 65:
                *STATE2 = 'u';
                break;
            case 66:
                *STATE2 = 'd';
                break;
            case 67:
                *STATE2 = 'r';
                break;
            case 68:
                *STATE2 = 'l';
                break;
        }
    }
}

void move_player(char **map, Player *player, Point r, Point max) {
    Point new_pos = {player->pos.x + r.x, player->pos.y + r.y};
    char c = map[new_pos.x][new_pos.y];
    if (c == ' ') {
        player->pos.x += 1;
        return;
    }
    if (c == 'B' || c == '!')
        return;
    if (c == 'T') {
        teleport(map, player, get_objs(map, 'T', max), max);
        reobj(map, player->pos, max);
        return;
    }
    if (c == '.') {
        player->score += 1;
        player->pos.x += 1;
        reobj(map, player->pos, max);
        return;
    }
    if (c == 'F') {
        player->score += 5;
        reobj(map, player->pos, max);
        player->pos.x += 1;
        return;
    }
}


void move(char **map,Point max, char *STATE1, char *STATE2, Player *player1, Player *player2) {
    Point r;
    switch (*STATE1) {
        case 'r':
            r = (Point) {player1->pos.x + 1, player1->pos.y};
        case 'l':
            r = (Point) {player1->pos.x - 1, player1->pos.y};
        case 'u':
            r = (Point) {player1->pos.x, player1->pos.y - 1};
        case 'd':
            r = (Point) {player1->pos.x, player1->pos.y + 1};
    }
    move_player(map, player1, r, max);
    r = (Point){0, 0};
    switch (*STATE2) {
        case 'r':
            r = (Point) {player2->pos.x + 1, player2->pos.y};
        case 'l':
            r = (Point) {player2->pos.x - 1, player2->pos.y};
        case 'u':
            r = (Point) {player2->pos.x, player2->pos.y - 1};
        case 'd':
            r = (Point) {player2->pos.x, player2->pos.y + 1};
    }
    move_player(map, player2, r, max);
}

void reobj(char **map, Point p, Point max) {
    char c =  map[p.x][p.y];
    map[p.x][p.y] = ' ';
    Point randp = {rand()%max.x, rand()%max.y};
    while(map[randp.x][randp.y] != ' ')
        randp = (Point){rand()%max.x, rand()%max.y};
    map[randp.x][randp.y] = c;
}

void teleport(char **map, Player *player, Point *teleports, Point max) {
    Point *start, *end;
    if(is_equal(&player->pos, &teleports[0]))
        start = &teleports[0], end = &teleports[1];
    else
        start = &teleports[1], end = &teleports[0];
    player->pos = *end;
    reobj(map, *start, max);
}
