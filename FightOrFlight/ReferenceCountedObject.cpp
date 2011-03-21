#include "ReferenceCountedObject.h"

ReferenceCountedObject::ReferenceCountedObject() : ReferenceCount(1)
{

}

ReferenceCountedObject::~ReferenceCountedObject()
{

}

string ReferenceCountedObject::getDebugInfo()
{
	return string("ReferenceCounted");
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
