/* -----------------------------------------------------------------------
 * Testing shuffle()
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */


 #include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

 int main() {
     int i;
     int seed = 1000;
     int numPlayer = 2;
     int maxBonus = 10;
     int p = 2;
     int r, handCount;
     int bonus;
     int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
     struct gameState G, G2;
     int maxHandCount = 5;
     int newGame;
     int result;

    printf ("------TESTING shuffle():------\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    newGame = initializeGame(numPlayer, k, seed, &G);//initialize a new game at G
    //copy the same to G2 state
    memcpy(&G2, &G, sizeof(struct gameState));

    int before = G2.deckCount[p];
    result = shuffle(0, &G); //running shuffle on G
    int after = G.deckCount[p];

    if (before == after){
        printf("shuffle(): PASS\n");
        printf("    the number of cards is the same before and after\n");
    }
    else{
        printf("shuffle(): Failed\n");
        printf("    the number of cards before and after the shuffle are not the same\n");
    }
    return 0;
 }

 //shuffle() function
 //we want to check if the number of cards is the same
 /*
 int shuffle(int player, struct gameState *state) {


   int newDeck[MAX_DECK];
   int newDeckPos = 0;
   int card;
   int i;

   if (state->deckCount[player] < 1)
     return -1;
   qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare);
   /* SORT CARDS IN DECK TO ENSURE DETERMINISM! */
/*
   while (state->deckCount[player] > 0) {
     card = floor(Random() * state->deckCount[player]);
     newDeck[newDeckPos] = state->deck[player][card];
     newDeckPos++;
     for (i = card; i < state->deckCount[player]-1; i++) {
       state->deck[player][i] = state->deck[player][i+1];
     }
     state->deckCount[player]--;
   }
   for (i = 0; i < newDeckPos; i++) {
     state->deck[player][i] = newDeck[i];
     state->deckCount[player]++;
   }

   return 0;
 }
*/
