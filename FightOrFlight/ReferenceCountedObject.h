/* 
 * File:   ReferenceCountedObject.h
 * Author: chris
 *
 * Created on March 18, 2011, 9:13 AM
 */

#ifndef REFERENCECOUNTEDOBJECT_H
#define	REFERENCECOUNTEDOBJECT_H

#include "Types.h"

// Provides a base type for objects to be automatically destroyed.
// It uses a count on its 'grab' and 'drop' methods, and destroys itself at 0

class ReferenceCountedObject
{
public:
	ReferenceCountedObject();
	ReferenceCountedObject(const ReferenceCountedObject& Other);
protected:
	virtual ~ReferenceCountedObject() = 0;

public:
	inline void grab();
	inline void drop();

private:
	u32 ReferenceCount;
};

#endif	/* REFERENCECOUNTEDOBJECT_H */

