#include "ReferenceCountedObject.h"

ReferenceCountedObject::ReferenceCountedObject() : ReferenceCount(1)
{
	
}

ReferenceCountedObject::~ReferenceCountedObject()
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
