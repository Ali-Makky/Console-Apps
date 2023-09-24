#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>
#include <ctime>

using namespace std;

// the range of valid ranges of the game
#define MIN 1  // minimum number of questions
#define MAX 10 // maximum number of questions
const int Easy_Range[]{1, 10};
const int Med_Range[]{11, 100};
const int Hard_Range[]{101, 1000};

// **** Enums ******//
enum enLevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    Mix = 4
};
enum enOpType
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    mix = 5
};
enum enScreen
{
    Red,
    Green
};

// **** Structures ****//
struct stEquation
{
    short LeftOp; // left operand
    short RightOp;
    enOpType Operation;
};
struct stQuestion
{
    stEquation Equation;
    float CorrectAnswer;
    float UserAnswer;
    bool AnsweredCorrectly = false;
};
struct stQuiz
{
    stQuestion QuestionsList[MAX];
    short TotalQuestionsNum;
    short CurrentQuestionNum = 1;
    short TotalCorrectAns = 0; // number of correct answers
    short TotalWrongAns = 0;
    bool Pass; // final result
    enLevel Level;
    enOpType OpType;
};

// **** ToString **** //
inline const char *ToString(enOpType o)
{
    switch (o)
    {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mul:
        return "*";
    case Div:
        return "/";
    default:
        return "Mix (+ - * /)";
    }
}
inline const char *ToString(enLevel l)
{
    switch (l)
    {
    case Easy:
        return "Easy";
    case Med:
        return "Med";
    case Hard:
        return "Hard";
    default:
        return "Mix";
    }
}

// **** Functions *******//

/*
 * Ask user to enter how many questions in the game/quiz
 * @return: number of questions
 */
short HowManyQuestions()
{
    cout << "\nHow many questions do you want to solve [" << MIN << ", " << MAX << "]?\nEnter >> ";
    short questions;
    cin >> questions;
    while (questions < MIN || questions > MAX)
    {
        cout << "Questions must be in range [" << MIN << ", " << MAX << "] !." << endl
             << "Please try again." << endl
             << "\nHow many questions do you want to solve [" << MIN << ", " << MAX << "]?\nEnter >> ";
        cin >> questions;
    }

    return questions;
}

/*
 * Ask user to enter the questions level
 * @return: difficulty level
 */
enLevel ChooseLevel()
{
    short level;
    do
    {
        cout << "Enter questions level: [1]Easy, [2]Med, [3]Hard, [4]Mix ? \n>> ";
        cin >> level;
    } while (level < 1 || level > 4);

    return enLevel(level);
}

/*
 * Ask user to enter questions type
 * @return: type of questions
 */
enOpType ChooseOpType()
{
    short opType;
    do
    {
        cout << "Enter operations type: [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix ? \n>> ";
        cin >> opType;
    } while (opType < 1 || opType > 5);

    return enOpType(opType);
}

/*
 * Ask user to enter his answer of a question
 * @return: user answer
 */
short ReadPlayerAnswer()
{
    short ans;
    cout << ">> ";
    cin >> ans;
    return ans;
}

/*
 * range to choose from
 * @return: random integer in the specified range
 */
int RandIntIn(int start, int end)
{
    int number = (rand() % (end - start + 1)) + start;
    return number;
}

/*
 * @input: equation struct
 * @return: result of the given equation
 */
float ComputeResult(stEquation equation)
{
    switch (equation.Operation)
    {
    case enOpType::Add:
        return equation.LeftOp + equation.RightOp;
    case enOpType::Sub:
        return equation.LeftOp - equation.RightOp;
    case enOpType::Mul:
        return equation.LeftOp * equation.RightOp;
    default:
        return round((float(equation.LeftOp) / equation.RightOp) * 100.0) / 100.0; // round to 2 decimal places
    }
}

/*
 * @input: questions level
 * @return: random number in level range
 */
short GenerateRandOperand(enLevel level)
{
    switch (level)
    {
    case Easy:
        return RandIntIn(Easy_Range[0], Easy_Range[1]);
    case Med:
        return RandIntIn(Med_Range[0], Med_Range[1]);
    case Hard:
        return RandIntIn(Hard_Range[0], Hard_Range[1]);
    default:
        return GenerateRandOperand((enLevel)RandIntIn(1, 3)); // recusrive call to choose [easy, med, hard] each one has equal chance
    }
}

/*
 * @input: user answer and correct result
 * @return: true if equal, false otherwise
 */
bool EvaluateAnswer(float correctAns, float usrAns)
{
    return (correctAns == usrAns);
}

/*
 * used when the user choose mix operation types
 * @return: random operation type
 */
enOpType GenerateRandOperation()
{
    return enOpType(RandIntIn(1, 4));
}

/*
 * @input: both question's level and type
 * @return: filled equation struct
 */
stEquation CreateEquation(enLevel level, enOpType type)
{
    stEquation equation; // new instance of the struct
    equation.LeftOp = GenerateRandOperand(level);
    equation.RightOp = GenerateRandOperand(level);
    equation.Operation = (type != enOpType::mix ? type : GenerateRandOperation());
    return equation;
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
///////////////////////////

// clean the console screen
void ResetConsole()
{
    system("cls");     // clear the console
    system("color 7"); // default colors
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
    default:
        system("color 7");
    }
}

// Take actions upon lose
void LoseActions()
{
    ChangeScreenColor(enScreen::Red);
}

// Take actions upon win
void WinActions()
{
    ChangeScreenColor(enScreen::Green);
}

// print question information
void PrintQuestionInfo(stQuiz quiz, stQuestion question)
{
    cout << "\n---Question[" << quiz.CurrentQuestionNum << "/" << quiz.TotalQuestionsNum << "]----\n\n";
    cout << question.Equation.LeftOp << endl;
    cout << question.Equation.RightOp << " " << ToString(question.Equation.Operation) << endl;
    cout << "\n---------------------\n";
}

// announce if the answer correct of wrong
void ApplyScreenChanges(stQuestion question)
{
    if (question.AnsweredCorrectly)
    {
        WinActions();
        cout << "Correct Answer :)\n";
    }
    else
    {
        LoseActions();
        cout << "Wrong Answer :(\n";
        cout << "The right answer is: " << question.CorrectAnswer << endl;
    }
}

// update game statistics after each round
void UpdateGameInfo(stQuiz &quiz, stQuestion question)
{
    quiz.CurrentQuestionNum++;
    if (question.AnsweredCorrectly)
        quiz.TotalCorrectAns++;
    else
        quiz.TotalWrongAns++;
}

// paly quation
void PlayQuestion(stQuiz quiz, stQuestion &question)
{
    PrintQuestionInfo(quiz, question);
    cin >> question.UserAnswer;
    question.AnsweredCorrectly = EvaluateAnswer(question.CorrectAnswer, question.UserAnswer);
    ApplyScreenChanges(question);
    cout << endl;
}

// print game over headr
void PrintGameOver()
{
    cout << Tabs(2) << "----------------------------------------------------------------\n\n";
    cout << Tabs(2) << "                  +++ G a m e   O v e r +++\n"
         << endl;
    cout << Tabs(2) << "----------------------------------------------------------------\n\n";
}

// set the pass/fail result
void SetFinalGrade(stQuiz &quiz)
{
    quiz.Pass = (quiz.TotalCorrectAns >= quiz.TotalWrongAns);
}

// print the pass/fail result
void PrintFinalResult(bool pass)
{
    cout << Tabs(2) << "---------------------- [Final Results ] -------------------------\n";
    if (pass)
        cout << Tabs(2) << "                            PASS :)\n";
    else
        cout << Tabs(2) << "                            Fail :(\n";
    cout << Tabs(2) << "-----------------------------------------------------------------\n";
}

// Print Final Game Statistics
void PrintFinalStat(stQuiz quiz)
{
    cout << Tabs(2) << "--------------------- [Game Statistics ] -----------------------\n\n";
    cout << Tabs(2) << "Number of Questions: " << (quiz.TotalQuestionsNum) << endl;
    cout << Tabs(2) << "Questions Level: " << ToString(quiz.Level) << endl;
    cout << Tabs(2) << "Operations Typs: " << ToString(quiz.OpType) << endl;
    cout << Tabs(2) << "Number of Right Answers: " << quiz.TotalCorrectAns << endl;
    cout << Tabs(2) << "Number of Wrong Answers: " << quiz.TotalWrongAns << endl;
    cout << Tabs(2) << "----------------------------------------------------------------\n\n";
}

// Fill the quiz with generated questions
void WirteQuizQuestions(stQuiz &quiz)
{
    for (short i = 0; i < quiz.TotalQuestionsNum; i++)
    {
        quiz.QuestionsList[i].Equation = CreateEquation(quiz.Level, quiz.OpType);
        quiz.QuestionsList[i].CorrectAnswer = ComputeResult(quiz.QuestionsList[i].Equation);
    }
}

// Initialze a new game with needed information
void InitGameInfo(stQuiz &quiz)
{
    quiz.TotalQuestionsNum = HowManyQuestions();
    quiz.Level = ChooseLevel();
    quiz.OpType = ChooseOpType();

    WirteQuizQuestions(quiz);
}

// Play a complete new math quiz
void PlayNewGame()
{
    stQuiz quiz; // new empty object to track game information
    InitGameInfo(quiz);

    for (short i = 0; i < quiz.TotalQuestionsNum; i++)
    {
        PlayQuestion(quiz, quiz.QuestionsList[i]); // play a new round
        UpdateGameInfo(quiz, quiz.QuestionsList[i]);
    }

    Sleep(1900); // to see the result of the last round before displaying the final results
    SetFinalGrade(quiz);
    if (quiz.Pass)
        WinActions();
    else
        LoseActions();
    // Information at the end of the game
    PrintGameOver();
    PrintFinalResult(quiz.Pass);
    PrintFinalStat(quiz);
}

// Run the game until stop flag
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

///////////////////////////////////

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
