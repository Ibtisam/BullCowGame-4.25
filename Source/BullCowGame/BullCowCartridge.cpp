// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordsList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
       ProcessGuess(Input);
    }
    
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to Bull & Cows Game!"));
    int32 WordNumber =FMath::RandRange(0, HiddenWords.Num()-1);
    HiddenWord = HiddenWords[WordNumber];
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("You have %i lives"),Lives);
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress Enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (HiddenWord == Guess)
    {
        PrintLine(TEXT("You Win!"));
        EndGame();
        return;
    }
    else
    {
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("No repeating letters!"));
        }

        if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The hidden word has %i characters,\nguess again!"), HiddenWord.Len());
        }
        else
        {
            PrintLine(TEXT("You are wrong, guess again!"));
        }
        
        --Lives;
        if (Lives <= 0)
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives left!"));
            PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
            EndGame();
        }
        PrintLine(TEXT("You have %i lives remaining!"), Lives);
        FBullCowCount GuessCount = GetBullCows(Guess);
        PrintLine(TEXT("The hidden word is %s"), *HiddenWord);
        PrintLine(TEXT("You have %i Bulls and %i Cows."), GuessCount.Bulls, GuessCount.Cows);
        return;
    }
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = i+1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
            {
                return false;
            }
        }
    }
    return true;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
            
        }
    }
    return Count;
}