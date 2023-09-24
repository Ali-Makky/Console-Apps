#include <iostream>
#include <string>
#include <ctime>
#include "lib.hpp"

using namespace std;

int main()
{
    srand((unsigned)time(NULL));

    StartGame(); // start rock-paper-scissors game

    return 0;
}
