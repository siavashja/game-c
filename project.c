#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "game.h"

clock_t start;

void refresh(float time, char **map, int i, int j) {

    while (time > 0) {
        fflush(stdout);


        if (clock() - start > 200) {
            remap(map, i, j);
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


//void move(char** map,char STATE1,char STATE2)
int main() {
    FILE *file;
    file = fopen("map.txt", "r");
    int x, y;
    float time;
    Player player1, player2;
    Game game;
    if (file == NULL) {
        printf("Cant open the file.(I dunno why !? :)");
        return 0;
    }

    init(file, &x, &y, &time);
    char** map = makemap(x, y);
    refresh(time, map, x, y);
    submit_game(&game);
    printf("\n");
    win(&player1, &player2);
}
