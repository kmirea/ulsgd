/* 
 * File:   main.cpp
 * Author: chris
 *
 * Created on October 19, 2011, 6:15 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

/*
 * 
 */

typedef unsigned int u32;
typedef int s32;

vector< vector<bool> > Map;

void GenerateMap( u32 X, u32 Y, u32 mines );
bool SelectCoord( u32 X, u32 Y );

int main()
{
	bool isFinished = false;
	bool isWon = true;
	
	u32 mineCount;
	u32 xDim, yDim;
	
	cout << "Please select X and Y Dimensions: " << endl;
	cout << "X: ";
	cin >> xDim;
	cout << "Y: ";
	cin >> yDim;
	
	cout << "How many mines would you like? ";
	cin >> mineCount;
	
	if( xDim * yDim <= mineCount )
	{
		cout << "Too many mines, or too small a map :(" << endl;
		cout << "Restarting..." << endl;
		return main();
	}
	
	cout << "Generating Map..." << endl;
	
	GenerateMap( xDim, yDim, mineCount );
	
	while( !isFinished )
	{
		
	}
	
	bool playagain = false;
	
	if( isWon )
		cout << "You Won! ";
	else
		cout << "Too bad. ";
	cout << "The game has finished. Would you like to play again (y/n)? ";
	
	return 0;
}

void GenerateMap( u32 X, u32 Y, u32 mines )
{
	Map.resize(X, false);
	for( u32 i=0; i<Map.size(); i++ )
		Map[i].resize(Y, false);
	
	for( u32 i=0; i<Map.size(); i++ )
	{
		for( u32 j=0; j<Map[i].size(); j++ )
		{
			Map[i][j] = rand()%2;
			if( Map[i][j] )
				mines--;
			if( mines == 0 )
				return;
		}
	}
}

bool SelectCoord( u32 X, u32 Y )
{
	
}