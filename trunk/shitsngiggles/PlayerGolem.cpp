#include "PlayerGolem.h"
#include "BinarySearchTree.h"

#define PLAYER_GOLEM_TEXTURE "media/player.png"

PlayerGolem::PlayerGolem( Room* room, const vector<u32>& Position, const vector<u32>& Velocity, E_ELEMENT_TYPE Element )
 : Golem( room, Position, Velocity, Element )
{

}

PlayerGolem::~PlayerGolem()
{

}

bool PlayerGolem::shoot(DIRECTION Direction)
{
	return false;
}

void PlayerGolem::pass(const u32 GameTime)
{

}