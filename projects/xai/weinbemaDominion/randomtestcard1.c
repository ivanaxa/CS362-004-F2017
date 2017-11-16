#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//testing villager
/*
+1 card
+2 action
cost 3 coins
*/

#define TESTCARD "steward"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int x;
    for (x = 0; x < 500; x++){
    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = rand() % 1000 + 1;
    int numPlayers = rand() % 3 + 2; // 2,3,4 players
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("------Testing Card: %s------\n", TESTCARD);
    int flag = 0;

    //cost of card test
    int costSteward = getCost(steward);
    printf("    Cost of Card\n");
    printf("        Actual cost: %d\n", costSteward);
    printf("        Expected cost: 3\n");
    if(costSteward == 3){
        printf("            PASS: cost of village card is correct\n");
    }
    else{
        printf("            FAIL: cost of village card is incorrect\n");
        flag = 1;
    }

	// ----------- TEST 1: choice1 = 1 = +2 cards --------------
	printf("TEST 1: choice1 = 1 = +2 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 2;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

	if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded){
        printf("    PASS: Card Count is correct\n");
    }
    else{
        printf("    FAIL: Card Count is incorrect\n");
        flag = 1;
    }
	if(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards){
        printf("    PASS: Deck Count is correct\n");
    }
    else{
        printf("    FAIL: Deck Count is incorrect\n");
    }
	if(testG.coins == G.coins + xtraCoins){
        printf("    PASS: Coin count is correct\n");
    }
    else{
        printf("    FAIL: Coin count is incorrect\n");
    }

	// ----------- TEST 2: choice1 = 2 = +2 coins --------------
	printf("TEST 2: choice1 = 2 = +2 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 0;
	xtraCoins = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded){
        printf("    PASS: Card Count is correct\n");
    }
    else{
        printf("    FAIL: Card Count is incorrect\n");
    }
	if(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards){
        printf("    PASS: Deck Count is correct\n");
    }
    else{
        printf("    FAIL: Deck Count is incorrect\n");
    }
	if(testG.coins == G.coins + xtraCoins){
        printf("    PASS: Coin count is correct\n");
    }
    else{
        printf("    FAIL: Coin count is incorrect\n");
        flag = 1;
    }

	// ----------- TEST 3: choice1 = 3 = trash two cards --------------

	printf("TEST 3: choice1 = 3 = trash two cards\n");
	choice1 = 3;

	// cycle through each eligible combination of 2 cards to trash
	for (i=1; i<G.handCount[thisPlayer]; i++) {
		for (j=i+1; j<G.handCount[thisPlayer]; j++) {

			G.hand[thisPlayer][0] = steward;
			G.hand[thisPlayer][1] = copper;
			G.hand[thisPlayer][2] = duchy;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = feast;

			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));

			printf("starting cards: ");
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
			}
			printf("; ");

			choice2 = j;
			choice3 = i;
			remove1 = testG.hand[thisPlayer][i];
			remove2 = testG.hand[thisPlayer][j];
			cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("removed: (%d)(%d); ", remove1, remove2);
			printf("ending cards: ");

			// tests that the removed cards are no longer in the player's hand
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
				assert(testG.hand[thisPlayer][m] != remove1);
				assert(testG.hand[thisPlayer][m] != remove2);
			}
			printf(", expected: ");
			for (m=1; m<G.handCount[thisPlayer]; m++) {
				if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i] && G.hand[thisPlayer][m] != G.hand[thisPlayer][j]) {
					printf("(%d)", G.hand[thisPlayer][m]);
				}
			}
			printf("\n");

			// tests for the appropriate number of remaining cards
			newCards = 0;
			xtraCoins = 0;
			discarded = 3;
			if (i==1 && j==2) {
				printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
				printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			}
            if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded){
                printf("    PASS: Card Count is correct\n");
            }
            else{
                printf("    FAIL: Card Count is incorrect\n");
                flag = 1;
            }
        	if(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards){
                printf("    PASS: Deck Count is correct\n");
            }
            else{
                printf("    FAIL: Deck Count is incorrect\n");
                flag = 1;
            }
        	if(testG.coins == G.coins + xtraCoins){
                printf("    PASS: Coin count is correct\n");
            }
            else{
                printf("    FAIL: Coin count is incorrect\n");
                flag = 1;
            }
		}

	}

    if(flag == 1){
        printf("FAIL: Steward did not pass tests\n");
    }
    else{
        printf("SUCCESS: Steward pass tests\n");
    }
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
