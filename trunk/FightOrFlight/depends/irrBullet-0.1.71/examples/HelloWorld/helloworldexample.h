#ifndef __HELLO_WORLD_EXAMPLE_H_INCLUDED__
#define __HELLO_WORLD_EXAMPLE_H_INCLUDED__

#include "../framework/exampleframework.h"
#include <irrlicht/irrString.h>
#include <irrlicht/irrTypes.h>


class IRigidBody;

class CHelloWorldExample : public CExampleFramework
{
    public:
        CHelloWorldExample();
        virtual ~CHelloWorldExample();

        virtual void runExample();

        virtual bool OnEvent(const irr::SEvent& event);

        void createBoxes();

        void createGround();

    private:
        irr::u32 rows;
        irr::u32 columns;


};

#endif // __HELLO_WORLD_EXAMPLE_H_INCLUDED__
