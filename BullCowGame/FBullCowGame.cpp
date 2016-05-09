#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

uint32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES{8};
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if the guess isnt an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	    
	else if (!IsLowercase(Guess))//if the guess isnt all lowercase, number or special char
	{
		return EGuessStatus::Invalid_Character;
	}
	else if (Guess.length() != GetHiddenWordLenght())// if guess is wrong lenght
	{
		return EGuessStatus::Wrong_Lenght;
	}
	
	else// otherwise
	{
		return EGuessStatus::OK;
	}
	    //return OK
	return EGuessStatus::OK;
}
// receives a valid guess, increments  try and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	uint32 WordLenght{MyHiddenWord.length()};
	// loop through all letters in the hidden word
	for (uint32 MHWChar{0}; MHWChar < WordLenght; MHWChar++)
	{
		// loop through all letters in the guess
		for (uint32 GChar{0}; GChar < WordLenght; GChar++)
		{
			// compare letters agaisnt the guess
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	// compare letters agaisnt the hidden word
	bGameIsWon = (BullCowCount.Bulls == WordLenght);
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// treat 0 and 1 letter words as isograms
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;// setup our map
	for (auto Letter : Guess)// loop through all the letters
	{
		Letter = tolower(Letter); //convert letter to lowercase
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
			
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }
	for (auto Letter : Guess)// loop through all the letters
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}


