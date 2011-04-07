#include "NetProtocolStruct.h"
#include "string.h"

NetData::NetData() : ReferenceCountedObject()
{

}

NetData::~NetData()
{
	
}

string NetData::getDebugInfo() const
{
	return string( "NetData" );
}

inline bool operator< ( const NetData& A, const NetData& B )
{
	if( A.MsgType < B.MsgType )
		return true;

	else if( A.MsgType > B.MsgType )
		return false;

	else if( A.MsgType == B.MsgType )
	{
		if( A.MsgTime < B.MsgTime )
			return true;
		else if( A.MsgTime > B.MsgTime )
			return false;
		else return false;
	}
}

// Helper functions
NetData* getMessage( deque<u8>& Data )
{
	NetData* Out;

	u32 temp = 0;
	
	u8 Buffer[sizeof(NetData)] = {0};
	u32 DataIndex = 1;
	u32 NetIndex = 1;

	for( u32 i=0; i<sizeof(NetData) && i<Data.size(); i++ )
	{
		Buffer[i] = Data[i];
	}

	if( Buffer[0] == Message_Begin )
	{
		Out = new NetData();

		Out->MessageStart = Message_Begin;

		memcpy( (void*)(Out+NetIndex), (void*)(Buffer+DataIndex), sizeof(NETID) + sizeof(u32) + sizeof(E_NET_MESSAGE_TYPE) + sizeof(u8) );
		DataIndex += sizeof(NETID) + sizeof(u32) + sizeof(E_NET_MESSAGE_TYPE) + sizeof(u8);
		NetIndex += sizeof(NETID) + sizeof(u32) + sizeof(E_NET_MESSAGE_TYPE) + sizeof(u8);

		if( DataIndex > Data.size() )
		{
			Out->drop();
			return NULL;
		}

		if( Out->MsgType == ENMT_SYNC )
		{
			memcpy( (void*)(Out+NetIndex), (void*)(Buffer+DataIndex), sizeof(NetData::Message_Sync) );
			DataIndex += sizeof( NetData::Message_Sync );
		}
		NetIndex += sizeof( NetData::Message_Sync );

		if( DataIndex > Data.size() )
		{
			Out->drop();
			return NULL;
		}

		if( Out->MsgType == ENMT_CREATE )
		{
			memcpy( (void*)(Out+NetIndex), (void*)(Buffer+DataIndex), sizeof( NetData::Message_Create) );
			DataIndex += sizeof( NetData::Message_Create );
		}
		NetIndex += sizeof( NetData::Message_Create );

		if( DataIndex > Data.size() )
		{
			Out->drop();
			return NULL;
		}

		if( Out->MsgType == ENMT_DESTROY )
		{
			memcpy( (void*)(Out+NetIndex), (void*)(Buffer+DataIndex), sizeof( NetData::Message_Destroy) );
			DataIndex += sizeof( NetData::Message_Destroy );
		}
		NetIndex += sizeof( NetData::Message_Destroy );

		if( DataIndex > Data.size() )
		{
			Out->drop();
			return NULL;
		}
		
		Out->MessageEnd = Message_End;

		for( u32 i=DataIndex; i>0; i++ )
		{
			Data.pop_front();
		}
	}
	else
	{
		for(u32 i=0; i<Data.size() && Data[0] != Message_End; )
			Data.pop_front();
		return NULL;
	}
}

deque<u8> makeSyncMessage( NetData* Data )
{
	deque<u8> Output;
	if( Data != NULL && Data->MsgType == ENMT_SYNC )
	{
		u8 Buffer [sizeof(NetData)];
		ptr Index = 0;

		Buffer[Index++] = Data->MessageStart;

		memcpy( (void*)(Buffer+Index), (void*)&(Data->net_id), Index+=sizeof(NETID) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MsgTime), Index+=sizeof(u32) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MsgType), Index+=sizeof(E_NET_MESSAGE_TYPE) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->Sync), Index+=sizeof(NetData::Message_Sync) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MessageEnd), Index++ );

		for( u32 i=0; i<Index; i++ )
			Output.push_back( Buffer[i] );
	}
	return Output;
}

deque<u8> makeCreateMessage( NetData* Data )
{
	deque<u8> Output;
	if( Data != NULL && Data->MsgType == ENMT_CREATE )
	{
		u8 Buffer [sizeof(NetData)];
		ptr Index = 0;

		Buffer[Index++] = Data->MessageStart;

		memcpy( (void*)(Buffer+Index), (void*)&(Data->net_id), Index+=sizeof(NETID) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MsgTime), Index+=sizeof(u32) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MsgType), Index+=sizeof(E_NET_MESSAGE_TYPE) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->Create), Index+=sizeof(NetData::Message_Create) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MessageEnd), Index++ );

		for( u32 i=0; i<Index; i++ )
			Output.push_back( Buffer[i] );
	}
	return Output;
}

deque<u8> makeDestroyMessage( NetData* Data )
{
	deque<u8> Output;
	if( Data != NULL && Data->MsgType == ENMT_DESTROY )
	{
		u8 Buffer [sizeof(NetData)];
		ptr Index = 0;

		Buffer[Index++] = Data->MessageStart;

		memcpy( (void*)(Buffer+Index), (void*)&(Data->net_id), Index+=sizeof(NETID) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MsgTime), Index+=sizeof(u32) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MsgType), Index+=sizeof(E_NET_MESSAGE_TYPE) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->Destroy), Index+=sizeof(NetData::Message_Destroy) );
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MessageEnd), Index++ );

		for( u32 i=0; i<Index; i++ )
			Output.push_back( Buffer[i] );
	}
	return Output;
}

deque<u8> makeRawMessage( const u8* data, u32 size )
{
	deque<u8> Output;

	if( data[0] != Message_Begin || data[size-1] != Message_End )
		return Output;

	for( u32 i=0; i<size; i++ )
	{
		Output.push_back( data[i] );
	}

	return Output;
}
