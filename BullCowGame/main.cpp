/* This is the console executable that makes use of the Bullcow class
This acts as the view in a MVC pattern and is responsible for all user 
interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using std::cout;
using std::cin;
using std::getline;
using FText = std::string;
using int32 = int32;
using uint32 = unsigned int;

// prototypes
void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

//the entry point for our application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain() == true);
	return 0;
}

FBullCowGame BCGame{}; //instantiate a new game


// introduce the game
void PrintIntro()
{
	cout << "\n\nWelcome to Bulls and Cows\n";
	cout << "Can you guess the " << BCGame.GetHiddenWordLenght();
	cout << " letter isogram I'm thinking of?\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries{BCGame.GetMaxTries()};
	// loop asking for guesses while the game is not won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess{GetValidGuess()};
		
		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		cout << "Bulls = " << BullCowCount.Bulls;
		cout << ". Cows = " << BullCowCount.Cows << '\n';
		// Print number of bulls and cows
	}
	PrintGameSummary();
}

// Loop continually until the user gets a valid guess
FText GetValidGuess()
{
	EGuessStatus Status{EGuessStatus::Invalid_Status};
	FText Guess{};
	do {
		// Get a guess from the player
		int32 CurrentTry{BCGame.GetCurrentTry()};
		cout << '\n';
		cout << "Try " << CurrentTry << ". Enter your guess: ";
		getline(cin, Guess);
		cout << '\n';

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Invalid_Character:
			cout << "Please enter all lowercase alphabetical characters.\n";
			break;
		case EGuessStatus::Not_Isogram:
			cout << "Please enter a word without repeating letters\n";
			break;
		case EGuessStatus::Wrong_Lenght:
			cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		cout << "\nCongratulations. YOU WIN!\n\n";
		cout << "You've used: " << BCGame.GetCurrentTry()-1 << " tries.\n\n";
	}
	else
	{
		cout << "Sorry. YOU LOSE!\n";
	}
}

//Ask the player whether they want to play again and returns them to the game
bool AskToPlayAgain()
{
	cout << "Do you want to play again? (y/n) ";
	FText Response{};
	getline(cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}