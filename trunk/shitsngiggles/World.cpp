#include "World.h"
#include "Room.h"

irr::IrrlichtDevice* World::getIrrDevice() const
{
	return IrrDevice;
}

World::World()
{
    //TODO: set the current room to the hub in here
    
}

World::~World()
{
    
}
bool World::run()
{
    //CurrentRoom->Update();
    while(true)
    {
        //TODO:: scan the inputs of irrlicht
        prepass();
        pass();
        postpass();

    }
    return true;
}

void World::RegisterInputUser(InputUser* User)
{
    bool flag = false;

    if(!InputUserList.empty())
    {
        for(u32 i = 0; i < InputUserList.size(); i++)
        {
            if(User == InputUserList[i])
                flag = true;
        }
    }

    if(!flag)
    {
        InputUserList.push_back(User);
    }
}
void World::prepass(const u32 GameTime)
{

}
void World::pass(const u32 GameTime)
{

}

void World::postpass(const u32 GameTime)
{

}