#include "game.h"
#include <conio.h>
#include <stdlib.h>

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
