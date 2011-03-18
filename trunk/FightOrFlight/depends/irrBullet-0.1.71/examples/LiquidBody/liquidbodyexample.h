#ifndef __LIQUID_BODY_EXAMPLE_H_INCLUDED__
#define __LIQUID_BODY_EXAMPLE_H_INCLUDED__

#include "../framework/exampleframework.h"
#include <irrString.h>
#include <irrTypes.h>
#include <irrbulletcommon.h>

class ISoftBody;


class CLiquidbodyExample : public CExampleFramework
{
    public:
        CLiquidbodyExample();
        ~CLiquidbodyExample();

        virtual void runExample();

        virtual bool OnEvent(const irr::SEvent& event);

    private:
        int softVersusSoft;
};

#endif // __LIQUID_BODY_EXAMPLE_H_INCLUDED__
