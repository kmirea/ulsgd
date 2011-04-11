#ifndef __AFFECTORS_EXAMPLE_H_INCLUDED__
#define __AFFECTORS_EXAMPLE_H_INCLUDED__

#include "../framework/exampleframework.h"
#include <irrlicht/irrString.h>
#include <irrlicht/irrTypes.h>


class IRigidBody;

class CAffectorsExample : public CExampleFramework
{
    public:
        CAffectorsExample();
        virtual ~CAffectorsExample();

        virtual void runExample();

        virtual bool OnEvent(const irr::SEvent& event);

        void createGround();

        void createBoxes();

        void makeAffector(IRigidBody* const body);

    private:
        irr::u32 AffectorType;
};

#endif // __AFFECTORS_EXAMPLE_H_INCLUDED__