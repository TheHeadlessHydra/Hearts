// STD includes
#include <iostream> 
#include <stdlib.h>
#include <vector>
#include <string>
#include <unistd.h>
#include <fstream>
#include <algorithm>
// Local includes
#include "Player.h"
#include "SmartPlayer.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
#include "CardPile.h"
#include "Deck.h"
#include "Card.h"
#include "Options.h"
#include "trick.h"

using namespace std;

// Local Functions *************************************************************

// A local function that prepends sType onto sName.
// It expets one of "S" "R" or "H" for sType
string prependName(string sName, string sType)
{
	if(sType == "S")
		return ("s"+sName);
	else if(sType == "R")
		return ("r"+sName);
	else if(sType == "H")
		return ("h"+sName);
	else
		return "";
}

// A local function that checks if the Card card
// is in the CardPile pile. Returns the two of clubs
// if it finds it, NULL otherwise.
Card* ownsTwoOfClubs(CardPile *pile, Card card)
{
	for(int i = 0; i < pile->getSize(); i++)
	{	
		if(*(pile->getCard(i)) == card)
			return pile->getCard(i);
	}

	return NULL;
}

// A local function that takes in 4 players and an int 
// representing the last player played, and will give you
// a pointer to the next player that should be played.
// This int should be inbetween [1-4] inclusive. 
// This algorithm will choose the player in down to up fashion:
// .. -> playerOne -> playerTwo -> playerThree -> playerFour -> playerOne -> ...  
Player* nextPlayer(Player* playerOne, Player* playerTwo, Player* playerThree, Player* playerFour, int iLastPlayed)
{
	// Take the next player: +1
	// Mod it by 4 so that if we go above 4, we wrap back around to player one
	int i = ((iLastPlayed+1)%4);
	if(i == 1) // 4+1 % 4 = 1
		return playerOne;
	else if(i == 2) // 1+1 % 4 = 2
		return playerTwo;
	else if(i == 3) // 2+1 % 4 = 3
		return playerThree;
	else if(i == 0) // 3+1 % 4 = 0
		return playerFour;
	else
		assert (false); // It should be mathematically impossible to hit this assert. If you do, things really went wrong.
	return NULL;
}

// A local function that calculates the player with the lowest
// amount of points given 4 players. In the event of a tie
// it will output the player in 'alphabetical' order. So if
// playerOne and playerTwo both win, the output will be playerOne.
Player* whoIsTheWinner(Player* playerOne, Player* playerTwo, Player* playerThree, Player* playerFour)
{
	int playerOneValue = playerOne->heartsValue();
	int playerTwoValue = playerTwo->heartsValue();
	int playerThreeValue = playerThree->heartsValue();
	int playerFourValue = playerFour->heartsValue();

	int lowestNumber = min(playerOneValue, playerTwoValue);
	lowestNumber = min(lowestNumber, playerThreeValue);
	lowestNumber = min(lowestNumber, playerFourValue);

	if(playerOneValue == lowestNumber)
		return playerOne;
	else if(playerTwoValue == lowestNumber)
		return playerTwo;
	else if(playerThreeValue == lowestNumber)
		return playerThree;
	else
		return playerFour;
}	

// A local function that deals the cards from the main deck to the players.
// It removes the cards from the deck permanently and moves them to the hands of
// each player. The order it will deal the cards out in is always:
// Player 1 -> Player 2 -> Player 3 -> Player 4
void dealTheCards(Deck *mainDeck, Player* playerOne, Player* playerTwo, Player* playerThree, Player* playerFour )
{
	for(int i = 51; i > -1;)
		{
			Card *card1 = mainDeck->getCard(i);
			mainDeck->removeCard(i);
			playerOne->addToHand(card1);
			i--;

			Card *card2 = mainDeck->getCard(i);
			mainDeck->removeCard(i);
			playerTwo->addToHand(card2);
			i--;

			Card *card3 = mainDeck->getCard(i);
			mainDeck->removeCard(i);
			playerThree->addToHand(card3);
			i--;

			Card *card4 = mainDeck->getCard(i);
			mainDeck->removeCard(i);
			playerFour->addToHand(card4);
			i--;
		}
}

// A local function that will take in a name, type, seed, iterator and arguments list.
// This function is meant to be used to obtain arguments listed after a -p has been called ONLY!
// It will iterate through the arguments list like so:
// 1. ONCE: obtain name. TWICE: obtain type. IF TYPE IS NOT R: DONE. Iterater += 2. 
// 2. ONCE: obtain name. TWICE: obtain type. IF TYPE IS  R: Iterate again, obtain seed, DONE. Iterater += 3. 
void obtainAPlayer(string& sName, string& sType, int& iSeed, int& iIterator, char* argv[])
{
	sName = argv[iIterator];
	iIterator++;
	sType = argv[iIterator];
	// Check if it is of the correct type
	if (!(sType == "R" ||
		  sType == "S" ||
		  sType == "H"))
	{
		cerr << "Illegal player kind: \"" << sType << "\"" << endl;
		exit(1);
	}
	iIterator++;
	if (sType == "R")
	{
		iSeed = atoi(argv[iIterator]);
		assert(iSeed != 0);           // Make sure its a valid seed!
		iIterator++;
	}
}

// The main *************************************************************************************
int main(int argc, char* argv[])
{
	// This holds the main options for the game
	Options mainOptions;

	// Player one
	string sNameOne = "Alice";
	string sTypeOne = "S";
	int iSeedOne = -1;
	// Player two
	string sNameTwo = "Bob";
	string sTypeTwo = "S";
	int iSeedTwo = -1;
	// Player three
	string sNameThree = "Carole";
	string sTypeThree = "S";
	int iSeedThree = -1;
	// Player four
	string sNameFour = "Ted";
	string sTypeFour = "S";
	int iSeedFour = -1;

	string sCheck;
	
	for(int i = 1; i < argc; i++)
	{
		sCheck = argv[i];
		if(sCheck == "-r")
			mainOptions.setSeed( atoi(argv[++i]) );
		else if(sCheck == "-s")
			mainOptions.setMaxScore( atoi(argv[++i]) );
		else if(sCheck == "-d")
			mainOptions.setFileName( argv[++i] );
		else if(sCheck == "-p")
		{
			i++;

			// Make sure there are enough arguments to the -p
			int iIndex = i;
			int iCounter = 0;
			int iRCounter = 0;
			// Obtain total number of optional arguments to -p
			while(true)
			{
				if(iIndex >= argc)
					break;
				string sTemp = argv[iIndex];
				if(sTemp == "R")
					iRCounter++;
				if(sTemp[0] == '-')
					break;

				iCounter++;
				iIndex++;
			}
			// Check to see if -p has the right amount of arguments
			if (iCounter < 8 || 
			   (iRCounter == 1 && iCounter < 9) ||
			   (iRCounter == 2 && iCounter < 10) ||
			   (iRCounter == 3 && iCounter < 11) ||
			   (iRCounter == 4 && iCounter < 12))
			{
				cerr << "Error, -p requires another argument.  Aborting." << endl;
				exit(1);
			}

			// Obtain the stats of each player.
			obtainAPlayer(sNameOne, sTypeOne, iSeedOne, i, argv);
			obtainAPlayer(sNameTwo, sTypeTwo, iSeedTwo, i, argv);
			obtainAPlayer(sNameThree, sTypeThree, iSeedThree, i, argv);
			obtainAPlayer(sNameFour, sTypeFour, iSeedFour, i, argv);
			i--; // Go back one - needed because of the way obtainAPlayer is implemented.
		}
	}

	// Prepend the names with the proper suffixes
	sNameOne = prependName(sNameOne, sTypeOne);
	sNameTwo = prependName(sNameTwo, sTypeTwo);
	sNameThree = prependName(sNameThree, sTypeThree);
	sNameFour = prependName(sNameFour, sTypeFour);

	// Create the Players ----------------------------
	// Create player one
	Player *playerOne;
	if(sTypeOne == "S")
		playerOne = new SmartPlayer(1, sNameOne);
	else if(sTypeOne == "R")
		playerOne = new RandomPlayer(1, sNameOne, iSeedOne);
	else if(sTypeOne == "H")
		playerOne = new HumanPlayer(1, sNameOne);

	// Create player two
	Player *playerTwo;
	if(sTypeTwo == "S")
		playerTwo = new SmartPlayer(2, sNameTwo);
	else if(sTypeTwo == "R")
		playerTwo = new RandomPlayer(2, sNameTwo, iSeedTwo);
	else if(sTypeTwo == "H")
		playerTwo = new HumanPlayer(2, sNameTwo);

	// Create player three
	Player *playerThree;
	if(sTypeThree == "S")
		playerThree = new SmartPlayer(3, sNameThree);
	else if(sTypeThree == "R")
		playerThree = new RandomPlayer(3, sNameThree, iSeedThree);
	else if(sTypeThree == "H")
		playerThree = new HumanPlayer(3, sNameThree);

	// Create player four
	Player *playerFour;
	if(sTypeFour == "S")
		playerFour = new SmartPlayer(4, sNameFour);
	else if(sTypeFour == "R")
		playerFour = new RandomPlayer(4, sNameFour, iSeedFour);
	else if(sTypeFour == "H")
		playerFour = new HumanPlayer(4, sNameFour);

	// Create the deck ---------------------------------
	Deck *mainDeck = new Deck;
	if(mainOptions.getFileName() == "")
		mainDeck->generate();
	else
	{
		string fileName = mainOptions.getFileName();
		ifstream deckFile( fileName.c_str() );
		if(deckFile.is_open())
		{
			deckFile >> *(mainDeck);
			deckFile.close();
		}
	}
	// Set the seed for the deck
	mainDeck->setRandomSeed(mainOptions.getSeed());

	// Output the beginning newline
	cout << endl;

	int iHandNumber = 1; 	// Used to calculate the hand number
	int iWhoIsNext = 1; 	// Used to calculate which order the cards get dealt in.
	Player *exceededPoints; // The player who exceeded the points.
	Player *winner; 		// The player who won the game.

	do // Start of the game! ------------------------------------------------------------------------
	{
		// Shuffle the deck
		mainDeck->shuffle();

		// Cout the first values of the game
		cout << endl << "At the beginning of hand " << iHandNumber << ", here is the deck:" << endl;
		cout << "    ";
		mainDeck->print();
		cout << endl << endl << endl;

		// Deal the cards
		if (iWhoIsNext == 1)
		{
			iWhoIsNext++;
			dealTheCards(mainDeck, playerOne, playerTwo, playerThree, playerFour);
		}
		else if (iWhoIsNext == 2)
		{
			iWhoIsNext++;
			dealTheCards(mainDeck, playerTwo, playerThree, playerFour, playerOne);
		}
		else if (iWhoIsNext == 3)
		{
			iWhoIsNext++;
			dealTheCards(mainDeck, playerThree, playerFour, playerOne, playerTwo);
		}
		else
		{
			iWhoIsNext = 1;
			dealTheCards(mainDeck, playerFour, playerOne, playerTwo, playerThree);
		}

		// Show to console the hands for each player
		cout << "Here are the hands for each player at the start of hand number " << iHandNumber << endl << endl;

		cout << playerOne->getName() << " has these cards:" << endl << "    ";
		playerOne->printHand(); cout << endl << endl;

		cout << sNameTwo << " has these cards:" << endl << "    ";
		playerTwo->printHand(); cout << endl << endl;

		cout << sNameThree << " has these cards:" << endl << "    ";
		playerThree->printHand(); cout << endl << endl;

		cout << sNameFour << " has these cards:" << endl << "    ";
		playerFour->printHand(); cout << endl << endl << endl;

		// Find out who the current player is on the first round by finding 
		// who owns the two of clubs
		Player *currentPlayer;
		if( ownsTwoOfClubs( playerOne->getHand(), Card::TwoOfClubs ) != NULL )
			currentPlayer = playerOne;
		else if( ownsTwoOfClubs( playerTwo->getHand(), Card::TwoOfClubs ) != NULL )
			currentPlayer = playerTwo;
		else if( ownsTwoOfClubs( playerThree->getHand(), Card::TwoOfClubs ) != NULL )
			currentPlayer = playerThree;
		else if( ownsTwoOfClubs( playerFour->getHand(), Card::TwoOfClubs ) != NULL )
			currentPlayer = playerFour;
		else
			assert (false); // No one owns the two of clubs?! Huge error!

		// Create the first trick of the game
		trick *currentTrick = new trick;
		// Get the two of clubs
		Card *cardToBePlayed = ownsTwoOfClubs( currentPlayer->getHand(), Card::TwoOfClubs );

		// Play the 13 rounds of the game
		for(int iRoundNumber = 1; iRoundNumber < 14; iRoundNumber++)
		{
			cout << "Now starting round " << iRoundNumber <<" of hand " << iHandNumber << endl;

			// Each person plays their card
			for(int iPlayNumber = 0; iPlayNumber < 4; iPlayNumber++)
			{
				// Special case where the 2 of clubs has been played, we need a custom cout statement
				if( iRoundNumber == 1 && iPlayNumber == 0 )
				{
					cout << "  " << currentPlayer->getName() << " has 2C and leads with it" << endl;
				}
				else
				{
					if(iPlayNumber != 0)
						currentPlayer = nextPlayer(playerOne, playerTwo, playerThree, playerFour, currentPlayer->getPlayerNumber() );
					cardToBePlayed = currentPlayer->PlayCard(currentTrick);
				}
				// Take the card from the hand, and put it into the trick
				currentTrick->addToTrick(cardToBePlayed, currentPlayer);
				if ( !currentPlayer->removeFromHand(cardToBePlayed) )
					assert(false); // cardToBeplayed was not removed from the hand
			}
			// Get the winner of the last trick. This function
			// itself will give the winning player the 4 cards.
			currentPlayer = currentTrick->getWinner();
		}

		// Calculate the hearts values of each player up to this point.
		int iPlayerOneScore = playerOne->heartsValue();
		int iPlayerTwoScore = playerTwo->heartsValue();
		int iPlayerThreeScore = playerThree->heartsValue();
		int iPlayerFourScore = playerFour->heartsValue();

		// Empty the discarded piles, as they are no longer needed. 
		playerOne->emptyDiscard();
		playerTwo->emptyDiscard();
		playerThree->emptyDiscard();
		playerFour->emptyDiscard();

		// Generate a new deck
		mainDeck->generate();

		// Display the score at the end of the round
		cout << "At the end of hand " << iHandNumber << ", the score is:" << endl;
		cout << "    " << playerOne->getName() << "  " << iPlayerOneScore << endl;
		cout << "    " << playerTwo->getName() << "  " << iPlayerTwoScore << endl;
		cout << "    " << playerThree->getName() << "  " << iPlayerThreeScore << endl;
		cout << "    " << playerFour->getName() << "  " << iPlayerFourScore << endl << endl;

		// Delete the trick
		delete currentTrick;

		// Check to see if the game is over. If it is, record who won and who lost. 
		if ( iPlayerOneScore >= mainOptions.getMaxScore() )
		{
			exceededPoints = playerOne;
			winner = whoIsTheWinner(playerOne, playerTwo, playerThree, playerFour);
			break;
		}
		if ( iPlayerTwoScore >= mainOptions.getMaxScore() )
		{
			exceededPoints = playerTwo;
			winner = whoIsTheWinner(playerOne, playerTwo, playerThree, playerFour);
			break;
		}
		if ( iPlayerThreeScore >= mainOptions.getMaxScore() )
		{
			exceededPoints = playerThree;
			winner = whoIsTheWinner(playerOne, playerTwo, playerThree, playerFour);
			break;
		}
		if ( iPlayerFourScore >= mainOptions.getMaxScore() )
		{
			exceededPoints = playerFour;
			winner = whoIsTheWinner(playerOne, playerTwo, playerThree, playerFour);
			break;
		}
		iHandNumber++;
	} while(true); // End of the game! ----------------------------------------------

	// Output who the winner is
	cout << "The game is over." << endl;
	cout << exceededPoints->getName() << " has exceeded " << mainOptions.getMaxScore() << " points." << endl;
	cout << "The winner is " << winner->getName() << endl;

	// Free all allocated space. Main deck will be freed on its own after it goes out of scope
	// thanks to the deconstructor of the CardPile class. 
	delete mainDeck;
	delete playerOne;
	delete playerTwo;
	delete playerThree;
	delete playerFour;

	return 0;
}
