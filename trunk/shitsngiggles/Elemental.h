/* 
 * File:   Elemental.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:05 PM
 */

#ifndef ELEMENTAL_H
#define	ELEMENTAL_H

#include "Object.h"

#define OBJECT_TYPE_ELEMENTAL 0x0001

enum E_ELEMENT_TYPE
{
	EET_NULL = 0,
	EET_FIRE,
	EET_WATER,
	EET_EARTH,
	EET_METAL,
	EET_ICE,
	EET_PLANT,
	EET_COUNT,
	EET_FORCE_8_BIT = 255
};

class Elemental : public Object
{
public:
	Elemental( Room* room, const vector<u32>& Position, const vector<u32>& Velocity, E_ELEMENT_TYPE Element );

	virtual ~Elemental() = 0;

	E_ELEMENT_TYPE getElementyType() const;
protected:
	E_ELEMENT_TYPE ElementType;

	E_ELEMENT_TYPE NextElement;
};

#endif	/* ELEMENTAL_H */

