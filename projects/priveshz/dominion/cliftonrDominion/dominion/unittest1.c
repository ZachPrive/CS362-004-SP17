//test handCard

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main (){
      struct gameState G;

      int turn = 0;
      int p = 0;
      int r;
      int k[10] = {adventurer, council_room, feast, gardens, mine,
    	       remodel, smithy, village, baron, great_hall};

      printf("Testing whoseTurn\n");

      for (p=0; p<4; p++){
            //clear gamestate
            memset(&G, 23, sizeof(struct gameState));
            //initialize the game
            r = initializeGame(2, k, 1, &G);
            //take current players turn from gamestate
            G.whoseTurn = p;
            //check return from the whoseturn function
            turn = whoseTurn(&G);

            //make sure they are the same
            assert(turn == p);
      }

      printf("whoseTurn passed\n");
      return 0;
}
