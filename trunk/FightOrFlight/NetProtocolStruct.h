/* 
 * File:   NetProtocolStruct.h
 * Author: chris
 *
 * Created on March 18, 2011, 10:40 AM
 */

#ifndef NETPROTOCOLSTRUCT_H
#define	NETPROTOCOLSTRUCT_H

// include the proper header to expose our data containers (matrix,vector3df)
#include "Types.h"

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

struct NetData
{
	u8 MessageStart;

	NETID net_id;
	u32 MsgTime;

	E_NET_MESSAGE_TYPE MsgType;

	// used for passing updates to existing objects.
	u8 SyncSize;
	struct Message_Sync
	{
		u8 SyncStart;
		u8 CalibrateSize;
		struct Sync_Calibrate
		{
			u8 CalibrateStart;
			// old_position/rotation matrix
			// old_velocity matrix
			// old_accelleration matrix
			u8 CalibrateEnd;
		} * Calibrate;
		u8 ForceUpdateSize;
		struct Sync_ForceUpdate
		{
			u8 ForceUpdateStart;
			// new_position/rotation matrix
			// new_velocity matrix
			// new_accelleration matrix
			u8 ForceUpdateEnd;
		} * ForceUpdate;
		u8 RelUpdateSize;
		struct Sync_RelUpdate
		{
			u8 RelUpdateStart;
			// rel_position/rotation matrix
			// new_velocity matrix
			// new _accelleration matrix
			u8 RelUpdateEnd;
		} * Relative;
		u8 SyncEnd;
	} * Sync;

	// used for passing object creation queries
	u8 CreateSize;
	struct Message_Create
	{
		u8 CreateStart;
		// Object Type
		// Object Parent NetID
		// Initial position/rotation matrix
		// Initial velocity matrix
		// Initial accelleration matrix
		u8 CreateEnd;
	} * Create;

	u8 DestroySize;
	struct Message_Destroy
	{
		u8 DestroyStart;
		// Object NetID
		// Destroy Type
		u8 DestroyEnd;
	} * Destroy;

	ACKID Acknowledge;

	u8 MessageEnd;

	inline bool operator < ( const NetData& Other ) const;
};

// Helper functions
vector<u8> makeAckMessage( const vector<u8>& OrigMessage );
vector<u8> makeSyncMessage( /*...*/ );
vector<u8> makeCreateMessage( /*...*/ );
vector<u8> makeDestroyMessage( /*...*/ );

vector<u8> makeRawMessage( const u8* );

#endif	/* NETPROTOCOLSTRUCT_H */

