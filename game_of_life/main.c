
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "gameoflife.h"

int main(void)
{
    // re-seed random number generator
    srand((unsigned)time(NULL));

    GameArea *a = createGameArea(50,20);
    initGameArea(a, 300);

    // how many iterations we want
    int rounds = 300;

    // loop iterations, cancel with ctrl-c
    for(int i=0; i<rounds; i++) {
        printf("\nGeneration: %d\n", i+1);
        printGameArea(a);
        // slow down iterations
        nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);
        gameTick(a);
    }
    releaseGameArea(a);
    return 0;
}
