#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_TESTS 1200

// This randomly tests village

/// Oracle function returns 1 if state is valid after drawing village card,
/// 0 if state is inconsistent with expected results (deckCount should be reduced)
int validateStateAfterVillageDraw(struct gameState * state, int player, int prevActions, int prevDeckCount) {
	if (state->deckCount[player] > prevDeckCount && prevDeckCount != 0) {
		printf("Test failure: deckCount should be smaller than before\n");
        printf("deckCount before: %d   ", prevDeckCount);
        printf("deckCount after: %d\n", state->deckCount[player]);
		return 0;
	}
    else if(state->numActions != prevActions + 2) {
        printf("Test failure: numActions should be 2 larger than before\n");
        printf("numActions before: %d   ", prevActions);
        printf("numActions after: %d\n", state->numActions);
    }
	return 1;
}

int main() {
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		     sea_hag, tribute, smithy};
	int i, players, player, handCount, deckCount, numActions, seed, handPos, coinBonus;
	struct gameState state;

    srand(time(NULL));

	printf("Running Random Card Test for Village\n");

	for (i = 0; i < MAX_TESTS; i++) {

		players = rand() % (MAX_PLAYERS - 2) + 2;
        seed = rand();
		coinBonus = 0;
		handPos = rand() % 4;
		player = i % (players + 1);

        // Initialize gamestate
		initializeGame(players, k, seed, &state);

		// Initiate valid state variables
		state.deckCount[player] = rand() % MAX_DECK;
		state.discardCount[player] = rand() % MAX_DECK;
		state.handCount[player] = rand() % MAX_HAND;

		// Copy state variables
		handCount = state.handCount[player];
		deckCount = state.deckCount[player];
        numActions = state.numActions;

        cardEffect(village, 1, 1, 1, &state, handPos, &coinBonus);
        int result = validateStateAfterVillageDraw(&state, player, numActions, deckCount);
        assert(result == 1);
	}

	printf("Tests Complete\n");

	return 0;
}
/*
int adventurer_card(struct gameState *state, int *currentPlayer, int *drawntreasure, int *cardDrawn, int *temphand, int *z){

    while(*drawntreasure<2){
  if (state->deckCount[*currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
    shuffle(*currentPlayer, state);
  }
  drawCard(*currentPlayer, state);
  *cardDrawn = state->hand[*currentPlayer][state->handCount[*currentPlayer]-1];//top card of hand is most recently drawn card.
  if (*cardDrawn == copper || *cardDrawn == silver || *cardDrawn == gold)
    //*drawntreasure++;
    *drawntreasure=drawntreasure+2;
  else{
    temphand[*z]=*cardDrawn;
    state->handCount[*currentPlayer]--; //this should just remove the top card (the most recently drawn one).
    *z++;
  }
    }
    while(*z-1>=0){
  state->discard[*currentPlayer][state->discardCount[*currentPlayer]++]=temphand[*z-1]; // discard all cards in play that have been drawn
  *z=*z-1;
    }
    return 0;
}
*/
