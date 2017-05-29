/*
This random test is for Smithy.

Smithy makes the player draw 3 cards. My refactored code only allows the player to draw one card.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//define noisytest as shown in the examples and the number of tests to return
#define NOISY_TEST 1
#define MAX_TESTS 1500


int main(){

      //define variables to be used
      int i, n, j, game, player, handcount, discardcount = 0, returnvalue, randomcard;
      int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0, pass = 1;
      //seeds used are the same as in betterTestDrawCard.c
      SelectStream(2);
      PutSeed(3);
      //array for gameState
      int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

      struct gameState G;

      //bool value for later check
      int didhandcountpass = 1, diddiscardcountpass = 1;

      //game = initializeGame(player, k, 1, &G);

      //check for proper initialize and proper starting hand count
      //assert(game == 0);
      //assert(numHandCards(&G) == 5);

      for (i = 0; i < MAX_TESTS; i++){
            for (n = 0; n < sizeof(struct gameState)/ sizeof(int); n++) {
                ((int*)&G)[n] = rand() % 128;
            }
            //game = initializeGame(player, k, 1, &G);

            //set random values
            G.numPlayers = (rand() % 3)+2;
		G.whoseTurn = rand() % G.numPlayers;
            player = whoseTurn(&G);
            G.handCount[player] = rand() % MAX_HAND + 1;
            G.deckCount[player] = rand() % MAX_DECK + 1;
            G.discardCount[player] = rand() % MAX_DECK + 1;
            handPos = (rand() % G.handCount[player]);

            //set local variables
            handcount = G.handCount[player];

            //play smithy
            returnvalue = cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);
            if (returnvalue != 0) {
			printf("Return Fail");
			pass = 0;
		};

            //check if the number of cards in hand increase by 2 (draw 3 discard 1). Since I only gain 1 card this should always fire
            if (G.handCount[player] != handcount + 2){
                  #if (NOISY_TEST == 1)
                  printf("SMITHY CARD HANDCOUNT TEST FAILED\n");
                  printf("EXPECTED HAND COUNT: %d\n", handcount + 2);
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
      if (returnvalue){
      printf("SMITHY CARD TEST SUCCESSFULLY FINISHED\n");
}
else {
      printf("SMITHY CARD TEST FAILED\n");
}
      return 0;
}
