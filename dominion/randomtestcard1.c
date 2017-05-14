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
#include <assert.h>

//define noisytest as shown in the examples and the number of tests to return
#define NOISY_TEST 1
#define MAX_TESTS 1500


int main(){

      //define variables to be used
      int i, j, game, player, handcount, actions;
      //seeds used are the same as in betterTestDrawCard.c
      SelectStream(2);
      PutSeed(3);
      //array for gameState
      int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

      struct gameState G;

      int properhandcount = 1, properactioncount = 1;

      //new gamestate and player set
      player = rand() % 3 + 1;
      game = initializeGame(player, k, 1, &G);

      //check for proper gamestate intilization
      assert(game == 0);

      //check if player has 5 cards in hand and 1 action
      assert(numHandCards(&G) == 5);
      assert(G.numActions == 1);


      printf("STARTING VILLAGE RANDOM TEST\n");

      for (i = 0; i < MAX_TESTS; i++){

            game = initializeGame(player, k, 1, &G);

            //set random values
            G.handCount[player] = rand() % MAX_HAND + 1;//+1 so we at least have 1
            G.discardCount[player] = rand() % MAX_DECK + 1;
            G.deckCount[player] = rand() % MAX_DECK + 1;


            //make a random hand
            for (j = 0; j < 5; j++) {
                  int randomcard = rand() % 10;//pick a random index for k
                  G.hand[player][j] = k[randomcard];
            }

            //set action randomly
            G.numActions = rand() % MAX_HAND + 1;

            //set local variables for comparison
            G.whoseTurn = player;
            handcount = G.handCount[player];
            actions = G.numActions;

            //play my refactored village function
            playVillage(&G, 0);

            //check to see if the draw and discard happened correctly, hand count should remain the same
            if (G.handCount[player] != handcount){
                  //using NOISY_TEST here as shown in examples
                  #if (NOISY_TEST == 1)
                        printf("VILLAGE HANDCOUNT FAILED IN ITERATION: %d\n", i);
                        printf("LOCAL HANDCOUNT: %d\n", handcount);
                        printf("GAMESTATE HANDCOUNT: %d\n", G.handCount[player]);
                  #endif
                  properhandcount = 0;
            }

            //check for correct number of actions. Since my refactored code incorrectly sets actions, this should always fire
            if (G.numActions != (actions + 2)){
                  #if (NOISY_TEST == 1)
                        printf("VILLAGE NUMACTIONS FAILED IN ITERATION: %d\n", i);
                        printf("LOCAL ACTION NUMBER: %d\n", actions);
                        printf("GAMESTATE ACTION NUMBER: %d\n", G.numActions);
                  #endif
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
      //end the test
      printf("END OF VILLAGE TESTING\n");
      return 0;
}
