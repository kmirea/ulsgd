#include "NetworkObject.h"
#include "NetworkManager.h"

NetworkObject::NetworkObject( NetworkManager* Net, NETID NetID ) : ReferenceCountedObject(),
		Manager(Net), net_id(NetID), OutStream(NULL), InStream(NULL), MessageAvailable(false)
{
	Manager->grab();
	InStream = Manager->getUpdateData( net_id );
}

NetworkObject::~NetworkObject()
{
	Manager->drop();
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
	InStream->grab();
}

NetData* NetworkObject::getInStream()
{
	NetData* ret = InStream;
	InStream = NULL;
	return ret;
}

void NetworkObject::sendData( NetData* Out )
{
	OutStream = Out;
	OutStream->grab();
	MessageAvailable = true;
}

string NetworkObject::getDebugInfo() const
{
	return string("NetworkObject");
}
