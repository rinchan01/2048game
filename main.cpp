#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_image.h>
#include "game.h"
#include <iostream>
#include <ctime>
using namespace std;

const int SCREEN_WIDTH = 616;
const int SCREEN_HEIGHT = 616;

struct matrix {
        int  x;
        int  y;
        SDL_Surface *img;
}board[4][4];

/****************************
    i,y -> rows
    j,x -> columns
****************************/
int SDL_Init(Uint32 flags);
int choose_random_num(){
    int num;
    num = rand() % 4;
    return num;
}
void reGame(Game* matrix){
    FILE* flie_save;
    int i, j;

    flie_save = fopen("GameSave.txt","r");
    if (flie_save == NULL){
        cout << "Error opening file!" << endl;
        exit(0);
    } else {
        cout << "Opening..." << endl;
        for(i = 0; i < 4; i++){
          for(j = 0; j < 4; j++){
            if(!fscanf(flie_save,"%d", &matrix->board[i][j])){
              cout << "Error reading input " << i << " " << j << " from the board" << endl;
               break;
            }
            else {
                cout << i << " " << j << " " << " " << matrix->board[i][j];
            }
          }
        }
        fscanf(flie_save,"%d",&matrix->moves);//Regame
        cout << "Moves: " << matrix->moves << endl;

    }
    fclose(flie_save);
}

/*********************************************************
    Save game
*********************************************************/
void save(Game* matrix){

    FILE *flie_save;
    int i=0,j=0;

    flie_save = fopen("GameSave.txt","w");
    if (flie_save == NULL){
        cout << "Error opening file save" << endl;
        exit(0);
    } else {
        cout << "Saving..." << endl;
        for (i=0; i<4; i++){
            for(j=0;j<4;j++){
                fprintf(flie_save, "%d\n", matrix->board[i][j]);
            }
        }
    }
    fprintf(flie_save, "%d\n", matrix->moves);

    cout << "moves: " << matrix->moves << endl;

    fclose(flie_save);
}
/*************************************
    reset matrix/ create new matrix
*************************************/
void zeroTab(Game* matrix){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            matrix->board[i][j] = 0;
        }
    }
    matrix->moves = 0;

}

void changeScreen(SDL_Surface* screen, SDL_Surface* after_screen){
    SDL_BlitSurface(screen, NULL, after_screen, NULL);

}

int setup(Game* matrix, int loadTab){
    int i;
    matrix->size = 4;
    matrix->moves =0;
    //Create matrix columns
    matrix->board = (int**) malloc(matrix->size * sizeof(int*));

    if(matrix->board == NULL){
        return -1;
    }

    for(i=0; i<matrix->size; i++){
            //Fill with 0
        matrix->board[i] = (int*) calloc(matrix->size, sizeof(int*));

        if(matrix->board[i] == NULL){
            return -1;
        }
    }
    int line_1, col_1, line_2, col_2;
    line_1 = choose_random_num();
    col_1 = choose_random_num();
    col_2 = choose_random_num();
    line_2 = choose_random_num();
    matrix->board[line_1][col_1] = matrix->board[line_2][col_2] = 2;
    return 0;
}

void createParts(SDL_Surface* images[12]) {
    int i, j;
    for (i=0; i<4; i++){
        for (j=0;j<4; j++){
            board[i][j].x = i*130 + i*30;
            board[i][j].y = j*130 + j*30;
        }
    }
    images[0] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/0.bmp");
    images[1] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/1.bmp");
    images[2] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/2.bmp");
    images[3] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/3.bmp");
    images[4] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/4.bmp");
    images[5] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/5.bmp");
    images[6] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/6.bmp");
    images[7] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/7.bmp");
    images[8] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/8.bmp");
    images[9] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/9.bmp");
    images[10] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/10.bmp");
    images[11] = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/11.bmp");

}

void displayMatrix(Game* matrix){
    int i,j;
    system("cls");
    for(i=0; i < matrix->size; i++){
        for(j=0; j < matrix->size; j++){
            cout << " " << matrix->board[i][j] << " " << endl;
        }
    cout << endl;
    }
}


bool loadImages(Game* matrix, SDL_Surface* images[12]){
    int i,j;
    bool success = true;

    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            switch (matrix->board[i][j]){
                case 0:
                    board[i][j].img = images[0];
                break;

                case 2:
                    board[i][j].img = images[1];
                break;

                case 4:
                    board[i][j].img = images[2];
                break;

                case 8:
                    board[i][j].img = images[3];
                break;

                case 16:
                    board[i][j].img = images[4];
                break;

                case 32:
                    board[i][j].img = images[5];
                break;

                case 64:
                    board[i][j].img = images[6];
                break;

                case 128:
                    board[i][j].img = images[7];
                break;

                case 256:
                    board[i][j].img =images[8];
                break;

                case 512:
                    board[i][j].img = images[9];
                break;

                case 1024:
                    board[i][j].img = images[10];
                break;

                case 2048:
                    board[i][j].img = images[11];
                break;
            }

            if (board[i][j].img == NULL && matrix->board[i][j] != 0){
                success = false;
                cout << "Coludn't load parts" << endl << SDL_GetError() << endl;
            }
        }
    }
    return success;
}

int add_new_number(void){
    int new_num;
    new_num = rand()%10;
    if(new_num<4){
        return new_num;
    }
    else{
        return add_new_number();
    }
}
int displayPieces(Game* matrix){
       int A, i, X, Y;
       A = matrix->size*matrix->size;
       for(i=1; i<=A; i++){
            X = add_new_number();
            Y = add_new_number();
            if(matrix->board[Y][X] == 0){
                matrix->board[Y][X] = 2;
                break;
            }
       }
}
void refreshScreen(SDL_Surface *screen, SDL_Window *window){
    int i, j;

    SDL_Surface* GameBg = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/background.bmp"); // Load background
    SDL_BlitSurface(GameBg, NULL, screen, NULL);

    SDL_FreeSurface(GameBg);

    SDL_Rect position;
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            position.x = board[j][i].x;
            position.y = board[j][i].y;

            SDL_BlitSurface(board[i][j].img, NULL, screen, &position);

        }
    }
    SDL_UpdateWindowSurface(window);
}
/********************************************
    check if there is 2048
*********************************************/
int checkPiece(Game* matrix){

    int i, j;
    for(i=0; i<matrix->size; i++){
        for(j=0; j<matrix->size; j++){
            if(matrix->board[i][j] == 2048){
                return 0;
            }
        }
    }
    return -1;
}


/*****************************************************
check if movements avail
return -1 if it has any 0
return -2 when it has movement
return -3 when there is no movement avail
*****************************************************/
int checkMovement(Game* matrix){
    int i, j , m;
    for(i=0; i<matrix->size; i++){
        for(j=0; j<matrix->size; j++){
            if(matrix->board[i][j] == 0){
                return -1;
            }
        }
    }
    for(i=0; i<matrix->size; i++){

        for(j=0; j<matrix->size; j++){
            if(i!=3){
                if( j!= 3){
                    if(matrix->board[i][j] == matrix->board[i][j+1] || matrix->board[i][j] == matrix->board[i+1][j]){
                        return -2;
                    }
                }else{
                    if(matrix->board[i][j] == matrix->board[i+1][j]){
                        return -2;
                    }
                }
            }else{
                if(j != 3){
                    if(matrix->board[i][j] == matrix->board[i][j+1]){
                        return -2;

                    }
                }
            }
        }
    }
    return -3;

}
//change position
int up(Game* matrix, SDL_Surface* screen, SDL_Surface* images[12], SDL_Window* window){
    int change = 0, next_line, next_column, x;
    for (int j=0; j<4; j++){
        next_line = 0;
        next_column = j;
        for (int i=1; i<4; i++){
            if (matrix->board[i][j]!=0){
                if (matrix->board[i-1][j]==0 || matrix->board[i-1][j]==matrix->board[i][j]){
                    if (matrix->board[next_line][next_column]==matrix->board[i][j]){
                        matrix->board[next_line][next_column] += matrix->board[i][j];
                        matrix->board[i][j] = 0;
                        change = 1;
                    }
                    else {
                        if (matrix->board[next_line][next_column]==0){
                            matrix->board[next_line][next_column] = matrix->board[i][j];
                            matrix->board[i][j] = 0;
                            change = 1;
                        } else {
                            next_line++;
                            matrix->board[next_line][next_column] = matrix->board[i][j];
                            matrix->board[i][j] = 0;
                            change = 1;
                        }
                    }
                }
                else {
                next_line++;
                }
            }
        }
    }
    if(change != 0){

        displayPieces(matrix);
        displayMatrix(matrix);

        if (loadImages(matrix, images)){
                //update screen
            refreshScreen(screen, window);
        }
        else {
            cout << "Error loading images" << endl;
        }

        if(checkPiece(matrix) == -1){
            x = checkMovement(matrix);
           return x;
        }
        else{
            return 0;
        }
    }
    else{
        x = checkMovement(matrix);
        return x;
    }
    return -3;
}
int down(Game* matrix, SDL_Surface* screen, SDL_Surface* images[12], SDL_Window* window){
    int change = 0, next_line, next_column, x;
    for (int j=0; j<4; j++){
        next_line = 3;
        next_column = j;
        for (int i=2; i>=0; i--){
            if (matrix->board[i][j]!=0){
                if (matrix->board[i+1][j]==0 || matrix->board[i+1][j]==matrix->board[i][j]){
                    if (matrix->board[next_line][next_column]==matrix->board[i][j]){
                        matrix->board[next_line][next_column] += matrix->board[i][j];
                        matrix->board[i][j] = 0;
                        change = 1;
                    }
                    else {
                        if (matrix->board[next_line][next_column]==0){
                            matrix->board[next_line][next_column] = matrix->board[i][j];
                            matrix->board[i][j] = 0;
                            change = 1;
                        } else {
                            next_line--;
                            matrix->board[next_line][next_column] = matrix->board[i][j];
                            matrix->board[i][j] = 0;
                            change = 1;
                        }
                    }
                }
                else {
                next_line--;
                    }
                }
            }
        }
    if(change != 0){

        displayPieces(matrix);
        displayMatrix(matrix);

        if (loadImages(matrix, images)){
                //update screen
            refreshScreen(screen, window);
        }
        else {
            cout << "Error loading images" << endl;
        }

        if(checkPiece(matrix) == -1){
            x = checkMovement(matrix);
           return x;
        }
        else{
            return 0;
        }
    }
    else{
        x = checkMovement(matrix);
        return x;
    }
    return -3;
}
int left(Game* matrix, SDL_Surface* screen, SDL_Surface* images[12], SDL_Window* window){
    int change = 0, next_line, next_column, x;
    for (int i=0; i<4; i++){
        next_line = i;
        next_column = 0;
        for (int j=1; j<=3; j++){
            if (matrix->board[i][j]!=0){
                if (matrix->board[i][j-1]==0 || matrix->board[i][j-1]==matrix->board[i][j]){
                    if (matrix->board[next_line][next_column]==matrix->board[i][j]){
                        matrix->board[next_line][next_column] += matrix->board[i][j];
                        matrix->board[i][j] = 0;
                        change = 1;
                    }
                    else {
                        if (matrix->board[next_line][next_column]==0){
                            matrix->board[next_line][next_column] = matrix->board[i][j];
                            matrix->board[i][j] = 0;
                            change = 1;
                        } else {
                            next_column++;
                            matrix->board[next_line][next_column] = matrix->board[i][j];
                            matrix->board[i][j] = 0;
                            change = 1;
                        }
                    }
                }
                else {
                next_column++;
                }
            }
        }
    }
    if(change != 0){

        displayPieces(matrix);
        displayMatrix(matrix);

        if (loadImages(matrix, images)){
                //update screen
            refreshScreen(screen, window);
        }
        else {
            cout << "Error loading images" << endl;
        }

        if(checkPiece(matrix) == -1){
            x = checkMovement(matrix);
           return x;
        }
        else{
            return 0;
        }
    }
    else{
        x = checkMovement(matrix);
        return x;
    }
    return -3;
}
int right(Game* matrix, SDL_Surface* screen, SDL_Surface* images[12], SDL_Window* window){
    int change = 0, next_line, next_column, x;
    for (int i=0; i<4; i++){
        next_line = i;
        next_column = 3;
        for (int j=2; j>=0; j--){
            if (matrix->board[i][j]!=0){
                if (matrix->board[i][j+1]==0 || matrix->board[i][j+1]==matrix->board[i][j]){
                    if (matrix->board[next_line][next_column]==matrix->board[i][j]){
                        matrix->board[next_line][next_column] += matrix->board[i][j];
                        matrix->board[i][j] = 0;
                        change = 1;
                    }
                    else {
                        if (matrix->board[next_line][next_column]==0){
                            matrix->board[next_line][next_column] = matrix->board[i][j];
                            matrix->board[i][j] = 0;
                            change = 1;
                        } else {
                            next_column--;
                            matrix->board[next_line][next_column] = matrix->board[i][j];
                            matrix->board[i][j] = 0;
                            change = 1;
                        }
                    }
                }
                else {
                next_column--;
                }
            }
        }
    }
    if(change != 0){

        displayPieces(matrix);
        displayMatrix(matrix);

        if (loadImages(matrix, images)){
                //update screen
            refreshScreen(screen, window);
        }
        else {
            cout << "Error loading images" << endl;
        }

        if(checkPiece(matrix) == -1){
            x = checkMovement(matrix);
           return x;
        }
        else{
            return 0;
        }
    }
    else{
        x = checkMovement(matrix);
        return x;
    }
    return -3;
}



int main(int argc, char **argv){
    Game matrix;
    //Declare variables
    int change = FALSE ,running = TRUE, game = FALSE, startTab = FALSE, loadTab = FALSE, win = FALSE, currentScreen = HOME;
    srand(time(NULL));
    //Declare SDL variables
    SDL_Surface *homeBg;
    SDL_Surface *GameBg;
    SDL_Surface *winBg;
    SDL_Surface *loseBg;
    SDL_Surface *screen;
    SDL_Surface *images[12];
    SDL_Point mousePos;
    SDL_Window *window;
    SDL_Renderer *renderer;
    //Create rectangles
    SDL_Rect start;
        start.x = 52;
        start.y = 273;
        start.h = 67;
        start.w = 515;
    SDL_Rect resume;
        resume.x = 49;
        resume.y = 357;
        resume.h = 56;
        resume.w = 523;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Can't initial video %s", SDL_GetError());
        return 1;
    }

    //Window creation
    window = SDL_CreateWindow("2048 simple game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screen = SDL_GetWindowSurface(window);
    //Load Backgrounds
    homeBg = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/home.bmp");
    GameBg = SDL_LoadBMP("C:/Users/RIN/Documents/2048console/background_game.bmp");
    winBg = SDL_LoadBMP("win.bmp");
    loseBg = SDL_LoadBMP("lose.bmp");
    changeScreen(homeBg, screen);


    //Game loop
    while(running == TRUE)
    {
        //Event Dectection
        SDL_Event event;
        while(SDL_PollEvent(&event) && game == 0 && win == 0){

            if(currentScreen != HOME){
                changeScreen(homeBg, screen);
            }
            switch(event.type)
            {
            case SDL_QUIT: //Close the game
                running = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(
                    // Positions
                    &mousePos.x,
                    &mousePos.y
                );
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(SDL_EnclosePoints(&mousePos, 1, &start, NULL)){
                    changeScreen(GameBg, screen);
                    currentScreen = 2;
                    game =! 0;
                    //Starts Game
                    }
                    else if(SDL_EnclosePoints(&mousePos, 1, &resume, NULL)){
                        SDL_Log("resume");
                        loadTab = 1;
                        game =! 0;
                    }
                }
                break;
            }
        }
        SDL_UpdateWindowSurface(window);

        if(game == 1){
            //Execute the game
            SDL_Delay(100);
            //Delay to process game
            if(startTab == FALSE){
                    //Check if it's already initialized
                    if(setup(&matrix, loadTab) == -1){
                        cout << "Error creating matrix->board" << endl;
                        return 0;
                    }
                    if (loadTab == 1){
                        changeScreen(GameBg,screen);
                        currentScreen = 2;
                        reGame(&matrix);
                    }
                    else{
                    displayPieces(&matrix);
                //Show first piece
                    }
                    createParts(images);
                    displayMatrix(&matrix);
                    startTab = TRUE;
                    if (loadImages(&matrix, images)){
                    refreshScreen(screen, window);
                    } else {
                    cout << ("Error loading images");
                    }
                }

            else if(startTab == 2){
                change = FALSE;
                createParts(images);
                //Create board
                displayMatrix(&matrix);
                //Display matrix
                startTab = TRUE;
                if (loadTab == 1){
                    changeScreen(GameBg,screen);
                    currentScreen = 2;
                    reGame(&matrix);
                }else{
                    displayPieces(&matrix);
                }
                if (loadImages(&matrix, images)){
                    refreshScreen(screen, window);
                } else {
                    cout << ("Error loading images");
                }
            }
            while (SDL_PollEvent(&event) != 0){
                if (event.type == SDL_QUIT){
                    save(&matrix);
                    running = 0;
                }
                else if (event.type == SDL_KEYDOWN){
                    //Select surfaces based on key press
						switch (event.key.keysym.sym)
						{
							case SDLK_UP:
                                change = up(&matrix,screen, images, window);
                                SDL_Log("%d", change);
                                break;


							case SDLK_DOWN:
                                change = down(&matrix, screen, images, window);
                                SDL_Log("%d", change);

                                break;

							case SDLK_LEFT:
                                change = left(&matrix, screen, images, window);
                                SDL_Log("%d", change);
                                break;

							case SDLK_RIGHT:
                                change = right(&matrix, screen, images, window);
                                SDL_Log("%d", change);

                                break;
						}
                }
            }
            if(change == FALSE && matrix.moves > 0){
                SDL_Delay(600);
                win = TRUE;
                game = FALSE;
                changeScreen(winBg, screen);
                currentScreen = WIN;
                cout << "End of moves " << matrix.moves << endl;


            }
            else if(change == -3){
                changeScreen(loseBg, screen);
                game = FALSE;
                win = FALSE;
                currentScreen = 3;
                SDL_Delay(600);
                zeroTab(&matrix);
                startTab = ZERO;
                //indicates that in the next game you don't need to initialize the matrix but you need to put the pieces
                cout << "Cannot move!" << endl;

            }
        }

    }
    SDL_Quit();

    return 0;
}
