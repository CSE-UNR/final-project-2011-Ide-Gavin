//Final Project
//Gavin Ide
//07-26/24

#include <stdio.h>

#define FILE_NAME "easy.txt"
#define SIZE 10

void loadGame(char board[][SIZE]);
void displayGuess(char board[][SIZE]);
int checkHit(char fileBoard[][SIZE], char userBoard[][SIZE], int row, int col);
int playerMove(int *row, int *col);
void showScore(int movesMade);
int checkBoard(char board[][SIZE]);
void resetBoard(char board[][SIZE]);

int main(){
    char fileBoard[SIZE][SIZE];
    char userBoard[SIZE][SIZE];
    int inputRow;
    int inputCol;
    char playAgain = 'Y';
    
    printf("\n*****LET'S PLAY BATSHIP*****\n");
    loadGame(fileBoard);
    resetBoard(userBoard);
    displayGuess(userBoard);
    

    while(playAgain == 'Y'){
        resetBoard(userBoard);
        int movesMade = 0;
        
        do{
            if (playerMove(&inputRow, &inputCol) == 0){
                checkHit(fileBoard, userBoard, inputRow, inputCol);
                displayGuess(userBoard);
                movesMade++;
            }
        }while(!checkBoard(fileBoard)); 

        showScore(movesMade); 

        printf("Play again (Y/N): ");
        scanf(" %c", &playAgain);
    }
    return 0;
}

void loadGame(char board[][SIZE]){
    FILE *fp;
    int indRow, indCol;

    fp = fopen("easy.txt", "r");

    if (fp == NULL){
        printf("Cannot open file.\n");
        return;
    }
    for(indRow = 0; indRow < SIZE; indRow++){
        for(indCol = 0; indCol < SIZE; indCol++){
            fscanf(fp, " %c", &board[indRow][indCol]);
        }
    }
    fclose(fp);
}

int playerMove(int *row, int *col){
    char column;
    
    if(scanf(" %c%d", &column, row) == 2){
        if(column < 'A' || column > 'J'){
            printf("Invalid column letter. Try again!\n");
            return -1; // check why this is here 
        }
        *col = column - 'A';
        if(*row < 1 || *row >10){
            printf("Invalid row number. Try again!\n");
            return -1; //check this again
        }    
        *row -= 1;
        return 0;
    }
    return -1; //check this again
}

int checkHit(char fileBoard[][SIZE], char userBoard[][SIZE], int row, int col){
    if (fileBoard[row][col] == 'S') {
        userBoard[row][col] = 'X';
        fileBoard[row][col] = 'X';
    } else {
        userBoard[row][col] = 'O';
    }
    return 0;
}

void displayGuess(char board[][SIZE]){
    printf("  ");
    for (char c = 'A'; c < 'A' + SIZE; c++){
        printf(" %c", c);
    }
    printf("\n");

    for (int iRow = 0; iRow < SIZE; iRow++){
        printf("%2d", iRow + 1);
        for (int iCol = 0; iCol < SIZE; iCol++){
            printf(" %c", board[iRow][iCol]);
        }
        printf("\n");
    }
    printf("        FIRE AWAY!\n");
    printf("(enter a spot in the grid like A1) ");
}

void showScore(int movesMade){
    int score = 100 - (movesMade - 31);
    printf("CONGRATULATIONS!!!! It took you %d moves to hit 31 spaces. Your score is: %d \n", movesMade, score);
}

int checkBoard(char board[][SIZE]){
    for(int indRow = 0; indRow < SIZE; indRow++){
        for(int indCol = 0; indCol < SIZE; indCol++){
            if (board[indRow][indCol] == 'S'){
                return 0;
            }
        }
    }
    return 1;
}

void resetBoard(char board[][SIZE]){
    for(int indRow = 0; indRow < SIZE; indRow++){
        for(int indCol = 0; indCol < SIZE; indCol++){
            board[indRow][indCol] = ' ';
        } 
    }
}

