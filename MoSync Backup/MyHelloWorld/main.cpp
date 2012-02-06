#include <MAUtil/Moblet.h>
#include <MAUtil/util.h>
#include <conprint.h>

using namespace MAUtil;

/**
 * A Moblet is a high-level class that defines the
 * behaviour of a MoSync program.
 */
class MyMoblet : public Moblet
{
public:

	MyMoblet()
	{
		maSetColor(0xFFFFFF);
		maDrawText(0, 32, "Hello, World!");
		maUpdateScreen();

	}

	void keyPressEvent( int keyCode, int nativeCode )
	{
		if( keyCode == MAK_0 || keyCode == MAK_BACK || keyCode == MAK_SOFTRIGHT )
		{
			close();
		}

		maSetColor(0);
		maFillRect(0, 64, 2000, 96);
		maUpdateScreen();
		maSetColor(0xFFFFFF);
		maDrawText(0, 64, integerToString(keyCode, 10).c_str() );
		maUpdateScreen();
	}

	void keyReleaseEvent( int keyCode, int nativeCode )
	{

	}

    /**
     * Called when the screen is touched.
     */
    void pointerPressEvent(MAPoint2d point)
    {
        // Print the x and y coordinate.
        //printf("You touched: %i %i", point.x, point.y);

        maSetColor(0x000000);
        maFillRect(0, 96, 2000, 128);
        maUpdateScreen();
        maSetColor(0xFFFFFF);
        maDrawText(0, 96, ((integerToString(point.x, 10)) + " "
                + (integerToString(point.y, 10))).c_str());
        maUpdateScreen();

    }
};

/**
 * Entry point of the program. The MAMain function
 * needs to be declared as extern "C".
 */
extern "C" int MAMain()
{
	Moblet::run(new MyMoblet());
	return 0;
}
