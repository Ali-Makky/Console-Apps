#include <iostream>
#include <string>
#include <windows.h>
#include "lib.hpp"

using namespace std;
// the range of valid ranges of the game
#define MIN 1 // minimum valid rounds
#define MAX 5 // maximum valid rounds

////////////////////////////
// ***** Functions ***** //
////////////////////////////

/*
 * Ask user to enter how many rounds in the game
 * @return: number of rounds
 */
int ReadRoundsNumber()
{
    cout << "\nHow many rounds do you want to play [" << MIN << ", " << MAX << "]?\nEnter >> ";
    int rounds;
    cin >> rounds;
    while (rounds < MIN || rounds > MAX)
    {
        cout << "Rounds must be in range [" << MIN << ", " << MAX << "] !." << endl
             << "Please try again." << endl
             << "\nHow many rounds do you want to play [" << MIN << ", " << MAX << "]?\nEnter >> ";
        cin >> rounds;
    }

    return rounds;
}

/*
 * @param: both players' choices
 * @return: winner player
 */
enWinner DetermineRoundWinner(enPlayerChoice humanChoice, enPlayerChoice computerChoice)
{
    if (humanChoice == computerChoice)
        return enWinner::Tie;
    else if ((humanChoice == Rock && computerChoice == Paper) || (humanChoice == Scissors && computerChoice == Rock) || (humanChoice == Paper && computerChoice == Scissors))
        return enWinner::Computer;
    else
        return enWinner::Human;
}

/*
 * @return: player's choice
 */
enPlayerChoice ReadPlayerChoice()
{
    int choice;
    do
    {
        cout << "Your choice: [1]Rock, [2]Paper, [3]Scissors ?\n>> ";
        cin >> choice;    
    } while (choice < 1 || choice > 3);
    
    return enPlayerChoice(choice);
}

/*
 * @param: random range
 * @return: random number in the range
 */
int RandIntIn(int start, int end)
{
    int number = (rand() % (end - start + 1)) + start;
    return number;
}

/*
 * computer random choice
 */
enPlayerChoice RandomChoice()
{
    int number = RandIntIn(1, 3);
    return enPlayerChoice(number);
}

/*
 * @param: player's choices
 * @return: player's choice as string
 */
inline const char *ToString(enPlayerChoice c)
{
    switch (c)
    {
    case Rock:
        return "Rock";
    case Paper:
        return "Paper";
    case Scissors:
        return "Scissors";
    default:
        return "[Unknown choice]";
    }
}

/*
 * @param: winner enum
 * @return: winner's name as string
 */
inline const char *ToString(enWinner w)
{
    switch (w)
    {
    case Human:
        return "You :)";
    case Computer:
        return "Computer :(";
    case Tie:
        return "[No Winner]";
    default:
        return "[Unknown choice]";
    }
}

/*
*@param: number of tabs
*@return: string of tabs
*/
string Tabs(short n)
{
    string tabs = "";
    for (int i = 0; i < n; i++)
        tabs += "\t";
    return tabs;
}

////////////////////////////
// ***** Procedures ***** //
////////////////////////////

// clean the console screen
void ResetConsole()
{
    system("cls");     // clear the console
    system("color 7"); // default colors
}

// print game over headr
void PrintGameOver()
{
    cout << Tabs(3) << "----------------------------------------------------------------\n\n";
    cout << Tabs(3) << "                  +++ G a m e   O v e r +++\n" << endl;
    cout << Tabs(3) << "----------------------------------------------------------------\n\n";
}

// print round information
void PrintRoundInfo(GameInfo game)
{
    cout << "----------Round[" << game.CurrentRound << "]----------\n\n";
    cout << "Your choice    :  " << ToString(game.HumanChoice) << endl;
    cout << "Computer choice: " << ToString(game.ComputerChoice) << endl;
    cout << "Round Winner   : " << ToString(game.CurrentRoundWinner) << endl;
    cout << "----------------------------\n\n";
}

// update game statistics after each round
void UpdateGameInfo(GameInfo &game)
{
    game.CurrentRound++;
    game.LeftRounds--;

    if (game.CurrentRoundWinner == enWinner::Human)
        game.HumanWinnings++;
    else if (game.CurrentRoundWinner == enWinner::Computer)
        game.ComputerWinnings++;
    else
        game.DrawRounds++;
}

// Fill screen with a givin color
void ChangeScreenColor(enScreen color)
{
    switch (color)
    {
    case enScreen::Red:
        system("color C0");
        break;
    case enScreen::Green:
        system("color A0");
        break;
    case enScreen::Blue:
        system("color 90");
        break;
    default:
        system("color 7");
    }
}

// Take actions upon lose
void LoseActions()
{
    ChangeScreenColor(enScreen::Red);
    Beep(500, 800); // ring a bell
}

// Take actions upon win
void WinActions()
{
    ChangeScreenColor(enScreen::Green);
}

// Take actions upon draw
void TieActions()
{
    ChangeScreenColor(enScreen::Blue);
}

// Apply changes based on round result
void ApplyActions(enWinner winner)
{
    if (winner == enWinner::Human)
        WinActions();
    else if (winner == enWinner::Computer)
        LoseActions();
    else
        TieActions();
}

/*
 * @param: round number
 * execute complete round
 */
void PlayRound(GameInfo &game)
{
    cout << "\nRound [" << game.CurrentRound << "] begins:" << endl;
    game.HumanChoice = ReadPlayerChoice();
    game.ComputerChoice = RandomChoice();
    game.CurrentRoundWinner = DetermineRoundWinner(game.HumanChoice, game.ComputerChoice);

    PrintRoundInfo(game);
    ApplyActions(game.CurrentRoundWinner);
    UpdateGameInfo(game);
}

// set the winner in the game structure
void SetGameWinner(GameInfo &game)
{
    if (game.HumanWinnings > game.ComputerWinnings)
        game.GameWinner = enWinner::Human;
    else if (game.HumanWinnings < game.ComputerWinnings)
        game.GameWinner = enWinner::Computer;
    else
        game.GameWinner = enWinner::Tie;
}

// Print Final Game Statistics
void PrintFinalResult(GameInfo game)
{
    PrintGameOver();
    cout << Tabs(3) << "---------------------- [Game Results ] -------------------------\n\n";
    cout << Tabs(3) << "Game Rounds\t\t: " << (game.CurrentRound - 1) << endl; // cuz current round is the next round after the game is finished
    cout << Tabs(3) << "Your Winning times\t: " << game.HumanWinnings << endl;
    cout << Tabs(3) << "Computer Winning times\t: " << game.ComputerWinnings << endl;
    cout << Tabs(3) << "Draw times\t\t: " << game.DrawRounds << endl;
    cout << Tabs(3) << "Final Winner\t\t: " << ToString(game.GameWinner) << endl;
    cout << Tabs(3) << "----------------------------------------------------------------\n\n";
}

// Play a Complete Game
void PlayNewGame()
{
    GameInfo game; // object to track game information
    game.LeftRounds = ReadRoundsNumber();

    while (game.LeftRounds > 0)
    {
        PlayRound(game); // play a new round
    }
    
    Sleep(1900);         // to see the result of the last round before displaying the final results
    SetGameWinner(game); // assing the winner of the game
    ApplyActions(game.GameWinner); // change secreen color based on game winner
    PrintFinalResult(game);
}

//
void StartGame()
{
    string playAgain;
    do
    {
        ResetConsole();
        PlayNewGame(); // a complete game

        cout << "\nDo you want to play again ? [Y/N]\n >> ";
        cin >> playAgain;

    } while (playAgain == "Y" || playAgain == "y" || playAgain == "1");
}
