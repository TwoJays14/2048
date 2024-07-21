#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <stdbool.h>
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

// TODO: add logic to add numbers based what numbers are currently on the board i.e. more smaller number make it more likely to add 2 || 4 etc.

struct Numbers {
    int two;
    int four;
    int eight;
};

void generateRandomNumberFromZeroToThree(int *randNum);
void generateRandomNumberFromZeroToTwo(int *randNum);
void printBoard(int board[4][4]);
void onGameInit(int board[4][4]); // fill board with random tiles with random values
int playerChoice();
void turnCalculation(const int *ptrPlayerSelection);
void addNewNumberToBoard(int board[4][4]);
bool isGameWon();


int board[4][4] = {
{0, 4, 8, 16},
{0, 4, 8, 16},
{0, 4, 8, 16},
{0, 4, 8, 16},
};



int main()
{
    srand(time(0));
    // int playerSelection = playerChoice();
    //
    //
    // // printf("%d", (int)board[0][2] - '0' + (int)board[3][1] - '0');
    // printf("%d", playerSelection);
    int playerSelection;
    int *ptrPlayerSelection = &playerSelection;

    // start game
    // onGameInit(board);
    printBoard(board);

    do {
        // get player choiace
        *ptrPlayerSelection = playerChoice();
        // Turn calculation function
        turnCalculation(ptrPlayerSelection);
        // add new number to board
        addNewNumberToBoard(board);
        // reprint board
        printBoard(board);
        // Add your game logic here based on playerSelection
    } while (!isGameWon(board));
    // } while (*ptrPlayerSelection != 0);


    return 0;


}


void printBoard(int board[4][4]) {
    printf("---------------------\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                printf("|    ");
            } else {
                printf("| %3d", board[i][j]);
            }
        }
        printf("|\n");
        printf("---------------------\n");
    }
}



void generateRandomNumberFromZeroToThree(int *randNum) {
    *randNum = rand() % 4;
}

void generateRandomNumberFromZeroToTwo(int *randNum) {
    *randNum = rand() % 3;
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

    const int length = 4;

    //up
    if(*ptrPlayerSelection == 1) {
        for(int row = 0; row < length; row++) {
            for (int col = 0; col < length; col++) {
                if(board[row][col] != 0) {
                    int currentRow = row;
                    while (currentRow > 0 && board[currentRow - 1][col] == 0) {
                        board[currentRow - 1][col] = board[currentRow][col]; // reassign square with number to row above it
                        board[currentRow][col] = 0;
                        currentRow--; // decrement current row to check row above it
                    }
                    // Add adjacent numbers together if matching
                    if(board[currentRow - 1][col] == board[currentRow][col]) {
                        board[currentRow - 1][col] += board[currentRow][col] ;
                        board[currentRow][col] = 0;
                    }
                }
            }
        }
    }

    // down
    if(*ptrPlayerSelection == 2 ) {
        for(int row = 0; row < length; row++) {
            for(int col = length - 1; col >= 0; col--) {
                if (board[row][col] != 0) {
                    int currentRow = row;
                    while (currentRow >= 0 && board[currentRow + 1][col] == 0) {
                        board[currentRow + 1][col] = board[currentRow][col];
                        board[currentRow][col] = 0;
                        currentRow--;
                    }
                    // Add adjacent numbers together if matching
                    if(board[currentRow + 1][col] == board[currentRow][col]) {
                        board[currentRow + 1][col] += board[currentRow][col];
                        board[currentRow][col] = 0;
                    }
                }
            }
        }
    }

        // left
        if(*ptrPlayerSelection == 3) {
            for(int row = 0; row < length; row++) {
                for (int col = 0; col < length; col++) {
                    if(board[row][col] != 0) {
                        int currentCol = col;
                        while (currentCol > 0 && board[row][currentCol - 1] == 0) {
                            board[row][currentCol - 1] = board[row][currentCol];
                            board[row][currentCol] = 0;
                            currentCol--;
                        }
                        // Add adjacent numbers together if matching
                        if(board[row][currentCol - 1] == board[row][currentCol]) {
                            board[row][currentCol - 1] += board[row][currentCol] ;
                            board[row][currentCol] = 0;
                            // reassign square back to empty char as number has moved up
                        }
                    }
                }
            }
        }

        // right
        if(*ptrPlayerSelection == 4) {
            for(int row = 0; row < length; row++) {
                for (int col = length - 1; col >= 0; col--) {
                    if (board[row][col] != 0) {
                        int currentCol = col;
                        while (currentCol < length - 1 && board[row][currentCol + 1] == 0) {
                            board[row][currentCol + 1] = board[row][currentCol];
                            board[row][currentCol] = 0;
                            currentCol++;
                        }
                        // Add adjacent numbers together if matching
                        if(currentCol < length - 1 && board[row][currentCol + 1] == board[row][currentCol]) {
                            board[row][currentCol + 1] += board[row][currentCol];
                            board[row][currentCol] = 0;
                            // reassign square back to empty char as number has moved up
                        }
                    }
                }
            }
        }
    }

void addNewNumberToBoard(int board[4][4]) {
    struct Numbers numbers;
    numbers.two = 2;
    numbers.four = 4;
    numbers.eight = 8;

    const int numbersArray[3] = {numbers.two, numbers.four, numbers.eight};


    int randNum1, randNum2;
    generateRandomNumberFromZeroToThree(&randNum1);
    generateRandomNumberFromZeroToThree(&randNum2);

    while (board[randNum1][randNum2] != 0) {
        generateRandomNumberFromZeroToThree(&randNum1);
        generateRandomNumberFromZeroToThree(&randNum2);
    }

    int randIndex;
    generateRandomNumberFromZeroToTwo(&randIndex);
    board[randNum1][randNum2] = numbersArray[randIndex];


}

bool isGameWon(int board[4][4]) {
    int counter = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                counter++;
            }
            if (board[i][j] == 2048) {
                printf("Congratulations! You Win!\n");
                return true;
            }
        }
    }

    if (counter == 16) {
        printf("You lose!");
        exit(0);
    }


    return false;
}



