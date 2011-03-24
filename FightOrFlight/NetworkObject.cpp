#include "NetworkObject.h"
#include "NetworkManager.h"

NetworkObject::NetworkObject( NetworkManager* Net, NETID NetID ) : ReferenceCountedObject(),
		Manager(Net), net_id(NetID), InStream(0,0), OutStream(0,0), MessageAvailable(false)
{
	NetData* InData = Manager->getUpdateData( net_id );
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

deque<u8> NetworkObject::getOutStream()
{
	MessageAvailable = false;
	deque<u8> out = OutStream;
	
	return out;
}

void NetworkObject::update()
{
	NetData* InData = Manager->getUpdateData( net_id );
}

const deque<u8>& NetworkObject::getInStream()
{
	return InStream;
}

void NetworkObject::sendData( const deque<u8>& OutData )
{
	for( u32 i=0; i<OutData.size(); i++ )
		OutStream.push_back( OutData[i] );
	MessageAvailable = true;
}

string NetworkObject::getDebugInfo()
{
	return string("NetworkObject");
}
