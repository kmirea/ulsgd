#include "ReferenceCountedObject.h"

ReferenceCountedObject::ReferenceCountedObject() : ReferenceCount(1)
{

}

ReferenceCountedObject::ReferenceCountedObject(const ReferenceCountedObject& Other) :
	ReferenceCount(1)
{

}

void ReferenceCountedObject::grab()
{
	++ReferenceCount;
}

void ReferenceCountedObject::drop()
{
	--ReferenceCount;
	if( ReferenceCount == 0 )
		delete this;
}
