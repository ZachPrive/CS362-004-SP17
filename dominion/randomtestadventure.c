/*
Random test of adventure

my refactored code changed the check for 2 treasure cards to 1, so the function stops after receiving only one treasure card.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set NOISY_TEST like in the examples and maximum number of tests to make
#define NOISY_TEST 1
#define MAX_TESTS 1500

int main(){

      //set variables to be used
      int i, j, game, player, coins, handcount = 0, deckcount, whichturn;

      //seeds used are the same as in betterTestDrawCard.c
      SelectStream(2);
      PutSeed(3);

      //array for gameState
      int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

      struct gameState G;
      //new gamestate and player set
      player = rand() % 3 + 1;
      game = initializeGame(player, k, 1, &G);

      //check for proper gamestate intilization
      assert(game == 0);

      //check if player has 5 cards in hand
      assert(numHandCards(&G) == 5);
      //bool values for later check
      int didcoinspass = 1, didhandcountpass = 1, correctplayerturn = 1, diddeckcoundpass = 1;

      printf("RANDOM TESTING ADVENTURER\n");

      for (i = 0; i < MAX_TESTS; i++){
            //initalize
            game = initializeGame(player, k, 1, &G);

            //random hand and deck values
            G.handCount[player] = rand() % MAX_HAND + 1;
            G.deckCount[player] = rand() % MAX_DECK + 1;
            //start with zero for discardCount
            G.discardCount[player] = 0;

            //set variables for later check
            deckcount = G.deckCount[player];
            G.whoseTurn = player;
            whichturn = G.whoseTurn;


            for (j = 0; j < 5; j++){
                  //fill hand randomly
                  int randomcard = rand() % 10;
                  //add random treasure card
                  if (randomcard == 5){
                        G.hand[player][j] = copper;
                        G.coins++;
                  }
                  else{
                        G.hand[player][j] = k[randomcard];
                  }
            }
            //pre condition coin count and handcount
            coins = G.coins;
            handcount = G.handCount[player];


            //play adventurer
            playAdventurer(&G);

            //check coins. Since my refactored code will pull out at 1 treasure card, the check will always fire
            if (G.coins != coins + 2){
            #if (NOISY_TEST == 1)
                  printf("ADVENTURER COINS CHECK FAILED\n");
                  printf("COINS PRE CONDITION: %d\n", coins);
                  printf("COINS POST CONDITION: %d\n", G.coins);
                  didcoinspass = 0;
            #endif
            }
            //check if the player turn changed
            if (G.whoseTurn != whichturn){
                  #if (NOISY_TEST == 1)
                  printf("PLAYER TURN HAS CHANGED AND THUS FAILED\n");
                  printf("PLAYER TURN EXPECTED: %d\n", whichturn);
                  printf("PLAYER TURN ACTUAL: %d\n", G.whoseTurn);
                  correctplayerturn = 0;
                  #endif
            }
            //check handcount increase by 1. Since the refactored code pulls out after 1, this should always fire
            if(G.handCount[player] != handcount + 2){
                  #if (NOISY_TEST == 1)
                  printf("PLAYER HANDCOUNT CHANGE FAILED\n");
                  printf("PLAYER HANDCOUNT EXPECTED: %d\n", handcount);
                  printf("PLAYER HANDCOUNT ACTUAL: %d\n", G.handCount[player]);
                  didhandcountpass = 0;
                  #endif
            }
            //check if no change in deckcount
            if (G.deckCount[player] == deckcount){
                  #if (NOISY_TEST == 1)
                  printf("DECKCOUNT CHECK HAS FAILED\n");
                  diddeckcoundpass = 0;
                  #endif
            }
      }
      //check post test bool values
      if (didcoinspass){
            printf("ADVENTURE CARD COINS TEST PASSED\n");
      }
      else{
            printf("ADVENTURE CARD COINS TEST FAILED\n");
      }
      if (correctplayerturn){
            printf("ADVENTURER CARD PLAYER TURN PASSED\n");
      }
      else {
            printf("ADVENTURER CARD PLAYER TURN FAILED\n");
      }
      if (didhandcountpass){
            printf("ADVENTURER CARD HANDCOUNT TEST PASSED\n");
      }
      else {
            printf("ADVENTURER CARD HANDCOUNT TEST FAILED\n");
      }
      if (diddeckcoundpass){
            printf("ADVENTURER CARD DECKCOUNT TEST PASSED\n");
      }
      else {
            printf("ADVENTURER CARD DECKCOUNT TEST FAILED\n");
      }
      //end function
      printf("ADVENTURER CARD TEST FINISHED\n");
      return 0;
}
