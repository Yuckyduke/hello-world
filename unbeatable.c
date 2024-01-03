#include <stdio.h>
#include <stdbool.h>
int minimax(char gameBoard[][3], int depth);
bool moveLeft(char gameBoard[][3]);
int move(char gameBoard[][3], int mover);
int checkBoard(char gameBoard[][3]);
int playGame(void);
int bestMove(char gameBoard[][3], int depth);
int printBoard(char gameBoard[][3], int m);

int main(void){
    playGame();
    return 0;
}

int playGame(void){
    int i = 0;
    char gameBoard[][3] = {{'#', '#', '#'}, {'#', '#', '#'}, {'#', '#', '#'}};
    printBoard(gameBoard, 3);
    while (checkBoard(gameBoard) == 0 && moveLeft(gameBoard) == true && i < 9){
        move(gameBoard, i);
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

int move(char gameBoard[][3], int depth){
    int n, m;
    if (depth % 2  == 0){
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
    n = bestMove(gameBoard, depth);
    printf("%d \n", n);
    gameBoard[n/10][n%10] = 'O'; 
    return 0;
}
int bestMove(char gameBoard[][3], int depth){
    int r, c;
    int bestVal = 1000;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (gameBoard[i][j] == '#'){
                gameBoard[i][j] = 'O';
                int moveVal = minimax(gameBoard, 0);
                gameBoard[i][j] = '#';
                if (moveVal < bestVal){
                    bestVal = moveVal;
                    r = i;
                    c = j;
                }
            }
                
        }
    }
        return r*10 + c;
}

int checkBoard(char gameBoard[][3]){
    if (gameBoard[0][0] == 'O' && gameBoard[0][1] == 'O' && gameBoard[0][2] == 'O'){
        return -10;}
    if (gameBoard[0][0] == 'X' && gameBoard[0][1] == 'X' && gameBoard[0][2] == 'X'){
        return 10;}        
    if (gameBoard[1][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[1][2] == 'O'){
        return -10;}
    if (gameBoard[1][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[1][2] == 'X'){
        return 10;}
    if (gameBoard[2][0] == 'O' && gameBoard[2][1] == 'O' && gameBoard[2][2] == 'O'){
        return -10;}
    if (gameBoard[2][0] == 'X' && gameBoard[2][1] == 'X' && gameBoard[2][2] == 'X'){
        return 10;}
    if (gameBoard[0][0] == 'O' && gameBoard[1][0] == 'O' && gameBoard[2][0] == 'O'){
        return -10;}
    if (gameBoard[0][0] == 'X' && gameBoard[1][0] == 'X' && gameBoard[2][0] == 'X'){
        return 10;}
    if (gameBoard[0][1] == 'O' && gameBoard[1][1] == 'O' && gameBoard[2][1] == 'O'){
        return -10;}
    if (gameBoard[0][1] == 'X' && gameBoard[1][1] == 'X' && gameBoard[2][1] == 'X'){
        return 10;}
    if (gameBoard[0][2] == 'O' && gameBoard[1][2] == 'O' && gameBoard[2][2] == 'O'){
        return -10;}
    if(gameBoard[0][2] == 'X' && gameBoard[1][2] == 'X' && gameBoard[2][2] == 'X'){
        return 10;}
    if (gameBoard[0][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[2][2] == 'O'){ 
        return -10;}
    if (gameBoard[0][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[2][2] == 'X'){
        return 10;}
    if (gameBoard[2][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[0][2] == 'O') {
        return -10;}
    if (gameBoard[2][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[0][2] == 'X'){
        return 10;}
    return 0;
    }
bool moveLeft(char gameBoard[][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j<3; j++){
            if (gameBoard[i][j] == '#'){
                return true;}}}
    return false;}

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
    }
    else{
        return 0;
    }
}
