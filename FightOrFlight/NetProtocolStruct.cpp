#include "NetProtocolStruct.h"
#include "string.h"

inline bool operator< ( const NetData& A, const NetData& B )
{
	if( A.MsgType < B.MsgType )
		return true;

	if( A.MsgType > B.MsgType )
		return false;

	if( A.MsgType == B.MsgType )
	{
		if( A.MsgTime < B.MsgTime )
			return true;
		if( A.MsgTime > B.MsgTime )
			return false;
		if( A.MsgTime == B.MsgTime )
		{
			if( A.Acknowledge < B.Acknowledge )
				return true;
			else return false;
		}
	}
}

// Helper functions
deque<u8> makeAckMessage( NetData& Orig )
{
	deque<u8> msg;

	const u32 BufferSize = 128;
	u8 Buffer [BufferSize] = {0};

	u32 BufferIndex = 0;

	Buffer[BufferIndex++] = Message_Begin;

	NETID temp_netid = Orig.net_id;
	memcpy( (void*)(Buffer+BufferIndex), (void*)(&temp_netid), sizeof(temp_netid) );

	BufferIndex+=sizeof(temp_netid);

	u32 temp_time = Orig.MsgTime;
	memcpy( (void*)(Buffer+BufferIndex), (void*)(&temp_time), sizeof(temp_time) );

	BufferIndex+=sizeof(temp_time);

	Buffer[BufferIndex++] = (u8)(Orig.MsgType);

	Buffer[BufferIndex++] = 0;
	Buffer[BufferIndex++] = 0;
	Buffer[BufferIndex++] = 0;

	ACKID temp_ack =  Orig.Acknowledge;
	memcpy( (void*)(Buffer+BufferIndex), (void*)(temp_ack), sizeof(temp_ack) );

	BufferIndex+=sizeof(temp_ack);
	Buffer[BufferIndex++] = Message_End;

	for( u32 i=0; i<BufferIndex; i++ )
	{
		msg.push_back( Buffer[i] );
	}

	return msg;
}

void getMessage( NetData& Out, deque<u8>& Data )
{
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
		Out.MessageStart = Message_Begin;

		memcpy( (void*)(&Out+NetIndex), (void*)(Buffer+DataIndex), sizeof(NETID) + sizeof(u32) + sizeof(E_NET_MESSAGE_TYPE) + sizeof(u8) );
		DataIndex += sizeof(NETID) + sizeof(u32) + sizeof(E_NET_MESSAGE_TYPE) + sizeof(u8);
		NetIndex += sizeof(NETID) + sizeof(u32) + sizeof(E_NET_MESSAGE_TYPE) + sizeof(u8);

		if( DataIndex > Data.size() )
		{
			Out.MessageStart = 0;
			return;
		}

		if( Out.MsgType == ENMT_SYNC )
		{
			memcpy( (void*)(&Out+NetIndex), (void*)(Buffer+DataIndex), sizeof(NetData::Message_Sync) );
			DataIndex += sizeof( NetData::Message_Sync );
		}
		NetIndex += sizeof( NetData::Message_Sync );

		if( DataIndex > Data.size() )
		{
			Out.MessageStart = 0;
			return;
		}

		if( Out.MsgType == ENMT_CREATE )
		{
			memcpy( (void*)(&Out+NetIndex), (void*)(Buffer+DataIndex), sizeof( NetData::Message_Create) );
			DataIndex += sizeof( NetData::Message_Create );
		}
		NetIndex += sizeof( NetData::Message_Create );

		if( DataIndex > Data.size() )
		{
			Out.MessageStart = 0;
			return;
		}

		if( Out.MsgType == ENMT_DESTROY )
		{
			memcpy( (void*)(&Out+NetIndex), (void*)(Buffer+DataIndex), sizeof( NetData::Message_Destroy) );
			DataIndex += sizeof( NetData::Message_Destroy );
		}
		NetIndex += sizeof( NetData::Message_Destroy );

		if( DataIndex > Data.size() )
		{
			Out.MessageStart = 0;
			return;
		}
		
		memcpy( (void*)(&Out+NetIndex), (void*)(Buffer+DataIndex), sizeof( ACKID ) );
		NetIndex += sizeof(ACKID);
		DataIndex += sizeof(ACKID);

		if( DataIndex > Data.size() )
		{
			Out.MessageStart = 0;
			return;
		}

		Out.MessageEnd = Message_End;

		for( u32 i=DataIndex; i>0; i++ )
		{
			Data.pop_front();
		}
	}
	else
	{
		Out.MessageStart = 0;
		for(u32 i=0; i<Data.size() && Data[0] != Message_End; )
			Data.pop_front();
	}
}

deque<u8> makeSyncMessage( /*...*/ )
{

}

deque<u8> makeCreateMessage( /*...*/ )
{

}

deque<u8> makeDestroyMessage( /*...*/ )
{

}

deque<u8> makeRawMessage( const u8* )
{

}
