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
#include <irrlicht/irrlicht.h>

using namespace std;
using namespace irr;

struct Cell
{
	bool isSeen;
	bool isFlag;
	int adjacentMineCount;	// -1 is a mine
	scene::ISceneNode* scenenode;
};

vector< vector<Cell> > MineField;
int NumMines;

void fillField();
bool markCell( int Row, int Column, bool SetFlag = false );	// Returns true if cell mark did not cause game over.
bool printField(); // Returns true if game has not ended.

IrrlichtDevice* device = NULL;
scene::ICameraSceneNode* cam = NULL;

int main()
{
	cout << "Welcome to MineSweeper!" << endl 
			<< "This game is limited to a field of 10x10 cells." << endl
			<< "You may play with as few as 1 or as many as 99 mines." << endl
			<< "\tPlease specify the number of mines you would like to play with: ";
	cin >> NumMines;
	
	while( NumMines <=0 || NumMines >=100 )
	{
		cout << "Wrong number of mines, please try again: ";
		cin >> NumMines;
	}
	
	fillField();
	
	while( printField() )
	{
		int Row = 0, Col = 0;
		cout << "Select Row: ";
		cin >> Row;
		cout << "Select Column: ";
		cin >> Col;
		int sel = 0;
		while( sel !=1 && sel != 2 )
		{
			cout << "Select: " << endl
				<< "\t(1) Flag Cell" << endl
				<< "\t(2) Uncover Cell" << endl;
			cin >> sel;
		}
		
		if( !markCell(Row, Col, sel==1?true:false) )
		{
			printField();
			cout << "Aww, too bad :(" << endl;
			break;
		}
	}
	
	char replay=0;
	
	while( replay !='y' && replay!='n' )
	{
		cout << "Game over. Play again? (y/n): ";
		cin >> replay;
	}
	
	for( int i=0; i<10; i++ )
	{
		for( int j=0; j<10; j++ )
		{
			MineField[i][j].scenenode->remove();
		}
		MineField[i].clear();
	}
	cam->remove();
	device->closeDevice();
	device->run();
	
	if( replay == 'y' )
		return main();
	return 0;
}

void fillField()
{
	int CurMineCount = 0;
	
	device = createDevice(video::EDT_BURNINGSVIDEO, core::dimension2d<u32>(600,400));
	device->getSceneManager()->setAmbientLight(video::SColorf(1,1,1));
	cam = device->getSceneManager()->addCameraSceneNode();
	cam->setPosition(core::vector3df(5,5,-15));
	cam->setTarget(core::vector3df(5,5,0));
	
	for( int Row=0; Row<10; Row++ )
	{
		MineField.push_back( vector<Cell>() );
		for( int Col=0; Col<10; Col++ )
		{
			MineField[Row].push_back( Cell() );
			MineField[Row][Col].isFlag = false;
			MineField[Row][Col].isSeen = false;
			MineField[Row][Col].scenenode = device->getSceneManager()->addEmptySceneNode();
		}
	}
	
	while( CurMineCount < NumMines )
	{
		int X = rand()%10, Y = rand()%10;
		
		if( MineField[X][Y].adjacentMineCount != -1 )
		{
			MineField[X][Y].adjacentMineCount = -1;
			CurMineCount++;
		}
	}
	
	for( int Row=0; Row<10; Row++ )
	{
		for( int Col=0; Col<10; Col++ )
		{
			if( MineField[Row][Col].adjacentMineCount == -1 )
			{
				for( int i=0; i<8; i++ )
				{
					switch(i)
					{
					case 0:	// East
						if( Col < 9 )
							MineField[Row][Col+1].adjacentMineCount += MineField[Row][Col+1].adjacentMineCount>=0?1:0;
						break;
					case 1: // NorthEast
						if( Row > 0 && Col < 9 )
							MineField[Row-1][Col+1].adjacentMineCount += MineField[Row-1][Col+1].adjacentMineCount>=0?1:0;
						break;
					case 2: // North
						if( Row > 0 )
							MineField[Row-1][Col].adjacentMineCount += MineField[Row-1][Col].adjacentMineCount>=0?1:0;
						break;
					case 3: // NorthWest
						if( Row > 0 && Col > 0 )
							MineField[Row-1][Col-1].adjacentMineCount += MineField[Row-1][Col-1].adjacentMineCount>=0?1:0;
						break;
					case 4: // West
						if( Col > 0 )
							MineField[Row][Col-1].adjacentMineCount += MineField[Row][Col-1].adjacentMineCount>=0?1:0;
						break;
					case 5: // SouthWest
						if( Row < 9 && Col > 0 )
							MineField[Row+1][Col-1].adjacentMineCount += MineField[Row+1][Col-1].adjacentMineCount>=0?1:0;
						break;
					case 6: // South
						if( Row < 9 )
							MineField[Row+1][Col].adjacentMineCount += MineField[Row+1][Col].adjacentMineCount>=0?1:0;
						break;
					case 7: // SouthEast
						if( Row < 9 && Col < 9 )
							MineField[Row+1][Col+1].adjacentMineCount += MineField[Row+1][Col+1].adjacentMineCount>=0?1:0;
						break;
					}
				}
			}
		}
	}
}

bool markCell( int Row, int Column, bool SetFlag )	// Returns true if cell mark did not cause game over.
{
//	if( Row < 0 || Row > 9 || Row < 0 || Column > 9 )
//		return true;
	
//	printField();
	
	if( SetFlag )			// attempting to flag/unflag cell
	{
		if( MineField[Row][Column].isSeen )
			return true;
		
		MineField[Row][Column].isFlag = MineField[Row][Column].isFlag ? false : true;
		return true;
	}
	else					// attempting to uncover cell
	{
		if( MineField[Row][Column].isFlag )
			return true;
		
		if( MineField[Row][Column].isSeen )
			return true;
		
		bool isMineSeen = false;
		
		switch( MineField[Row][Column].adjacentMineCount )
		{
		case -1:
			MineField[Row][Column].isSeen = true;
			return false;
		case 0:
			MineField[Row][Column].isSeen = true;
			for( int i=0; i<8; i++ )
			{
				switch(i)
				{
				case 0:	// nw
					if( Row > 0 && Column > 0 )
					{
						isMineSeen = markCell( Row-1, Column-1, false ) ? isMineSeen : true;
					}
					break;
				case 1:	// n
					if( Row > 0  )
					{
						isMineSeen = markCell( Row-1, Column, false ) ? isMineSeen : true;
					}
					break;
				case 2:	// ne
					if( Row > 0 && Column < 9 )
					{
						isMineSeen = markCell( Row-1, Column+1, false ) ? isMineSeen : true;
					}
					break;
				case 3:	// w
					if( Column > 0 )
					{
						isMineSeen = markCell( Row, Column-1, false ) ? isMineSeen : true;
					}
					break;
				case 4:	// e
					if( Column < 9 )
					{
						isMineSeen = markCell( Row, Column+1, false ) ? isMineSeen : true;
					}
					break;
				case 5:	// sw
					if( Row < 9 && Column > 0 )
					{
						isMineSeen = markCell( Row+1, Column-1, false ) ? isMineSeen : true;
					}
					break;
				case 6:	// s
					if( Row < 9 )
					{
						isMineSeen = markCell( Row+1, Column, false ) ? isMineSeen : true;
					}
					break;
				case 7:	// se
					if( Row < 9 && Column < 9)
					{
						isMineSeen = markCell( Row+1, Column+1, false ) ? isMineSeen : true;
					}
				}
			}
			return !isMineSeen;
		default:
			MineField[Row][Column].isSeen = true;
			return true;
		}
	}
}

bool printField() // Returns true if game has not ended.
{
	bool isMineVisible = false;
	int hidden_tiles = 0;
	
	cout << "+  0 1 2 3 4 5 6 7 8 9" << endl;
	for( int i=0; i<11; i++ )
	{
		cout << ' ' << ' ';
		for( int j=0; j<11; j++ )
		{
			if( i == 0 )
			{
				if( j == 0 )
					cout << '+' << '-';
				else if( j == 10 )
					cout << '+' << endl;
				else
					cout << '+' << '-';
			}
			else if( i == 10 )
			{
				if( j == 0 )
					cout << '+' << '-';
				else if( j == 10 )
					cout << '+' << endl;
				else
					cout << '+' << '-';
			}
			else
			{
				if( j == 0 )
					cout << '+' << '-';
				else if( j == 10 )
					cout << '+' << endl;
				else
					cout << '+' << '-';
			}
		}
		
		if( i == 10 ) break;
		
		cout << i << ' ';
		
		for( int j=0; j<10; j++ )
		{
			
			MineField[i][j].scenenode->remove();
			cout << '|';
			
			switch( MineField[i][j].adjacentMineCount )
			{
			case -1:
				if( MineField[i][j].isFlag )
				{
					MineField[i][j].scenenode = device->getSceneManager()->addBillboardTextSceneNode(0, L"F", NULL, 
																									 core::dimension2df(1,1));
					cout << 'F';
					hidden_tiles++;
				}
				else if( MineField[i][j].isSeen )
				{
					MineField[i][j].scenenode = device->getSceneManager()->addBillboardTextSceneNode(0,L"*", NULL, 
																									 core::dimension2df(1,1));
					cout << '*';
					isMineVisible = true;
				}
				else
				{
					MineField[i][j].scenenode = device->getSceneManager()->addCubeSceneNode(1);
					cout << '#';
					hidden_tiles++;
				}
				break;
			case 0:
				if( MineField[i][j].isFlag )
				{
					MineField[i][j].scenenode = device->getSceneManager()->addBillboardTextSceneNode(0, L"F", NULL, 
																									 core::dimension2df(1,1));
					cout << 'F';
					hidden_tiles++;
				}
				else if( MineField[i][j].isSeen )
				{
					MineField[i][j].scenenode = device->getSceneManager()->addEmptySceneNode();
					cout << ' ';
				}
				else
				{
					MineField[i][j].scenenode = device->getSceneManager()->addCubeSceneNode(1);
					cout << '#';
					hidden_tiles++;
				}
				break;
			default:
				if( MineField[i][j].isFlag )
				{
					MineField[i][j].scenenode = device->getSceneManager()->addBillboardTextSceneNode(0, L"F", NULL, 
																									 core::dimension2df(1,1));
					cout << 'F';
					hidden_tiles++;
				}
				else if( MineField[i][j].isSeen )
				{
					MineField[i][j].scenenode = device->getSceneManager()->addBillboardTextSceneNode(0, 
															core::stringw(MineField[i][j].adjacentMineCount).c_str(), NULL, 
																									 core::dimension2df(1,1));
					cout << MineField[i][j].adjacentMineCount;
				}
				else
				{
					MineField[i][j].scenenode = device->getSceneManager()->addCubeSceneNode(1);
					cout << '#';
					hidden_tiles++;
				}
				break;
			}
			MineField[i][j].scenenode->setPosition(core::vector3df(j,9-i,0));
			MineField[i][j].scenenode->setScale(core::vector3df(0.9, 0.9, 0.9));
			if( j == 9 )
				cout << '|' << endl;
		}
	}
	cout << "  ---------------------" << endl;
	
	device->run();
	device->getVideoDriver()->beginScene(true, true, video::SColor(255,0,0,255) );
	device->getSceneManager()->drawAll();
	device->getVideoDriver()->endScene();
	
	return !isMineVisible && hidden_tiles > NumMines;
}
