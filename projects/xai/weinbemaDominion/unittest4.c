/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
 //Added on version of the example given in class

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
    int p, handCount;
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

    printf ("------TESTING updateCoins():------\n");

    for (p = 0; p < numPlayer; p++){
        for (handCount = 1; handCount <= maxHandCount; handCount++){
            for (bonus = 0; bonus <= maxBonus; bonus++){
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
                if (G.coins == handCount * 1 + bonus){
                    printf("updateCoins() \n\tPASS: with all copper coins in hand\n");
                } // check if the number of coins is correct

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
                if (G.coins == handCount * 2 + bonus){
                    printf("updateCoins() \n\tPASS: with all silver coins in hand\n");
                } // check if the number of coins is correct

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
                if (G.coins == handCount * 3 + bonus){
                    printf("updateCoins() \n\tPASS: with all gold coins in hand\n");
                } // check if the number of coins is correct

                //testing a mix of coins now
                //4 copper and 1 gold
                int mixedCards[5]={copper, copper, copper, copper, gold};
                memcpy(G.hand[p], mixedCards, sizeof(int) * handCount);
                updateCoins(p, &G, 0);
                printf("G.coins = %d, expected = 7\n", G.coins);
                if(G.coins == 7){
                    printf("updateCoins() \n\tPASS: with 4 copper and 1 gold\n");
                }
                else{
                    printf("updateCoins() \n\tFAIL: with 4 copper and 1 gold\n");
                }
                //testing 1 copper, 1 silver, and 3 gold
                int mixedCards2[5]={copper, silver, gold, gold, gold};
                memcpy(G.hand[p], mixedCards2, sizeof(int) * handCount);
                updateCoins(p, &G, 0);
                printf("G.coins = %d, expected = 12\n", G.coins);
                if(G.coins == 12){
                    printf("updateCoins() \n\tPASS: with 1 copper, 1 silver and 3 gold\n");
                }
                else{
                    printf("updateCoins() \n\tFAIL: with 1 copper, 1 silver and 3 gold\n");
                }
                //printf("All tests passed!\n");

            }
        }
    }
    return 0;
}