/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */
 //Testing smithy

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <string.h>
 #include <stdio.h>
 #include <assert.h>
 #include "rngs.h"
 #include <stdlib.h>

int testSmithy(struct gameState *, int );

int main(){
    int seed = 1000;
    int numPlayer = 3;
    int r, result;
    int handPos = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("------Smithy Card Test------\n");
    result = testSmithy(&G, handPos);
    if(result == 0)
        printf("Smithy: PASS test\n");
    else
        printf("Smithy: FAIL test\n");
    return 0;
}

int testSmithy(struct gameState* before, int handPos){
    int beforecount, beforecoins, after, aftercoins;
    int currentPlayer = whoseTurn(before);
    int flag = 0;
    //Draw 3 cards
    //costs 4 coins
    beforecount = before->handCount[currentPlayer];
    printf("    Card count in hand before: %d\n", beforecount);
    beforecoins = before->coins;
    printf("    Coin count before: %d\n", beforecoins);
    after = cardEffect(smithy, 0, 0, 0, before, handPos, 0); // run cardEffect
    printf("    Card count after: %d\n", before->handCount[currentPlayer]);
    printf("        Expected: %d\n", beforecount + 2);
    if (before->handCount[currentPlayer] == beforecount +2){
        printf("        SUCCESS: card count is correct\n");
    }
    else{
        printf("        FAIL: card count is not correct\n");
        flag = 1;
    }

    printf("    Coin count after: %d\n", before->coins);
    printf("        Expected: %d\n", beforecoins - 4);
    if (before->coins == 4){
        printf("        SUCCESS: coin cost is correct\n");
    }
    else{
        printf("        FAIL: coin cost is not correct\n");
        flag = 1;
    }

    int costSmithy = getCost(smithy);
    printf("    Cost of Card\n");
    printf("        Actual cost: %d\n", costSmithy);
    printf("        Expected cost: 4\n");
    if(costSmithy == 4){
        printf("            PASS: cost of Smithy card is correct\n");
    }
    else{
        printf("            FAIL: cost of Smithy card is incorrect\n");
        flag = 1;
    }
    return flag;
}



/*

case smithy:
  //+3 Cards
  for (i = 0; i < 3; i++)
{
  drawCard(currentPlayer, state);
}

  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
*/
