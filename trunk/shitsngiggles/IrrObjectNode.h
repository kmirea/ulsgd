/* 
 * File:   IrrObjectNode.h
 * Author: chris
 *
 * Created on February 19, 2011, 3:16 PM
 */

#ifndef IRROBJECTNODE_H
#define	IRROBJECTNODE_H

#ifdef __WIN32__
#include <include/irrlicht.h>
#else
#include <irrlicht/irrlicht.h>
#endif

#include "Types.h"

class Room;

class IrrObjectNode
{
	irr::scene::ISceneNode* IrrSceneNode;

	static irr::scene::ISceneManager* IrrSceneManager;
	static irr::video::IVideoDriver* IrrVideoDriver;

	irr::core::vector3df IrrPosition;
	irr::core::vector3df IrrRotation;
	
	vector<f32> FrameBoundary;
	f32 Frame;

	irr::scene::ISceneNodeAnimator* Animator;
public:
	IrrObjectNode( Room* RoomRoot );
	void setIrrManagers( irr::IrrlichtDevice* IrrDevice );

protected:
	void setTexture( string TextureName, u32 TextureMaxX, u32 TextureMaxY );
	void setFrameBoundaries( u32 FrameMinX, u32 FrameMaxX, u32 FrameY );
	void setFrame( u32 Frame );

	void setIrrPosition( u32 X, u32 Y );
	void setIrrRotation( u32 R );

	void setIrrLayer( u32 Z );

	void addMotionAnimator( s32 DeltaX, s32 DeltaY, u32 Speed );
	void removeAnimator();
};

#endif	/* IRROBJECTNODE_H */

