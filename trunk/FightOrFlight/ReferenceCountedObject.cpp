#include "ReferenceCountedObject.h"

ReferenceCountedObject::ReferenceCountedObject() : ReferenceCount(0)
{
	
}

ReferenceCountedObject::~ReferenceCountedObject()
{

}

void ReferenceCountedObject::grab()
{
	++ReferenceCount;
	cout << ptr(this) << " ref cnt: " << ReferenceCount << endl;
}

void ReferenceCountedObject::drop()
{
	--ReferenceCount;
	cout << ptr(this) << " ref cnt: " << ReferenceCount << endl;
	if( ReferenceCount == 0 )
		delete this;
}
