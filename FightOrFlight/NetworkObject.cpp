#include "NetworkObject.h"
#include "NetworkManager.h"

NetworkObject::NetworkObject( NetworkManager* Net, NETID NetID ) : ReferenceCountedObject(),
		Manager(Net), net_id(NetID), OutStream(NULL), InStream(NULL), MessageAvailable(false)
{
	InStream = Manager->getUpdateData( net_id );
}

NetworkObject::~NetworkObject()
{
	
}

NETID NetworkObject::getNetID() const
{
	return net_id;
}

bool NetworkObject::isMessageAvailable() const
{
	return MessageAvailable;
}

NetData* NetworkObject::getOutStream()
{
	MessageAvailable = false;
	return OutStream;
}

void NetworkObject::update()
{
	if( InStream != NULL )
	{
		InStream->drop();
		InStream = NULL;
	}
	InStream = Manager->getUpdateData( net_id );
}

NetData* NetworkObject::getInStream()
{
	return InStream;
}

void NetworkObject::sendData( NetData* Out )
{
	OutStream = Out;
	MessageAvailable = true;
}

string NetworkObject::getDebugInfo()
{
	return string("NetworkObject");
}
