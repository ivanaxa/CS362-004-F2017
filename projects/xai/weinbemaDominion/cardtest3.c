#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int testVillage(struct gameState *, int); //declared fucntion

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
    result = testVillage(&G, handPos);
    printf("------Village Card Test------\n");
    if(result == 0){
        printf("Village: PASS tests\n");
    }
    else{
        printf("Village: FAIL test\n");
    }
    return 0;
}

//test for 1 more card after playing but 0 net cards since discard the village after
//test for 2 more actions
//test for cost of card

int testVillage(struct gameState *before, int handPos){
    //bool correctNumCards;
    int currentPlayer = whoseTurn(before);
    int result;
    int flag = 0;

    int beforeVillageActionCount = before->numActions;
    int beforeVillageCardCount = before->handCount[currentPlayer];
    int costVillage = getCost(village);

    result = cardEffect(village, 0, 0, 0, before, handPos, 0);

    int afterVillageActionCount = before->numActions;
    int afterVillageCardCount = before->handCount[currentPlayer];

    printf("    Cost of Card\n");
    printf("        Actual cost: %d\n", costVillage);
    printf("        Expected cost: 3\n");
    if(costVillage == 3){
        printf("            PASS: cost of village card is correct\n");
    }
    else{
        printf("            FAIL: cost of village card is incorrect\n");
        flag = 1;
    }

    printf("    Action Effect of Village\n");
    printf("        Actions before Village: %d\n", beforeVillageActionCount);
    printf("        Actions after Village: %d\n", afterVillageActionCount);
    printf("        Expected Actions after Village: %d\n", beforeVillageActionCount+1);
    if(afterVillageActionCount == (beforeVillageActionCount+1)){
        printf("            PASS: action effect of village card is correct\n");
    }
    else{
        printf("            FAIL: action effect of village card is incorrect\n");
        flag = 1;
    }

    printf("    Card Count Effect of Village\n");
    printf("        Card Count before Village: %d\n", beforeVillageCardCount);
    printf("        Card Count after Village: %d\n", afterVillageCardCount);
    printf("        Expected Card Count after Village: %d\n", beforeVillageCardCount);
    if(afterVillageCardCount == beforeVillageCardCount){
        printf("            PASS: card count effect of village card is correct\n");
    }
    else{
        printf("            FAIL: card count effect of village card is incorrect\n");
        flag = 1;
    }

    return flag;
}