#ifndef MINESWEEPER_H_INCLUDED
#define MINESWEEPER_H_INCLUDED

#include "minesweep.h"
using namespace std;
class mineSweeper
{
	public:
	// Constructor: Makes the minesweeper array and initializes it.
		mineSweeper(int number)
		{
		    MaxRow = 10;
            MaxCol = 6;
            // Maximun row and columns.
		    mines = number;
		    // Number of mines = number determined by user.
		    for(int row = 0; row < MaxRow; row++)
                for(int col = 0; col < MaxCol; col++)
                {
                    array[row][col].adjMines = 0;
                    array[row][col].display = 'C';
                    array[row][col].mine = false;
                    array[row][col].covered = true;
                    array[row][col].flag = false;
                }
            // Initializes array components.
		    initialize();
		} // End constructor

		// Function Display
		// Displays the minesweeper array.
		void display()
		{
		    // For loop to go through the rows in the minesweeper array.
		    for(int row = 0; row < MaxRow; row++)
		    {
		        // For loop to go through the columns in the minesweeper array.
                for(int col = 0; col < MaxCol; col++)
                {
                    // Displays a F or C if it's been flagged or is still covered.
                    if(array[row][col].covered == true || array[row][col].flag == true)
                        cout << array[row][col].display << "    ";

                    // Displays a M if the cell has a mine.
                    else if(array[row][col].mine == true)
                        cout << "M    ";
                    // Displays the number of adjacent mines around the cell.
                    else
                        cout << array[row][col].adjMines << "    ";
                } // End for loop
                cout << endl;
		    } // End for loop
		}
		// End Display

		// Function Uncover
		// Uncovers a cell in the array.
		bool uncover(int row, int col)
		{
		    // Uncovers a cell in the array.
		    array[row][col].covered = false;
		    // If it's a mine, end the game.
		    if(array[row][col].mine)
		    {
		        // Show board
		        display();
		        cout << "You lose!" << endl;
		        // Return true to end game.
		        return true;
		    } // End if

		    // If there's a 0 in a cell, show adjacent cells that
		    // don't contain a mine.
		    if(array[row][col].adjMines == 0)
            {
                ShowZeros(row, col);
            } // End if

		    // Return false to keep playing.
		    return false;
		}
		// End uncover

		// Function flag
		// Flags a cell in the array.
		void flag(int row, int col)
		{
		    // Changes the cell from a covered state to a flagged state.
		    array[row][col].covered = false;
		    array[row][col].flag = true;
		    array[row][col].display = 'F';
		}
		// End flag

		// Function checkField
		// Checks to see if all cells have been uncovered and the mines flagged.
		bool checkField()
		{
		    // Integer to check the mines that been flagged so far.
		    int minesFlagged = 0;
		    // For loop to go through the rows in the minesweeper array.
		    for(int row = 0; row < MaxRow; row++)
                // For loop to go through  the columns in the minesweeper array.
                for(int col = 0; col < MaxCol; col++)
                {
                    // Returns true if a cell is still covered to continue play.
                    if(array[row][col].covered)
                        return false;
                    // minesFlagged + 1 if the mine is flagged
                    else if(array[row][col].flag && array[row][col].mine)
                        minesFlagged++;
                } // End for loop
            // If statement that checks if the mines that has been flagged
            // is equal to the total mines and returns true to end the game.
            if(minesFlagged == mines)
            {
                cout << "YOU WIN!!!" << endl;
                return true;
            } // End if
            // Else return false to continue game.
            else
                return false;
		}
		// End checkField

		// Function showField
		// Function to show all cells in the minesweeper array.
		void showField()
		{
		    // For loop to go through the rows in the minesweeper array.
		    for(int row = 0; row < MaxRow; row++)
		    {
		        // For loop to go through the columns in the minesweeper array.
		        for(int col = 0; col < MaxCol; col++)
                {
                    // Displays a M if the cell contains a mine.
                    if(array[row][col].mine)
                        cout << "M    ";
                    // Displays the number for adjacent mines.
                    else
                        cout << array[row][col].adjMines << "    ";
                }
                cout << endl;
		    }
		    // Pauses the system for the user to see.
		    system("pause>nul");
		}
		// End showField

		// Function unFlag
		// Used to unflag a cell in the minesweeper array.
		void unFlag(int row, int col)
		{
		    array[row][col].flag = false;
		    array[row][col].covered = true;
		    array[row][col].display = 'C';
		}
		// End unFlag

    protected:

    // Function initialize
    // Function to place the mines in the array.
    void initialize()
    {
        // Bool finishMines to check if all the mines have
        // been placed.
        bool finishMines = false;
        // Int row and col assigned numbers depending on how big
        // the minesweeper array is. Int placedMines will be used to
        // check how many mines have been placed.
        int row, col, placedMines = 0;
        // While loop to place mines.
        while(!finishMines)
        {
            // Assigns a random number to row and col depending how
            // big the minesweeper array is.
            row = rand() % MaxRow;
            col = rand() % MaxCol;
            // If statement to check if cell has a mine already.
            if(array[row][col].mine == false)
            {
                // Places mine.
                array[row][col].mine = true;
                // Updates the adjacent cells in the minesweeper array.
                updateArray(row, col);
                placedMines++;
            } // End if
            // If statement to check if all the mines have been placed.
            if(placedMines == mines)
                finishMines = true;
        } // End while loop
    }
    // End initialize

    // Function updateArray
    // Updates the adjacent cells to a mine.
    void updateArray(int row, int col)
    {
        // For loops to go through the adjacent cells of the mine.
        for(int x = -1; x <= 1; x++)
        {
            for(int y = -1; y <= 1; y++)
            {
                // If statements to check that program doesn't go out
                // of array boundaries.
                if( (row + x) > -1 && (row + x) < MaxRow)
                {
                    if( (col + y) > -1 && (col + y) < MaxCol)
                    {
                        array[row + x][col + y].adjMines++;
                    } // End if
                } // End if
            } // End for loop
        } // End for loop
    }
    // End updateArray

    // Function ShowZeros
    // Function to display adjacent cells to a cell that
    // contains 0 adjacent mines.
    void ShowZeros(int row, int col)
    {
        // For loops to go through the adjacent cells of the 0 cell.
        for(int x = -1; x <= 1; x++)
        {
            for(int y = -1; y <= 1; y++)
            {
                // If statements to check that program doesn't go out
                // of array boundaries.
                if( (row + x) > -1 && (row + x) < MaxRow)
                {
                    if( (col + y) > -1 && (col + y) < MaxCol)
                    {
                        // If statement to check to see if the cell has already been uncovered.
                        if(!array[row + x][col + y].mine && array[row + x][col + y].covered)
                        {
                            // Uncover the cell.
                            array[row + x][col + y].covered = false;

                            // If statement to check if the cell has no adjacent mines.
                            // Passes in the new row and column if it contains no adjacent
                            // mines.
                            if(array[row + x][col + y].adjMines == 0)
                                ShowZeros(row + x, col + y);
                        } // End if
                    } // End if
                } // End if
            } // End for loop
        } // End for loop
    }

	private:
        // Int mines is used to hold the number of mines.
        // Int MaxRow used to keep track of how many rows are in the minesweeper.
        // Int MaxCol used to keep track of how many columns are in the minesweeper.
        int mines, MaxRow, MaxCol;
        // Minesweeper array
        cell array[10][6];
};


#endif // MINESWEEPER_H_INCLUDED
