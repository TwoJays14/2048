#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <conio.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

/*
 * Game Rules
 * The player must combine tiles containing the same numbers until they reach the number 2048.
 * The tiles can contain only integer values starting from 2, and that are a power of two, like 2, 4, 8, 16, 32, and so on
 */

/*
 *   Implementation Details
 *   A player can swipe 1) up 2) down 3) left 4) right
 *   The board is 4x4 and starts with a random number of squares with each square being a multiple of 2 (e.g. 2, 4, 8, 16 etc.)
 *   When a player chooses which direction to move the squares all squares will move to that direction so long as there is available space to do so or if the adjacent square has the same number then the two squares will combine becoming a single square whose value is the addition of both squares value i.e. 4 + 4 becomes 1 square equalling 8
 *
 *
 * 1) Create board
 * 2) On game init, fill board with a random number of squares with random values (2, 4, 8, 16, 32)
 * 3) Get player to choose which direction to swipe the board
 * 4) Move each tile to the player-specified direction
 *      Constraints:
 *          1) Board space - i.e. is square already at the end of the board, therefore cannot move anymore
 *          2) Adjacent matching numbers => squares become one => value of that square doubles
 *          3) Check winning condition: if any square/tile has the value of 2048
 *  5) After tile moves occur - check if all squares are filled up with numbers - if not -continue game - if so - endgame
 *  6) Generate new random square in available board spaces
 */

struct Numbers {
    int two;
    int four;
    int eight;
    int sixteen;
    int thirtyTwo;
};

void generateRandomNumberFromZeroToThree();
void printBoard();
void onGameInit(char board[4][4]); // fill board with random tiles with random values
int playerChoice();
void turnCalculation(const int *ptrPlayerSelection);
void checkWinningCondition();

char board[4][4] = {
{' ', ' ', ' ', ' '},
{'2', ' ', '2', ' '},
{'2', ' ', '2', ' '},
{' ', '2', ' ', ' '},
};



int main()
{
    srand(time(0));
    // int playerSelection = playerChoice();
    //
    //
    // // printf("%d", (int)board[0][2] - '0' + (int)board[3][1] - '0');
    printBoard(board);
    // printf("%d", playerSelection);
    int playerSelection;
    int *ptrPlayerSelection = &playerSelection;

    do {
        // onGameInit(board);
        *ptrPlayerSelection = playerChoice();
        turnCalculation(ptrPlayerSelection);
        // Turn calculation function
        printBoard(board);
        // Add your game logic here based on playerSelection
    } while (*ptrPlayerSelection != 0);

    return 0;
}


void printBoard(char board[4][4]) {
    printf("---------------------\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == ' ') {
                printf("|    ");
            } else {
                printf("| %c  ", board[i][j]);
            }
        }
        printf("|\n");
        printf("---------------------\n");
    }
}


void generateRandomNumberFromZeroToThree() {
    for (int i = 0; i < 1; i++) {
        const int num = (rand() % (4 - 0)) + 0;

        printf("%d", num);
    }
}

void onGameInit(char board[4][4]) {
    board[0][2] = '2';
    board[3][1] = '2';

    // int length = sizeof(board) / sizeof(board[0]);

    // for(int i = 0; i < 4; i++ ) {
    //     for(int j = 0; j < 4; j++) {
    //         printf("%c\n", board[i][j]);
    //     }
    // }
}

int playerChoice() {
    int readKey;

    printf("Use WASD keys to make a selection:\n");
    printf("W - Up, A - Left, S - Down, D - Right\n");
    printf("Press 'q' to quit.\n");
    printf("Press a key and then Enter: ");

    while(1) {
        readKey = getchar();

        // Clear input buffer
        while (getchar() != '\n' && getchar() != EOF) {}

        switch (readKey) {
            case 'w':
            case 'W':
                printf("Up (W) key pressed\n");
            return 1; // up
            case 's':
            case 'S':
                printf("Down (S) key pressed\n");
            return 2; // down
            case 'a':
            case 'A':
                printf("Left (A) key pressed\n");
            return 3; // left
            case 'd':
            case 'D':
                printf("Right (D) key pressed\n");
            return 4; // right
            case 'q':
            case 'Q':
                printf("Quitting...\n");
            return 0;
            default:
                printf("Invalid input. Use WASD for direction, Q to quit.\n");
        }
        printf("Press a key and then Enter: ");
    }
}

void turnCalculation(const int *ptrPlayerSelection) {
    printf("%d\n", *ptrPlayerSelection);

    // TODO: refactor move directions to the same structure as right
    int length = 4;

        //up
        if(*ptrPlayerSelection == 1) {
            for(int row = 0; row < length; row++) {
                for (int col = 0; col < length; col++) {
                    if(board[row][col] != ' ') {
                        int currentRow = row;
                        while (currentRow > 0 && board[currentRow - 1][col] == ' ') {
                            board[currentRow - 1][col] = board[currentRow][col]; // reassign square with number to row above it
                            board[currentRow][col] = ' ';
                            currentRow--; // decrement current row to check row above it
                            // TODO: figure out how to add adjacent matching numbers together
                            // if(board[currentRow][col] && board[currentRow - 1][col] != ' ') {
                            //     printf("Total: %d\n", (int)board[currentRow][col] + (int)board[currentRow - 1][col] - '0');
                            //     (int)board[currentRow][col] + (int)board[currentRow - 1][col];
                            // }
                            // reassign square back to empty char as number has moved up
                        }
                    }
                }
            }
        }

        // down
        if(*ptrPlayerSelection == 2 ) {
            for(int row = 0; row < length; row++) {
                for(int col = length - 1; col >= 0; col --) {
                    if (board[row][col] != ' ') {
                        int currentRow = row;
                        while (currentRow >= 0 && board[currentRow + 1][col] == ' ') {
                            board[currentRow + 1][col] = board[currentRow][col];
                            board[currentRow][col] = ' ';
                            currentRow--;
                        }
                    }
                }
            }
        }

        // left
        if(*ptrPlayerSelection == 3) {
            for(int row = 0; row < length; row++) {
                for (int col = 0; col < length; col++) {
                    if(board[row][col] != ' ') {
                        int currentCol = col;
                        while (currentCol > 0 && board[row][currentCol - 1] == ' ') {
                            board[row][currentCol - 1] = board[row][currentCol];
                            board[row][currentCol] = ' ';
                            currentCol--;
                        }
                    }
                }
            }
        }

        // right
        if(*ptrPlayerSelection == 4) {
            for(int row = 0; row < length; row++) {
                for (int col = length - 2; col >= 0; col--) {
                    if (board[row][col] != ' ') {
                        int currentCol = col;
                        while (currentCol < length - 1 && board[row][currentCol + 1] == ' ') {
                            board[row][currentCol + 1] = board[row][currentCol];
                            board[row][currentCol] = ' ';
                            currentCol++;
                        }
                    }
                }
            }
        }
    }


