#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Minesweeper.h"

using namespace std;

int main()
{
    srand( time(NULL) );
    int mines, row, col, choice;
    bool gameOver = false, loser = false;
    cout <<  "Enter number of mines: ";
    cin >> mines;

    mineSweeper Msweeper(mines);
    do
    {
        system("CLS");
        Msweeper.display();
        cout << "1. Uncover Cell" << endl;
        cout << "2. Flag Cell" << endl;
        cout << "3. Unflag Cell" << endl;
        cout << "4. Show Field" << endl;
        cout << "Choice: ";
        cin >> choice;
        if(choice == 1)
        {
            cout << "Enter row number (1 - 10): ";
            cin >> row;
            cout << "Enter col number (1 - 6): ";
            cin >> col;
            loser = Msweeper.uncover(row - 1, col - 1);
        }
        else if(choice == 2)
        {
            cout << "Enter row number (1 - 10): ";
            cin >> row;
            cout << "Enter col number (1 - 6): ";
            cin >> col;
            Msweeper.flag(row - 1, col - 1);
        }
        else if(choice == 3)
        {
            cout << "Enter row number (1 - 10): ";
            cin >> row;
            cout << "Enter col number (1 - 6): ";
            cin >> col;
            Msweeper.unFlag(row - 1, col - 1);
        }
        else
            Msweeper.showField();

        gameOver = Msweeper.checkField();
    }
    while(!gameOver && !loser);

    return 0;
}
