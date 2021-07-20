#include <stdio.h>
#include <stdlib.h>

#include "gameoflife.h"

GameArea *createGameArea(unsigned int x_size, unsigned int y_size)
{
    GameArea* gameArea = malloc(sizeof(GameArea));
    gameArea->cells = malloc(y_size * sizeof(CellStatus*));
    gameArea->x_size = x_size;
    gameArea->y_size = y_size;

    for(unsigned int i = 0; i < y_size; i++)
    {
        gameArea->cells[i] = malloc(x_size * sizeof(CellStatus));
        for(unsigned int j = 0; j < x_size; j++)
            gameArea->cells[i][j] = DEAD;
    }

    return gameArea;
}

void releaseGameArea(GameArea *a)
{
    unsigned int i = 0;
    while(i < a->y_size)
    {
        free(a->cells[i]);
        i++;
    }
    free(a->cells);
    free(a);
}

void initGameArea(GameArea *a, unsigned int n)
{
    for(unsigned int i = 0; i < n; i++)
    {
        int x = rand() % a->x_size;
        int y = rand() % a->y_size;
        while(a->cells[y][x] == ALIVE)
        {
            x = rand() % a->x_size;
            y = rand() % a->y_size;
        }
        a->cells[y][x] = ALIVE;
    }
}

void printGameArea(const GameArea *a)
{
    for(unsigned int i = 0; i < a->y_size; i++)
    {
        for(unsigned int j = 0; j < a->x_size; j++)
        {
            if(a->cells[i][j] == ALIVE)
                printf("■");
            else
                printf(" ");
        }
        printf("\n");
    }
}

unsigned int live_neighbours(const GameArea *a, unsigned int x, unsigned int y)
{
    int c = 0;

    int n[8][2] = {{1, -1}, {1, 0}, {1, 1}, {0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}};
    for(int i = 0; i < 8; i++)
    {
        if(0 <= ((int)y + n[i][0]) && ((int)y + n[i][0]) < (int)a->y_size && 0 <= ((int)x + n[i][1]) && ((int)x + n[i][1]) < (int)a->x_size)
            if(a->cells[(int)y + n[i][0]][(int)x + n[i][1]] == ALIVE)
                c++;
    }
    return c;
}

void gameTick(GameArea *a)
{
    GameArea* oldState = createGameArea(a->x_size, a->y_size);
    for(unsigned int i = 0; i < oldState->y_size; i++)
    {
        for(unsigned int j = 0; j < oldState->x_size; j++)
        {
            oldState->cells[i][j] = a->cells[i][j];
        }
    }

    for(unsigned int i = 0; i < oldState->y_size; i++)
    {
        for(unsigned int j = 0; j < oldState->x_size; j++)
        {
            if(live_neighbours(oldState, j, i) < 2 && oldState->cells[i][j] == ALIVE)
                a->cells[i][j] = DEAD;
            else if(live_neighbours(oldState, j, i) <= 3 && oldState->cells[i][j] == ALIVE)
                a->cells[i][j] = ALIVE;
            else if(live_neighbours(oldState, j, i) > 3 && oldState->cells[i][j] == ALIVE)
                a->cells[i][j] = DEAD;
            else if(live_neighbours(oldState, j, i) == 3 && oldState->cells[i][j] == DEAD)
                a->cells[i][j] = ALIVE;
        }
    }

    releaseGameArea(oldState);
}
