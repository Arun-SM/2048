#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>
#include<curses.h>
using namespace std;
int a[4][4];
int ch;
int inputProcessed;
char choice;
int checkStatus() {
    int done = 1;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if(a[i][j] == 2048) {
                printf("\n\n *** Win *** \n\n");
                exit(0);
            }
            if(a[i][j] == 0) {
                done = 0;
            }
        }
    }
    if(done) {
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                if(a[i][j] == a[i][j+1] || a[j][i] == a[j+1][i])    {
                    return 1;
                }
            }
        }
    }
    if(done) {
        for(int i=0; i<3; i++) {
            if(a[i][3] == a[i+1][3] || a[3][i] == a[3][i+1]) {
                return 1;
            }
        }
    }
    if(!done) {
        return 1;
    }
    else {
        return 0;
    }
}
int getInput() {
    fflush(stdin);
    noecho();
    ch = getch();
    return 0;
}
int displayBoard() {
    refresh();
    for(int i=0; i<21; i++) {
        printf("-");
    }
    printf("\n");
    for(int i=0; i<4; i++) {
        printf("|");
        for(int j=0; j<4; j++) {
            if(a[i][j]) {
                printf("%4d",a[i][j]);
            }
            else {
                printf("    ");
            }
            printf("|");
        }
        printf("\n");
    }
    for(int i=0; i<21; i++) {
        printf("-");
    }
    printf("\n");
    return 0;
}
int moveLeft() {
    for(int i=0; i<4; i++) {
        for(int j=1; j<4; j++) {
            int k=j;
            while(a[i][k-1] == 0 && k>0) {
                a[i][k-1] = a[i][k];
                a[i][k] = 0;
                k--;
                inputProcessed = 1;
            }
        }
        for(int j=1; j<4; j++) {
            if(a[i][j-1] == a[i][j]) {
                a[i][j-1] += a[i][j];
                for(int k=j; k<3; k++) {
                    a[i][k] = a[i][k+1];
                    a[i][k+1] = 0;
                    inputProcessed = 1;
                }
            }
        }
    }
    return 0;
}
int moveRight() {
    for(int i=0; i<4; i++) {
        for(int j=2; j>=0; j--) {
            int k=j;
            while(a[i][k+1] == 0 && k<3) {
                a[i][k+1] = a[i][k];
                a[i][k] = 0;
                k++;
                inputProcessed = 1;
            }
        }
        for(int j=2; j>=0; j--) {
            if(a[i][j+1] == a[i][j]) {
                a[i][j+1] += a[i][j];
                for(int k=j; k>0; k--) {
                    a[i][k] = a[i][k-1];
                    a[i][k-1] = 0;
                    inputProcessed = 1;
                }
            }
        }
    }
    return 0;
}
int moveUp() {
    for(int i=0; i<4; i++) {
        for(int j=1; j<4; j++) {
            int k=j;
            while(a[k-1][i] == 0 && k>0) {
                a[k-1][i] = a[k][i];
                a[k][i] = 0;
                k--;
                inputProcessed = 1;
            }
        }
        for(int j=1; j<4; j++) {
            if(a[j-1][i] == a[j][i]) {
                a[j-1][i] += a[j][i];
                for(int k=j; k<3; k++) {
                    a[k][i] = a[k+1][i];
                    a[k+1][i] = 0;
                    inputProcessed = 1;
                }
            }
        }
    }
    return 0;
}
int moveDown() {
    for(int i=0; i<4; i++) {
        for(int j=2; j>=0; j--) {
            int k=j;
            while(a[k+1][i] == 0 && k<3) {
                a[k+1][i] = a[k][i];
                a[k][i] = 0;
                k++;
                inputProcessed = 1;
            }
        }
        for(int j=2; j>=0; j--) {
            if(a[j+1][i] == a[j][i]) {
                a[j+1][i] += a[j][i];
                for(int k=j; k>0; k--) {
                    a[k][i] = a[k-1][i];
                    a[k-1][i] = 0;
                    inputProcessed = 1;
                }
            }
        }
    }
    return 0;
}
int processInput() {
    inputProcessed = 0;
    if(choice == '1') {
        switch(ch) {
            case KEY_LEFT:  moveLeft(); break;
            case KEY_RIGHT:  moveRight(); break;
            case KEY_UP:    moveUp();   break;
            case KEY_DOWN:  moveDown(); break;
            case 27:    exit(0);
        }
    }
    else {
        switch(ch) {
            case 'a':
            case 'A':   moveLeft(); break;
            case 'w':
            case 'W':   moveUp();   break;
            case 'd':
            case 'D':   moveRight();    break;
            case 's':
            case 'S':   moveDown(); break;
            case 27:    exit(0);
        }
    }
    return 0;
}
int pad2or4() {
    srand(time(NULL));
    int x = rand() % 4;
    int y = rand() % 4;
   //  printf("%d %d",x,y);
    int done = 0;
    while(!done) {
        if(a[x][y]) {
            done = 0;
            x = rand() % 4;
            y = rand() % 4;
            continue;
        }
        else {
            int temp = rand();
            if(temp & 1 && temp/rand() > rand()) {
                a[x][y] = 4;
            }
            else {
                a[x][y] = 2;
            }
            done = 1;
        }
    }
    return 0;
}
int setupKeys() {
    refresh();
    printf("Would you like to Use\n");
    printf("\t1. Arrow Keys (For some reason this won't work on FEW SYSTEMS, PRESS ESC to escape from game)\n");
    printf("\t2. a w s d for LEFT UP DOWN RIGHT\n");
    printf("For input, press 1 / 2 and Enter to Start\n_");
    fflush(stdin);
    choice = getchar();
    while(choice != '1' && choice != '2') {
        printf("\nWrong choice !!! Don't try to be Smart, Press 1 or 2 and Enter to Start\n_");
        fflush(stdin);
        choice = getchar();
        printf("%d\n",choice);
    }
}
int main() {
    setupKeys();
    initscr();
    pad2or4();
    pad2or4();
    while(checkStatus()) {
        displayBoard();
        getInput();
        processInput();
        if(inputProcessed) {
            pad2or4();
        }
        displayBoard();
    }
    printf(" *** You Lose *** ");
    getch();
    endwin();
    return 0;
}
