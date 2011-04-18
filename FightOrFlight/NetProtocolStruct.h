/* 
 * File:   NetProtocolStruct.h
 * Author: chris
 *
 * Created on March 18, 2011, 10:40 AM
 */

#ifndef NETPROTOCOLSTRUCT_H
#define	NETPROTOCOLSTRUCT_H

// include the proper header to expose our data containers (matrix,vector3df)
#include "ReferenceCountedObject.h"

#define Message_Begin 0x7e	// 0111 1110b
#define Message_End 0x81	// 1000 0001b

typedef s32 NETID;

enum E_NET_MESSAGE_TYPE
{
	ENMT_PING=0,
	ENMT_SYNC,
	ENMT_APPLY_FORCE,
	ENMT_CREATE,
	ENMT_DESTROY,

// Illegal values
	ENMT_COUNT,
	ENMT_FORCE_8_BIT = U8_MAX
};

class NetData : public ReferenceCountedObject
{
public:
	NetData();
	
	u8 MessageStart;

	NETID net_id;
	u32 MsgTime;

	E_NET_MESSAGE_TYPE MsgType;

	// used for passing updates to existing objects.
	struct Message_Sync
	{
		f32 Position [3];
		f32 Rotation [3];
		f32 LinearVelocity [3];
		f32 AngularVelocity [3];
	} Sync;

	struct Message_Apply_Force
	{
		f32 LinearVelocity [3];
		f32 AngularVelocity[3];
	} ApplyForce;

	// used for passing object creation commands
	struct Message_Create
	{
		c8 Meshname [16];
		f32 Mass;
		f32 Position [3];
		f32 Rotation [3];
		f32 Scale [3];
		f32 LinearVelocity [3];
		f32 AngularVelocity [3];
	} Create;

	struct Message_Destroy
	{
		// Destroy Type
	} Destroy;

	u8 MessageEnd;

protected:
	virtual ~NetData();

	virtual string getDebugInfo() const;
};

#define MAX_BUF_SIZE sizeof(u8)+sizeof(NETID)+sizeof(u32)+sizeof(E_NET_MESSAGE_TYPE)+sizeof(NetData::Message_Create) + sizeof(u8)

inline bool operator< ( const NetData& A, const NetData& B );
inline bool operator==( const NetData& A, const NetData& B );

// Helper functions
NetData* getMessage( deque<u8>& Data );

deque<u8> makeSyncMessage( NetData* Data );
deque<u8> makeApplyMessage( NetData* Data );
deque<u8> makeCreateMessage( NetData* Data );
deque<u8> makeDestroyMessage( NetData* Data );

deque<u8> makeRawMessage( const u8* );

#endif	/* NETPROTOCOLSTRUCT_H */

