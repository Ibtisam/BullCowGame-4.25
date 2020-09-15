// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
    //PrintLine(TEXT("The Hidden Word is %s.\nIt is %i characters long.\n"), *HiddenWord, HiddenWord.Len());
    
    
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
        if (HiddenWord == Input)
        {
            PrintLine(TEXT("You Win!"));
            EndGame();
        }
        else
        {
            --Lives);
            if (Lives > 0)
            {
                if (Input.Len() != HiddenWord.Len())
                {
                    PrintLine(TEXT("Sorry, try guessing again!\nYou have %i lives remaining!"), Lives);
                }   
            }
            else
            {
                PrintLine(TEXT("You have no lives!"));
                EndGame();
            }
                
        }
    }
    
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to Bull & Cows Game!"));
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("You have %i lives"),Lives);
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again!"));
}