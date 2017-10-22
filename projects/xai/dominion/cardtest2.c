#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int testAdventurer(struct gameState *, int); //function declaration

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

    printf("------Adventurer Card Test------\n");
    result = testAdventurer(&G, handPos);
    if(result == 0)
        printf("Adventurer: PASS tests\n");
    else
        printf("Adventurer: FAIL test\n");
    return 0;
}

int testAdventurer(struct gameState* before, int handPos){
    int currentPlayer = whoseTurn(before);
    int beforeAdventurerCardCount = before->handCount[currentPlayer];
    int i, x, after;
    int flag = 0;
    int beforeAdventurerCoinCount = 0;
    for(i = 0; i < beforeAdventurerCardCount; i++){
        x = before->hand[currentPlayer][i];
        if (x == copper || x == silver || x == gold){
            beforeAdventurerCoinCount++;
        }
    }
    after = cardEffect(adventurer, 0, 0, 0, before, handPos, 0); // run cardEffect
    discardCard(handPos, currentPlayer, before, 0);
    printf("    Card count in hand before: %d\n", beforeAdventurerCardCount);
    printf("    Card count in hand after: %d\n", before->handCount[currentPlayer]);
    printf("    Expected count: %d\n", beforeAdventurerCardCount + 1);
    if((beforeAdventurerCardCount + 1)== before->handCount[currentPlayer]){
        printf("        SUCCESS: card count is correct\n");
    }
    else{
        printf("        FAIL: card count is incorrect\n");
        flag = 1;
    }
    int j;
    int afterAdventurerCoinCount = 0;
    printf("    Treasure count before Adventurer:%d", beforeAdventurerCoinCount);
    for(j = 0; j < before->handCount[currentPlayer]; j++){
        x = before->hand[currentPlayer][i];
        if (x == copper || x == silver || x == gold){
            afterAdventurerCoinCount++;
        }
    }
    printf("    Treasure count before Adventurer: %d\n", beforeAdventurerCoinCount);
    printf("    Treasure count after Adventurer: %d\n", afterAdventurerCoinCount);
    printf("    Expected count: %d\n", beforeAdventurerCoinCount + 2);
    if((beforeAdventurerCoinCount + 2)== afterAdventurerCoinCount){
        printf("        SUCCESS: treasure count is correct\n");
    }
    else{
        printf("        FAIL: treasure count is incorrect\n");
        flag = 1;
    }

    int costAdventurer = getCost(adventurer);
    printf("    Cost of Card\n");
    printf("        Actual cost: %d\n", costAdventurer);
    printf("        Expected cost: 6\n");
    if(costAdventurer == 6){
        printf("            PASS: cost of Adventurer card is correct\n");
    }
    else{
        printf("            FAIL: cost of Adventurer card is incorrect\n");
        flag = 1;
    }

    return flag;
}
/*
case adventurer:
  while(drawntreasure<2){
if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
  shuffle(currentPlayer, state);
}
drawCard(currentPlayer, state);
cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
  drawntreasure++;
else{
  temphand[z]=cardDrawn;
  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
  z++;
}
  }
  while(z-1>=0){
state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
z=z-1;
  }
  return 0;
*/
