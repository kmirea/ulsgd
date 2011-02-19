#include "IrrObjectNode.h"
#include "Room.h"

irr::scene::ISceneManager* IrrObjectNode::IrrSceneManager = NULL;
irr::video::IVideoDriver* IrrObjectNode::IrrVideoDriver = NULL;

void IrrObjectNode::setTexture( string TextureName, u32 TextureMaxX, u32 TextureMaxY )
{
	if( TextureName != "" )
	{
		IrrSceneNode->setVisible( true );
		IrrSceneNode->setMaterialTexture( 0, IrrVideoDriver->addTexture( TextureName.c_str(),
									IrrVideoDriver->createImageFromFile( TextureName.c_str() ) ) );
		IrrSceneNode->setMaterialFlag( irr::video::EMF_LIGHTING, false );
		IrrSceneNode->setMaterialFlag( irr::video::EMF_BILINEAR_FILTER, false );
		IrrSceneNode->setMaterialType( irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF );

		FrameBoundary[3] = (f32)TextureMaxX;
		FrameBoundary[4] = (f32)TextureMaxY;
	}
	else
		IrrSceneNode->setVisible( false );
}

void IrrObjectNode::setFrameBoundaries( u32 FrameMinX, u32 FrameMaxX, u32 FrameY )
{
	// TODO: implement error checking.
	FrameBoundary[0] = (f32) FrameMinX;
	FrameBoundary[1] = (f32) FrameMaxX;
	FrameBoundary[2] = (f32) FrameY;
}

void IrrObjectNode::setFrame( u32 frame )
{
	// TODO: make this less horribly inefficient...
	Frame = (f32)frame + FrameBoundary[0];
	while( Frame > FrameBoundary[1] )
		Frame -= ( FrameBoundary[1] - FrameBoundary[0] + 1.0f );

	if( IrrSceneNode->isVisible() )
	{
		IrrSceneNode->getMaterial(0).getTextureMatrix(0).setTextureTranslate(Frame / FrameBoundary[2], FrameBoundary[3] / FrameBoundary[4] );
	}
}

void IrrObjectNode::setIrrPosition( u32 X, u32 Y )
{
	IrrPosition.X = (f32)X;
	IrrPosition.Y = (f32)Y;
	IrrSceneNode->setPosition( IrrPosition );
}

void IrrObjectNode::setIrrRotation( u32 R )
{
	IrrRotation.rotateXYBy( (f64)R, IrrSceneNode->getPosition() );
}

void IrrObjectNode::setIrrLayer( u32 Z )
{
	IrrPosition.Z = (f32)Z;
}

void IrrObjectNode::setIrrManagers( irr::IrrlichtDevice* IrrDevice )
{
	IrrSceneManager = IrrDevice->getSceneManager();
	IrrVideoDriver = IrrDevice->getVideoDriver();
}

IrrObjectNode::IrrObjectNode( Room* RoomRoot ) : IrrSceneNode(NULL), IrrPosition(0,0,0), IrrRotation(0,0,0),
		FrameBoundary(5,0.0f), Frame(0)
{
	IrrSceneNode = IrrSceneManager->addBillboardSceneNode( RoomRoot->getRoomRoot() );
	IrrSceneNode->setVisible( false );
}
