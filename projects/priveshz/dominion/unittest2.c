//testing numHandCards

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main (){
      struct gameState G;

      int gamecount = 0;
      int handcount = 5;
      int r, p;
      int k[10] = {adventurer, council_room, feast, gardens, mine,
    	       remodel, smithy, village, baron, great_hall};

      printf("Testing numHandCards\n");

      for (p=0; p<4; p++){
            for (handcount=0; handcount<5; handcount++){
            //clear gamestate
            memset(&G, 23, sizeof(struct gameState));
            //initialize a game
            r = initializeGame(2, k, 1, &G);
            //take current players turn from gamestate
            G.handCount[p] = handcount;
            //check return from the whoseturn function
            gamecount = numHandCards(&G);

            printf("HANDCOUNT: %d\n", gamecount);

            //make sure they are the same
            if (gamecount != G.handCount[p]){
                  printf("NUMHANDCARD FAILED IN ITERATION %d\n", p);
            }
      }
}

      printf("numHandCards passed\n");
      return 0;
}
