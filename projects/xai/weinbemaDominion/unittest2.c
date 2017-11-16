/* -----------------------------------------------------------------------
 * Testing getCost()
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <string.h>
 #include <stdio.h>
 #include <assert.h>
 #include "rngs.h"

 int main() {
    int result;
    printf ("------TESTING getCost():------\n");

    //testing curse
    result = getCost(curse);
    if (result == 0){
        printf("getCost(): PASS when card is curse\n");
    }
    else{
        printf("getCost(): FAIL when card is curse\n");
        printf("    expected a PASS (return value 0) when card is curse\n");
    }
    //testing estate
    result = getCost(estate);
    if (result == 2){
        printf("getCost(): PASS when card is estate\n");
    }
    else{
        printf("getCost(): FAIL when card is estate\n");
        printf("    expected a PASS (return value 2) when card is estate\n");
    }

    int i;
    int cards[25] = {duchy, province, copper, silver, gold,
                       adventurer, council_room, feast, gardens, mine,
                       remodel, smithy, village, baron, great_hall,
                       minion, steward, tribute, ambassador, cutpurse,
                       embargo, outpost, salvager, sea_hag, treasure_map};
    int cardValues[25] = {5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};

    for (i = 0; i < 25; i++){
        //success
        if (getCost(cards[i]) == cardValues[i]){
            printf("getCost(): PASS when card is %d\n",cards[i]);
        }
        else{
            printf("getCost(): FAIL when card is %d\n",cards[i]);
            printf("    expected a PASS( return value %d) when card is %d\n", cardValues[i], cards[i]);
        }
    }
    return 0;
 }