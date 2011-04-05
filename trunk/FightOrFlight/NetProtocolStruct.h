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
typedef u8	ACKID;

enum E_NET_MESSAGE_TYPE
{
	ENMT_PING=0,
	ENMT_SYNC,
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
		struct Sync_Calibrate
		{
			// old_position/rotation matrix
			// old_velocity matrix
			// old_accelleration matrix
		} Calibrate;
		
		struct Sync_ForceUpdate
		{
			// new_position/rotation matrix
			// new_velocity matrix
			// new_accelleration matrix
		} ForceUpdate;

		struct Sync_RelUpdate
		{
			// rel_position/rotation matrix
			// new_velocity matrix
			// new _accelleration matrix
		} Relative;
	} Sync;

	// used for passing object creation commands
	struct Message_Create
	{
		c8 Meshname [16];
		NETID ParentID;
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

	ACKID Acknowledge;

	u8 MessageEnd;

protected:
	virtual ~NetData();

	virtual string getDebugInfo() const;
};

inline bool operator< ( const NetData&A, const NetData& B );

// Helper functions
deque<u8> makeAckMessage( NetData& OrigMessage );

NetData* getMessage( deque<u8>& Data );

deque<u8> makeSyncMessage( NetData* );
deque<u8> makeCreateMessage( /*...*/ );
deque<u8> makeDestroyMessage( /*...*/ );

deque<u8> makeRawMessage( const u8* );

#endif	/* NETPROTOCOLSTRUCT_H */
