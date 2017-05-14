CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unit1:
	gcc -fprofile-arcs -ftest-coverage -WALL -std=c99 dominion.c rngs.c unittest1.c -o unittest1 -lm -g

testresults: dominion.h rngs.h dominion_helpers.h dominion.o rngs.o rngs.o unittest1.c unittest2.c randomtestcard1.c randomtestcard2.c randomtestadventure.c
	#first unit test
	gcc -o unittest1 unittest1.c dominion.o rngs.o -g $(CFLAGS)
	./unittest1
	gcov dominion.c >> unittestresult.out
	gcov unittest1.c >> unittestresult.out
	cat unittest1.c.gcov >> unittestresult.out
	#second unit test
	gcc -o unittest2 unittest2.c dominion.o rngs.o -g $(CFLAGS)
	./unittest2
	gcov unittest2.c >> unittestresult.out
	cat unittest2.c.gcov >> unittestresult.out
	#first random card test
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o -g $(CFLAGS)
	./randomtestcard1
	gcov dominion.c >> randomtestresult.out
	gcov randomtestcard1.c >> randomtestresult.out
	cat randomtestcard1.c.gcov >> randomtestresult.out
	#second random card test adventurer
	gcc -o randomtestadventure randomtestadventure.c dominion.o rngs.o -g $(CFLAGS)
	./randomtestadventure
	gcov dominion.c >> randomtestresult.out
	gcov randomtestadventure.c >> randomtestresult.out
	cat randomtestadventure.c.gcov >> randomtestresult.out
	#second random card test adventurer
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o -g $(CFLAGS)
	./randomtestcard2
	gcov dominion.c >> randomtestresult.out
	gcov randomtestcard2.c >> randomtestresult.out
	cat randomtestcard2.c.gcov >> randomtestresult.out


all: playdom player testDrawCard testBuyCard badTestDrawCard runtests testresults

clean:
	rm -f *.o playdom.exe playdom test.exe unittest1 unittest2 randomtestcard1 test runtests testresults player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
