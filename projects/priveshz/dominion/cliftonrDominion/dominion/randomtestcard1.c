/*
This random test is for Villager.

Villager draws a card, gives the player 2 more actions, and discards villager from the player
hand. My refactored code will subtract 2 actions instead.
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
      int i, n, j, game, player, handcount, actions, returnvalue, randomcard;
      int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0, pass = 1;
      //seeds used are the same as in betterTestDrawCard.c
      SelectStream(2);
      PutSeed(3);
      //array for gameState
      int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

      struct gameState G;

      int properhandcount = 1, properactioncount = 1;


      printf("STARTING VILLAGE RANDOM TEST\n");

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
            handcount = numHandCards(&G);
            G.deckCount[player] = rand() % MAX_DECK + 1;
            G.discardCount[player] = rand() % MAX_DECK + 1;
            handPos = (rand() % G.handCount[player]);
            actions = G.numActions;

            //play my refactored village function
            returnvalue = cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);
            if (returnvalue != 0) {
                  printf("Return Fail");
                  pass = 0;
            };

            //check to see if the draw and discard happened correctly, hand count should remain the same
            if (G.handCount[player] != handcount){
                        printf("VILLAGE HANDCOUNT FAILED IN ITERATION: %d\n", i);
                        printf("LOCAL HANDCOUNT: %d\n", handcount);
                        printf("GAMESTATE HANDCOUNT: %d\n", G.handCount[player]);
                  properhandcount = 0;
            }

            //check for correct number of actions. Since my refactored code incorrectly sets actions, this should always fire
            if (G.numActions != (actions + 2)){
                        printf("VILLAGE NUMACTIONS FAILED IN ITERATION: %d\n", i);
                        printf("LOCAL ACTION NUMBER: %d\n", actions);
                        printf("GAMESTATE ACTION NUMBER: %d\n", G.numActions);
                  properactioncount = 0;
            }

            //check properactioncount and properhandcount for pass/fail
            if (properhandcount){
                  printf("VILLAGE HANDCOUNT PASSED\n");
            }
            else {
                  printf("VILLAGE HANDCOUNT FAILED\n");
            }
            if (properactioncount){
                  printf("VILLAGE ACTIONCOUNT FAILED\n");
            }
            else {
                  printf("VILLAGE ACTIONCOUNT FAILED\n");
            }
      }
      if (pass){
      printf("END OF VILLAGE TESTING SUCCESSFULLY\n");
}
else {
      printf("VILLAGE CARD TEST FAILED\n");
}
      return 0;
}
