#pragma once
#include <iostream>

using namespace std;

// **** Enums ******//
enum enPlayerChoice
{
    Rock = 1,
    Paper = 2,
    Scissors = 3
};
enum enWinner
{
    Human,
    Computer,
    Tie
};
enum enScreen
{
    Red,
    Blue,
    Green
};
// **** Structures ****//
struct GameInfo
{
    short LeftRounds;
    short CurrentRound = 1;  // game has at least one round
    short HumanWinnings = 0; // number of winning rounds
    short ComputerWinnings = 0;
    short DrawRounds = 0;

    enPlayerChoice HumanChoice;
    enPlayerChoice ComputerChoice;

    enWinner GameWinner; // for entier game
    enWinner CurrentRoundWinner; // per round
};

void StartGame();