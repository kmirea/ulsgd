#include "Golem.h"

#define GOLEM_TEXTURE "media/golem.png"
#define GOLEM_LAYER -3

Golem::Golem(Room* room, const vector<u32>& Position, const vector<u32>& Velocity, E_ELEMENT_TYPE Element)
: Elemental( room, Position, Velocity, Element )
{
	
}

Golem::~Golem()
{
	
}

bool Golem::isDead()
{
	return false;
}

void Golem::prepass(const u32 GameTime)
{
    //handle the pre updating in here
}

void Golem::pass(const u32 GameTime)
{
    //handle the update in here
}

void Golem::postpass(const u32 GameTime)
{
    //handle the execution of the update in here
}

void Golem::handleCollision(Object* Other)
{
    //nandle the collision that occurs
}