#include "NetworkObject.h"
#include "NetworkManager.h"

NetworkObject::NetworkObject(const NetworkManager* Net) : ReferenceCountedObject(),
		Manager(Net), net_id(Manager->getNetID()), InStream(0,0), OutStream(0,0), MessageAvailable(false)
{
	InStream = Manager->getUpdateData( net_id );
	OutStream = makeAckMessage( InStream );
}