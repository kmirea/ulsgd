/* 
 * File:   Object.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:05 PM
 */

#ifndef OBJECT_H
#define	OBJECT_H

#define OBJECT_TYPE_NULL 0

#include "Types.h"

#include "IrrObjectNode.h"

class Room;

class Object : public IrrObjectNode
{
	const Room* room;

	vector<u32> Position;
	vector<u32> Velocity;
public:
	Object( Room* room, const vector<u32>& Position, const vector<u32>& Velocity );

	virtual ~Object() = 0;

	const vector<u32>& getPosition() const;	// [0] == X, [1] == Y
	const vector<u32>& getVelocity() const; // [0] == S, [1] == R

	const u32& X() const;	// X or row
	const u32& Y() const;	// Y or column
	const u32& S() const;	// Speed
	const u32& R() const;	// Rotation (0,90,180,270)

	virtual const u32& getObjectType() const = 0;

	virtual bool isDead() const = 0;

	virtual void prepass( const u32 GameTime ) = 0;
	virtual void pass( const u32 GameTime ) = 0;
	virtual void postpass( const u32 GameTime ) = 0;

	virtual void handleCollision( Object& Other ) = 0;
	
protected:
	const Room* getRoom() const;

	void setPosition( const vector<u32>& Position );
	void setVelocity( const vector<u32>& Velocity );
};

#endif	/* OBJECT_H */
