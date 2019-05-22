#include "game.h"
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void init(FILE *file, int *x, int *y, float *time, int *points) {
    *x = getnum(file);
    *y = getnum(file);
    *time = getnum(file);
    *points = getnum(file);
}

void submit_game(Game *game) {
    FILE *leader_file = fopen(LEADERBOARD_FILE, "r");
    char content[1000];
    int n = 0, c;
    for (int i = 0; (c = getc(leader_file)) != EOF && i < 1000; i++) {
        content[i] = (char) c;
        if (c == '\n')
            n += 1;
    }
    printf("n: %d\n", n);
    fclose(leader_file);
    Game *games = (Game *) malloc(sizeof(Game) * n);
    int nn = 0;
    for (int i = 0; i < len(content) && nn < n;) {
        int s1, s2;
        char n1[20], n2[20];
        clear(n1, 20);
        clear(n2, 20);
        getname(content, &i, n1);
        s1 = getnum2(content, &i);
        s2 = getnum2(content, &i);
        getname(content, &i, n2);
        printf("%s %d %d %s\n", n1, s1, s2, n2);
        games[nn++] = (Game) {{{0, 0}, s1, ' ',},
                              {{0, 0}, s2, ' ',}};
        strcpy(games[nn - 1].player1.name, n1);
        strcpy(games[nn - 1].player2.name, n2);
        printf("done?!\n");
    }
    printf("indexing\n");
    int index = find_game(games, game, n);
    if (index == -1) {
        leader_file = fopen(LEADERBOARD_FILE, "a");
        fprintf(leader_file, "%s %d %d %s\n", game->player1.name, game->player1.score, game->player2.score,
                game->player2.name);
        return;
    }

    leader_file = fopen(LEADERBOARD_FILE, "w");
    games[index] = *game;
    for (int i = 0; i < n; i++) {
        Game *game = &games[i];
        fprintf(leader_file, "%s %d %d %s\n", game->player1.name, game->player1.score, game->player2.score,
                game->player2.name);
    }
}

int len(char *c) {
    int n = 0;
    while (c[n++]);
    return n - 1;
}

Point *get_objs(char **map, char c, Point max) {
    int n = 0;
    for (int i = 0; i < max.x; i++)
        for (int j = 0; j < max.y; j++)
            if (map[i][j] == c)
                n += 1;
    Point *objs = (Point *) malloc(sizeof(Point) * n);
    int k = 0;
    for (int i = 0; i < max.x; i++)
        for (int j = 0; j < max.y; j++)
            if (map[i][j] == c)
                objs[k++] = (Point) {i, j};
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
            case 'i':
                *STATE2 = 'u';
                break;
            case 'k':
                *STATE2 = 'd';
                break;
            case 'l':
                *STATE2 = 'r';
                break;
            case 'j':
                *STATE2 = 'l';
                break;
        }
    }
}

void move_player(char **map, Player *player, Point r, Point max) {
    char c = map[r.x][r.y];
    if (c == 'B' || c == '!')
        return;
    map[player->pos.x][player->pos.y] = ' ';
    player->pos = r;
    if (c == ' ') {
        return;
    }
    if (c == 'T') {
        teleport(map, player, get_objs(map, 'T', max), max);
        reobj(map, player->pos, max);
        return;
    }
    if (c == '.') {
        player->score += 1;
        reobj(map, player->pos, max);
        return;
    }
    if (c == 'F') {
        player->score += 5;
        reobj(map, player->pos, max);
        return;
    }
}


void move(char **map, Point max, char *STATE1, char *STATE2, Game *game, int auto_mode) {
    Point r = {0, 0};
    printf("state: %c\n", *STATE1);
    switch (*STATE1) {
        case 'r':
            r = (Point) {game->player1.pos.x, game->player1.pos.y + 1};
            break;
        case 'l':
            r = (Point) {game->player1.pos.x, game->player1.pos.y - 1};
            break;
        case 'u':
            r = (Point) {game->player1.pos.x - 1, game->player1.pos.y};
            break;
        case 'd':
            r = (Point) {game->player1.pos.x + 1, game->player1.pos.y};
            break;
    }
    move_player(map, &game->player1, r, max);
    r = (Point) {0, 0};
    if (auto_mode)
        *STATE2 = get_best_action(map, game, max);
    switch (*STATE2) {
        case 'r':
            r = (Point) {game->player2.pos.x, game->player2.pos.y + 1};
            break;
        case 'l':
            r = (Point) {game->player2.pos.x, game->player2.pos.y - 1};
            break;
        case 'u':
            r = (Point) {game->player2.pos.x - 1, game->player2.pos.y};
            break;
        case 'd':
            r = (Point) {game->player2.pos.x + 1, game->player2.pos.y};
            break;
    }
    move_player(map, &game->player2, r, max);
}

void reobj(char **map, Point p, Point max) {
    char c = map[p.x][p.y];
    map[p.x][p.y] = ' ';
    Point randp = {rand() % max.x, rand() % max.y};
    while (map[randp.x][randp.y] != ' ')
        randp = (Point) {rand() % max.x, rand() % max.y};
    map[randp.x][randp.y] = c;
}

void teleport(char **map, Player *player, Point *teleports, Point max) {
    Point *start, *end;
    if (is_equal(&player->pos, &teleports[0]))
        start = &teleports[0], end = &teleports[1];
    else
        start = &teleports[1], end = &teleports[0];
    player->pos = *end;
    reobj(map, *start, max);
}

int getnum2(char *str, int *i) {
    char c;
    int n = 0;
    while ((c = str[(*i)++]) != ' ')
        n = n * 10 + c - '0';
    return n;
}

void getname(char *str, int *i, char *n) {
    char c;
    while ((c = str[(*i)++]) != ' ' && c != '\n')
        *n++ = c;
}

int find_game(Game *games, Game *game, int size) {
    printf("game:%s, %s\n", game->player1.name, game->player2.name);
    for (int i = 0; i < size; i++) {
        printf("game[%d]:%s, %s\n", i, games[i].player1.name, games[i].player2.name);
        if (strcmp(games[i].player1.name, game->player1.name) == 0 ||
            strcmp(games[i].player1.name, game->player2.name) == 0)
            if (strcmp(games[i].player2.name, game->player1.name) == 0 ||
                strcmp(games[i].player2.name, game->player2.name) == 0)
                return i;
    }
    return -1;
}

char get_best_action(char **map, Game *game, Point max) {
    Point best_point = nearest_char(map, game->player2.pos, '.', max.x, max.y);
    int direct_dist = dist(game->player2.pos, best_point);
    //use teleport dist
    Point *teleports = get_objs(map, 'T', max);
    Point nearest_teleport;
    int undirect_dist;
    if (dist(teleports[0], game->player2.pos) < dist(teleports[1], game->player2.pos)) {
        undirect_dist = dist(teleports[0], game->player2.pos) +
                        dist(teleports[1], nearest_char(map, teleports[1], '.', max.x, max.y));
        nearest_teleport = teleports[0];
    } else {
        undirect_dist = dist(teleports[1], game->player2.pos) +
                        dist(teleports[0], nearest_char(map, teleports[0], '.', max.x, max.y));
        nearest_teleport = teleports[1];
    }

    Point target;
    if (direct_dist < undirect_dist)
        target = best_point;
    else
        target = nearest_teleport;

    return choose_dir(game->player2.pos, target);
}

char choose_dir(Point start, Point end) {
    static char last = ' ';
    char dir = 0;
    if (start.x < end.x && last != 'd')
        dir = 'd';
    else if (start.x > end.x && last != 'u')
        dir = 'u';
    else if (start.y < end.y && last != 'r')
        dir = 'r';
    else if (start.y > end.y && last != 'l')
        dir = 'l';
    last = dir;
    return dir;
}

void clear(char *c, int size) {
    for (int i = 0; i < size; i++)
        c[i] = 0;
}
