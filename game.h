#ifndef Game_H_INCLUDED
#define Game_H_INCLUDED

#define HOME 1
#define GAME 2
#define WIN 3
#define LOSE 4

#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

#define ZERO 2
#define TRUE 1
#define FALSE 0
#include <SDL.h>
typedef struct{
    int size, **board, moves, score;
}Game;

int setup(Game* matrix, int loadTab);

void displayMatrix(Game* matrix);

int  changePosition(Game* matrix, int side, SDL_Surface* screen, SDL_Surface* images[12], SDL_Window* window);

void antiRotate(Game* matrix, int ang);

void rotateMatrix(Game* matrix, int ang);

int displayPieces(Game* matrix);

int add_new_number(void);

int checkPiece(Game* matrix);

int checkMovement(Game* matrix);

bool loadImages(Game* matrix,SDL_Surface* images[12]);

void refreshScreen(SDL_Surface *screen, SDL_Window *window);

void save(Game* matrix);

void reGame(Game* matrix);

void createParts(SDL_Surface* images[12]);

void changeScreen(SDL_Surface* screen, SDL_Surface* screen_after);

void zeroTab(Game* matrix);


#endif // Game_H_INCLUDED
