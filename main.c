#include <stdio.h>
#include <raylib.h>
#include <time.h>

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
void onGameInit(const char *board[4][4]); // fill board with random tiles with random values
int playerChoice();
void checkWinningCondition();

char board[4][4] = {
{' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' '},
};


int main()
{
    srand(time(0));


    return 0;
}


void generateRandomNumberFromZeroToThree() {
    for (int i = 0; i < 1; i++) {
        const int num = (rand() % (4 - 0)) + 0;

        printf("%d", num);
    }
}
