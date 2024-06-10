/* Author: Caitlin Coulombe, T00756521
 * Date: June 8, 2024
 * Course: COMP 2131
 * Assignment 1: Create a Tic tac Toe game designed for one player (against the computer). You will need to create arrays and functions to complete this program.
 *      1. THe first screen should ask the user their name, print a welcome message, and display an empty 3x3 tic tac toe board. 
 *      2. Then the program should ask the user to put the coordinates of their move. One the user enters the coordinates, the program should respond accordingly with a print of the user's move and the compuer's move. This should go on until a winning pattern is found. 
 * After you complete the program, copy the code from UNIX environment to a text file and upload the 'C' file to the OLF member
 */

// import headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// function protoypes
void displayBoard(void);
int checkMove(int x, int y);
void updateBoard(int x, int y, int turn);
void compMove(void);
int checkWinner(void);
int checkCol(void);
int checkRow(void);
int checkDiag(void);

// global variables
char board[3][3];
int winner;

#define USER 1
#define COMP 2


int main(void)
{
    // Local variables
    char playerName[30];
    char another[10] = "y";

    int xCoor;
    int yCoor;

    printf("Welcome to Tic Tac Toe. What is your name?\n");
    scanf("%s", playerName);

    printf("Hello %s! You will be X and I will be O.\n", playerName);

    while(strcmp(another, "y") == 0 || strcmp(another, "Y") == 0)
    {
        printf("Lets play! Good luck %s!\n", playerName);
        // clear the board and reset the winner
        memset(board, 0, sizeof board);
        winner = 0;

        displayBoard();
        
        while(!winner)
        {
            printf("Enter the 0-indexed X,Y coordinates for your next move: ");
            scanf("%d,%d", &xCoor, &yCoor);
            while(!checkMove(xCoor, yCoor))
            {
                printf("Invalid position, must be an unoccupied spot in the 3x3 grid: ");
                scanf("%d,%d", &xCoor, &yCoor);
            }
            updateBoard(xCoor, yCoor, USER);
            if(checkWinner())
            {
                winner = USER;
                break;
            }

            compMove();

            if(checkWinner())
            { 
                winner = COMP;
                break;
            }
            displayBoard();
        }

        if(winner == USER)
        {
            printf("\n*** You win! ***\n");
            displayBoard();
        }
        else
        {
            printf("\nComputer wins!\n");
            displayBoard();
        }
        
        printf("\nDo you want to play another round? (y/n)\n");
        scanf("%s", another);
    }
    printf("Thanks for playing!\n");
}

//-----------------------------------------------------------------------------------------------------------
// compMove() make a random move for the computer and determine if it is valid. if so, display the board
//-----------------------------------------------------------------------------------------------------------
void compMove()
{
    int xCoor;
    int yCoor;

    // generate a different random seed each time the program is run
    srand(time(NULL));

    xCoor = rand() % 3;
    yCoor = rand() % 3;

    while(!checkMove(xCoor, yCoor))
    {
        xCoor = rand() % 3;
        yCoor = rand() % 3;
    }

    updateBoard(xCoor, yCoor, COMP);
}

//-----------------------------------------------------------------------------------------------------------
// checkMove(int x, int y) check that the space at the coordinates x,y is available for the move to be made
//-----------------------------------------------------------------------------------------------------------
int checkMove(int xCoor, int yCoor)
{
    if(xCoor >= 0 && xCoor <= 2 && yCoor >= 0 && yCoor <= 2)
    {
        return board[xCoor][yCoor] == 0;
    }

    return 0;
}

//-----------------------------------------------------------------------------------------------------------
// displayBoard() prints the current board incuding all moves made until this point
//-----------------------------------------------------------------------------------------------------------
void displayBoard()
{
    // display the board and all the content in it
    // printf("  %c | %c | %c\n---|---|---\n  %c | %c | %c\n---|---|---\n  %c | %c | %c\n", board[0][0], board[1][0], board[2][0], board[0][1], board[1][1], board[2][1], board[0][2], board[1][2], board[2][2]);
    printf("  %c | %c | %c\n-----------\n  %c | %c | %c\n-----------\n  %c | %c | %c\n", board[0][0], board[1][0], board[2][0], board[0][1], board[1][1], board[2][1], board[0][2], board[1][2], board[2][2]);
}

//-----------------------------------------------------------------------------------------------------------
// updateBoard(int , int y, int turn) update the board with an X or an O (depending on whose turn it is) in the specified position using the x,y coordinates
//-----------------------------------------------------------------------------------------------------------
void updateBoard(int xCoor, int yCoor, int turn)
{
    if(turn == USER)
    {
        board[xCoor][yCoor] = 'X';
    }
    else
    {
        board[xCoor][yCoor] = 'O';
    }
}

//-----------------------------------------------------------------------------------------------------------
// checkWinner() checks the board to see if either player has won and displays the corresponding announcement
//-----------------------------------------------------------------------------------------------------------
int checkWinner()
{
    return checkCol() || checkRow() || checkDiag();
}

//-----------------------------------------------------------------------------------------------------------
// checkCol() checks each column to see if either player has won
//-----------------------------------------------------------------------------------------------------------
int checkCol()
{
    for(int i = 0; i <= 2; i++)
    {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && (board[0][i] == 'X' || board[0][i] == 'O'))
        {
            // printf("win col, i = %d", i);
            return 1;
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------------------------------------
// checkRow() checks each row to see if either player has won
//-----------------------------------------------------------------------------------------------------------
int checkRow()
{
    for(int i = 0; i <= 2; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && (board[i][0] == 'X' || board[i][0] == 'O'))
        {
            // printf("win row");
            return 1;
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------------------------------------
// checkDiag() checks each diagonal to see if either player has won
//-----------------------------------------------------------------------------------------------------------
int checkDiag()
{
    if((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[2][0] == board[1][1] && board[1][1] == board[0][2]) && (board[1][1] == 'X' || board[1][1] == 'O'))
        {
            // printf("win diag.");
            return 1;
        }

    return 0;
}