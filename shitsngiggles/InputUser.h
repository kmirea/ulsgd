/* 
 * File:   InputUser.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:19 PM
 */

#ifndef INPUTUSER_H
#define	INPUTUSER_H

#include "Types.h"

class World;

class InputUser
{
	const World* world;

public:
	void registerInput( const u8 Key ); // TODO: Extend this to use more inputs
};

#endif	/* INPUTUSER_H */

