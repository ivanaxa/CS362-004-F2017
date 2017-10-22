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





 // getCost function
 /*
 int getCost(int cardNumber)
 {
   switch( cardNumber )
     {
     case curse:
       return 0;
     case estate:
       return 2;
     case duchy:
       return 5;
     case province:
       return 8;
     case copper:
       return 0;
     case silver:
       return 3;
     case gold:
       return 6;
     case adventurer:
       return 6;
     case council_room:
       return 5;
     case feast:
       return 4;
     case gardens:
       return 4;
     case mine:
       return 5;
     case remodel:
       return 4;
     case smithy:
       return 4;
     case village:
       return 3;
     case baron:
       return 4;
     case great_hall:
       return 3;
     case minion:
       return 5;
     case steward:
       return 3;
     case tribute:
       return 5;
     case ambassador:
       return 3;
     case cutpurse:
       return 4;
     case embargo:
       return 2;
     case outpost:
       return 5;
     case salvager:
       return 4;
     case sea_hag:
       return 4;
     case treasure_map:
       return 4;
     }

   return -1;
 }
 */
