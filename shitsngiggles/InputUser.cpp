#include "InputUser.h"


#include "World.h"

void InputUser::SendInput(const vector<u8>& input)
{
	for( u32 i=0; i<input.size(); i++ )
	{
		if( BST.searchData( input[i] ) != NULL )
			InputEvent( input[i] );
	}
}

void InputUser::registerInputVal(const u8 Key)
{
	if( BST.searchData( Key ) == NULL )
		BST.addNode( Key );
}

void InputUser::registerInput()
{
	world->RegisterInputUser(this);
}

InputUser::InputUser(World* W): world(W)
{
}
