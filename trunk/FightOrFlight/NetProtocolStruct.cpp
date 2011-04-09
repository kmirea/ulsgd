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
	if( Data.size() == 0 )
		return NULL;
	
	NetData* Out = NULL;

	u32 temp = 0;
	
	u8 Buffer[MAX_BUF_SIZE] = {Message_End};
	u32 DataIndex = 0;

	for( u32 i=0; i<MAX_BUF_SIZE && i<Data.size(); i++ )
	{
		Buffer[i] = Data[i];
	}

	if( Buffer[0] == Message_Begin )
	{
		Out = new NetData();
		Out->grab();

		Out->MessageStart = Message_Begin;
		DataIndex += sizeof( Out->MessageStart );

		memcpy( (void*)&(Out->net_id), (void*)(Buffer+DataIndex), sizeof(NETID) );
		DataIndex += sizeof(NETID);
		memcpy( (void*)&(Out->MsgTime), (void*)(Buffer+DataIndex), sizeof(u32) );
		DataIndex += sizeof(u32);
		memcpy( (void*)&(Out->MsgType), (void*)(Buffer+DataIndex), sizeof(E_NET_MESSAGE_TYPE) );
		DataIndex += sizeof(E_NET_MESSAGE_TYPE);
		
		if( DataIndex > Data.size() )
		{
			Out->drop();
			return NULL;
		}

		switch( Out->MsgType )
		{
		case ENMT_SYNC:
			memcpy( (void*)&(Out->Sync), (void*)(Buffer+DataIndex), sizeof(NetData::Message_Sync) );
			DataIndex += sizeof(NetData::Message_Sync);
			break;
		case ENMT_CREATE:
			memcpy( (void*)&(Out->Create), (void*)(Buffer+DataIndex), sizeof( NetData::Message_Create) );
			DataIndex += sizeof( NetData::Message_Create);
			break;
		case ENMT_DESTROY:
			memcpy( (void*)&(Out->Destroy), (void*)(Buffer+DataIndex), sizeof( NetData::Message_Destroy) );
			DataIndex += sizeof(NetData::Message_Destroy);
			break;
		}

		if( DataIndex > Data.size() )
		{
			Out->drop();
			return NULL;
		}
		
		Out->MessageEnd = Buffer[DataIndex++];
		if( (u32)(Out->MessageEnd) != (u32)(Message_End) )
		{
			Out->drop();
			Out = NULL;
		}
		for( u32 i=0; i<DataIndex&&Data.size()>0; i++ )
		{
			Data.pop_front();
		}

		return Out;
	}
	else
	{
		while( Data.size() > 0 && ( Data.front() != Message_Begin || Data.front() != Message_End ) )
			Data.pop_front();
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
		u8 Buffer [MAX_BUF_SIZE] = {Message_End};
		ptr Index = 0;

		Buffer[Index++] = Data->MessageStart;

		memcpy( (void*)(Buffer+Index), (void*)&(Data->net_id), sizeof(NETID) );
		Index+=sizeof(NETID);
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MsgTime), sizeof(u32) );
		Index+=sizeof(u32);
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MsgType), sizeof(E_NET_MESSAGE_TYPE) );
		Index+=sizeof(E_NET_MESSAGE_TYPE);
		memcpy( (void*)(Buffer+Index), (void*)&(Data->Create), sizeof(NetData::Message_Create) );
		Index+=sizeof(NetData::Message_Create);
		memcpy( (void*)(Buffer+Index), (void*)&(Data->MessageEnd), sizeof(u8) );
		Index+=sizeof(u8);
		
		for( u32 i=0; i<Index; i++ )
			Output.push_back( Buffer[i] );

		Data->drop();
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
