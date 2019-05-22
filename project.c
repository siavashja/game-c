#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "game.h"


void refresh(float time, Game *game, char **map, int i, int j, int auto_mode) {
    char STATE1, STATE2;
    clock_t start = clock();
    remap(map, game, i, j);
    while (time > 0) {
//        fflush(stdout);

        getkey(&STATE1, &STATE2);
        if (clock() - start > 200) {
            move(map, (Point) {i, j}, &STATE1, &STATE2, game, auto_mode);
            remap(map, game, i, j);
            time -= 0.2;
            printf("\n%.1f", time);
            start = clock();
        }
    }
}

void win(Player *player1, Player *player2) {
    if (player1->score > player2->score) {
        printf("%s won the game!", player1->name);
        return;
    }
    if (player2->score < player1->score) {
        printf("%s won the game!", player2->name);
        return;
    } else {
        printf("it's a draw!");
        return;
    }
}

void input_str(char* str){
    char c;
    while((c = getchar()) != '\n')
        *str++ = c;
}

void set_options(Game *game, int *auto_mode) {
    printf("one player or two?(enter 1 or 2): ");
    int c = getchar();
    if(c == '1')
        *auto_mode = 1;
    else
        *auto_mode = 0;
    getchar();
    printf("\nenter player1's name: ");
    input_str(game->player1.name);
    if(!*auto_mode) {
        printf("\nenter player2's name: ");
        input_str(game->player2.name);
    }
    else{
        game->player2.name[0] = 'C';
        game->player2.name[1] = 'P';
        game->player2.name[2] = 'U';
        game->player2.name[3] = 0;
    }
}

//void move(char** map,char STATE1,char STATE2)
int main() {
    FILE *file;
    file = fopen("F:\\Aref\\P\\c++\\game-c\\map.txt", "r");
    int x, y, points, auto_mode;
    float time;
    Player player1 = {{1,1}, 0, "ali", 'c'}, player2 = {{2,2}, 0, "ali", 'x'};
    Game game = {player1, player2};
    if (file == NULL) {
        printf("Cannot open the file.(I dunno why !? :))");
        return 0;
    }

    init(file, &x, &y, &time, &points);
    set_options(&game, &auto_mode);
    char **map = makemap(x, y);
    refresh(time, &game, map, x, y, auto_mode);
    submit_game(&game);
    printf("\n");
    win(&player1, &player2);
}
