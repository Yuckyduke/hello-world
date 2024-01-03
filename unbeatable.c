#include <stdio.h>
#include <stdbool.h>
int minimax(char gameBoard[][3], int depth);
int checkDiagonals(char gameBoard[][3]);
bool moveLeft(char gameBoard[][3]);
int playGame(void);
int getNextMove(char gameBoard[][3], int depth);
int checkBoard(char gameBoard[][3]);
int playGame(void);
int bestMove(char gameBoard[][3], int depth);
int printBoard(char gameBoard[][3], int m);

// This enum ended up being kind of pointless, but I kept it encase want to
// use it to encode the board
enum BoardValue { none = 0, x = 1, o = -1 };
enum BoardValue getValue(char character);
// maybe gameBoard could be struct that takes in Coordinate?
struct Coordinate {
    int x, y;
};

// The two diagonals on the board we need to check
struct Coordinate firstDiagonal[3] = {{0,0}, {1,1}, {2,2}};
struct Coordinate secondDiagonal[3] = {{0,2}, {1,1}, {2,0}};

int main(void){
    playGame();
    return 0;
}

// Just changed some formatting here so easier to visualize board
int playGame(void) {
    int i = 0;
    char gameBoard[][3] = {
        {'#', '#', '#'},
        {'#', '#', '#'},
        {'#', '#', '#'}
    };
    printBoard(gameBoard, 3);
    while (checkBoard(gameBoard) == 0 && moveLeft(gameBoard) == true && i < 9) {
        getNextMove(gameBoard, i);
        printBoard(gameBoard, 3);
        printf("i: %d \n", i);
        i++;
    }
    return 0;
}

int printBoard(char gameBoard[][3],int m){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < 3; j++){
            printf("%c ", gameBoard[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    return 0;
}


// initialize BoardValue given a character
enum BoardValue getValue(char character) {
    if (character == 'X') {
        return x;
    } else if (character == 'O') {
        return o;
    }
    return none;
}


// sum the diagonals, if all x's or all o's return 10/-10 (respectively)
int checkDiagonals(char gameBoard[][3]) {
    int firstDiagValue = 0;
    int secondDiagValue = 0;
    for (int i = 0; i < 3; i++) {
        firstDiagValue += getValue(gameBoard[firstDiagonal[i].x][firstDiagonal[i].y]);
        secondDiagValue += getValue(gameBoard[secondDiagonal[i].x][secondDiagonal[i].y]);
    }
    if (firstDiagValue == 3 || secondDiagValue == 3) {
        return 10;
    }
    if (firstDiagValue == -3 || secondDiagValue == -3) {
        return -10;
    }
    return 0;
}

// renamed because it seemed like this function gets the next move
// not 100% though
int getNextMove(char gameBoard[][3], int depth) {
    int n, m;
    if (depth % 2  == 0) {
        printf("Row: ");
        scanf(" %d", &n);
        printf("\nColumn: ");
        scanf(" %d", &m);
        if (gameBoard[n][m] == '#'){
        gameBoard[n][m] = 'X';
        return 0;}
        printf("Must move into an empty space \n");
        move(gameBoard, depth);
        return 0;
    }
        gameBoard[n][m] = 'X';
        return 0;
    } else {
        n = bestMove(gameBoard, depth);
        printf("%d \n", n);
        gameBoard[n/10][n%10] = 'O';
        return 0;
    }
}

int bestMove(char gameBoard[][3], int depth) {
    int row = 0, column = 0;
    int bestVal = 1000;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (gameBoard[i][j] == '#'){
                gameBoard[i][j] = 'O';
                int moveVal = minimax(gameBoard, 0);
                gameBoard[i][j] = '#';
                if (moveVal < bestVal){
                    bestVal = moveVal;
                    row = i;
                    column = j;
                }
            }
        }
    }
    return row*10 + column;
}

// Instead of the if statements (we still have some obvi) I tried to make
// a way to look through the whole board and return your -10/0/10 value
int checkBoard(char gameBoard[][3]) {
    for (int i = 0; i < 3; i++) {
        int horizontalScore = 0;
        int verticalScore = 0;
        for (int j = 0; j < 3; j++) {
            horizontalScore += getValue(gameBoard[i][j]);
            verticalScore += getValue(gameBoard[j][i]);
        }
        if (verticalScore == -3 || horizontalScore == -3) {
            return -10;
        }
        if (verticalScore == 3 || horizontalScore == 3) {
            return 10;
        }
    }
    return checkDiagonals(gameBoard);
}

bool moveLeft(char gameBoard[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j<3; j++) {
            if (gameBoard[i][j] == '#') {
                return true;
            }
        }
    }
    return false;
}

int minimax(char gameBoard[][3], int depth){
    int score = checkBoard(gameBoard);
    if (score == 10){
        return score - depth;
    }
    if (score == -10) {
        return score + depth;
    }
    if (moveLeft(gameBoard) == true){
        if (depth % 2 == 0){
            //maximizer
            int best = -1000;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if (gameBoard[i][j] == '#'){
                        gameBoard[i][j] = 'X';
                        int temp = minimax(gameBoard, depth + 1);
                        if (temp > best){
                            best = temp;}
                        gameBoard[i][j] = '#';
                    }
                }
            }
            return best;
        }
        else {
            //minimizer
            int best = 1000;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if (gameBoard[i][j] == '#'){
                        gameBoard[i][j] = 'O';
                        int temp = minimax(gameBoard, depth + 1);
                        if (temp < best){
                            best = temp;}
                        gameBoard[i][j] = '#';
                    }
                }
            }
            return best;
        }
    } else {
        return 0;
    }
}

