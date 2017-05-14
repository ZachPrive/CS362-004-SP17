/*
This random test is for Smithy.

Smithy makes the player draw 3 cards. My refactored code only allows the player to draw one card.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//define noisytest as shown in the examples and the number of tests to return
#define NOISY_TEST 1
#define MAX_TESTS 1500


int main(){

      //define variables to be used
      int i, j, game, player, handcount, discardcount = 0;
      //seeds used are the same as in betterTestDrawCard.c
      SelectStream(2);
      PutSeed(3);
      //array for gameState
      int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

      struct gameState G;

      //bool value for later check
      int didhandcountpass = 1, diddiscardcountpass = 1;

      //player seed and game initalize
      player = rand() % 3 + 1;
      game = initializeGame(player, k, 1, &G);

      //check for proper initialize and proper starting hand count
      assert(game == 0);
      assert(numHandCards(&G) == 5);

      for (i = 0; i < MAX_TESTS; i++){
            game = initializeGame(player, k, 1, &G);

            //set random values
            G.handCount[player] = rand() % MAX_HAND + 1;
            G.deckCount[player] = rand() % MAX_DECK + 1;

            player = G.whoseTurn;
            G.discardCount[player] = 0;

            //fill hand randomly
            for (j = 0; j < 5; j++){
                  int randomcard = rand() % 10;
                  G.hand[player][j] = k[randomcard];
            }

            //set local variables
            handcount = G.handCount[player];

            //play smithy
            playSmithy(&G, 0);

            //check if the number of cards in hand increase by 2 (draw 3 discard 1). Since I only gain 1 card this should always fire
            if (G.handCount[player] != handcount + 2){
                  #if (NOISY_TEST == 1)
                  printf("SMITHY CARD HANDCOUNT TEST FAILED\n");
                  printf("EXPECTED HAND COUNT: %d\n", handcount);
                  printf("ACTUAL HAND COUNT: %d\n", G.handCount[player]);
                  didhandcountpass = 0;
                  #endif
            }
            //check increase in discard pile
            if (G.discardCount[player] == discardcount){
                  #if (NOISY_TEST == 1)
                  printf("SMITHY CARD DISCARDCOUNT FAILED: DID NOT INCREASE\n");
                  diddiscardcountpass = 0;
                  #endif
            }
      }
      //check bool values
      if (didhandcountpass){
            printf("SMITHY CARD HANDCOUNT TEST PASSED\n");
      }
      else {
            printf("SMITHY CARD HANDCOUNT TEST FAILED\n");
      }
      if (diddiscardcountpass){
            printf("SMITHY CARD DISCARDCOUNT TEST PASSED\n");
      }
      else {
            printf("SMITHY CARD DISCARDCOUNT TEST FAILED\n");
      }
      //end function
      printf("SMITHY CARD TEST FINISHED\n");
      return 0;
}
