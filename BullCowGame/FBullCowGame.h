#pragma once
#include <string>

using FString = std::string;
using int32 = int;
using uint32 = unsigned int;

struct FBullCowCount 
{
	int32 Bulls{};
	int32 Cows{};
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Invalid_Character
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor
	uint32 GetHiddenWordLenght() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const; // Passes on that a valid guess has been made

	EGuessStatus CheckGuessValidity(FString) const; // TODO make a more rich return value.

	void Reset(); // TODO make a more rich return value.
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};