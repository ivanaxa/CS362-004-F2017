/* -----------------------------------------------------------------------
 * Testing isGameOver()
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <string.h>
 #include <stdio.h>
 #include <assert.h>
 #include "rngs.h"

 // set NOISY_TEST to 0 to remove printfs from output
 #define NOISY_TEST 1

 int main() {
     int i;
     int seed = 1000;
     int numPlayer = 2;
     int maxBonus = 10;
     int p, r, handCount;
     int bonus;
     int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
     struct gameState G;
     int maxHandCount = 5;
     // arrays of all coppers, silvers, and golds
     int coppers[MAX_HAND];
     int silvers[MAX_HAND];
     int golds[MAX_HAND];
     for (i = 0; i < MAX_HAND; i++)
     {
         coppers[i] = copper;
         silvers[i] = silver;
         golds[i] = gold;
     }

    int newGame;
    int result;

    printf ("------TESTING isGameOver():------\n");

    //testing a new initialized game
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    newGame = initializeGame(numPlayer, k, seed, &G); //initialize a new game
    result = isGameOver(&G);
    if (result == 0){
        printf("isGameOver(): PASS when game is new\n");
    }
    else{
        printf("isGameOver(): FAILED when game was new\n");
        printf("    expected a PASS(return value 0) when a new game is initialized\n");
    }

    //testing if Province cards are 0 (meaning the end of the game)
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    newGame = initializeGame(numPlayer, k, seed, &G); //initialize a new game
    G.supplyCount[province] = 0;
    result = isGameOver(&G);
    if(result == 1){
        printf("isGameOver(): PASS when there are 0 province cards left\n");
    }
    else{
        printf("isGameOver(): FAILED when there are 0 province cards left\n");
        printf("    expected a PASS(return value 1) when there are 0 province cards\n");
    }

    //testing if Province cards are 1 (meaning the game is not over)
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    newGame = initializeGame(numPlayer, k, seed, &G); //initialize a new game
    G.supplyCount[province] = 0;
    result = isGameOver(&G);
    if(result == 0){
        printf("isGameOver(): PASS when there are 1 province cards left\n");
    }
    else{
        printf("isGameOver(): FAILED when there are 1 province cards left\n");
        printf("    expected a PASS(return value 0) when there are 1 province cards\n");
    }

    //testing 1 Province card and 1 empty supply card
    G.supplyCount[adventurer] = 0;
    result = isGameOver(&G);
    if(result == 0){
        printf("isGameOver(): PASS when there are 1 province cards left and 1 empty supply (adventurer)\n");
    }
    else{
        printf("isGameOver(): FAILED when there are 1 province cards left and 1 empty supply (adventurer)\n");
        printf("    expected a PASS(return value 0) when there are 1 province cards and 1 empty supply (adventurer)\n");
    }

    //testing 1 Proince card and 3 empty supply cards
    G.supplyCount[council_room] = 0;
    G.supplyCount[feast] = 0;
    result = isGameOver(&G);
    if(result == 1){
        printf("isGameOver(): PASS when there are 1 province cards left and 3 empty supply cards\n");
    }
    else{
        printf("isGameOver(): FAILED when there are 1 province cards left and 3 empty supply cards\n");
        printf("    expected a PASS(return value 1) when there are 1 province cards left and 3 empty supply cards\n");
    }
    return 0;
 }