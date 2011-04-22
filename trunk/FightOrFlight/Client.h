/* 
 * File:   ClientObject.h
 * Author: chris
 *
 * Created on March 23, 2011, 8:54 PM
 */

#ifndef CLIENTOBJECT_H
#define	CLIENTOBJECT_H

#include "Entity.h"
#include "NetworkManager.h"

#include <irrlicht/IEventReceiver.h>

class Client : public Entity, public irr::IEventReceiver
{
public:
	Client( GameManager* Game, NETID NetID );

protected:
	virtual ~Client();

public:
	bool OnEvent( const irr::SEvent& Event );
	void update();

protected:
	virtual string getDebugInfo() const;

private:
	irr::scene::ISceneNode* camera_target;
	irr::scene::ISceneNode* camera_up;
	irr::scene::ISceneNode* camera_side;
	irr::scene::ICameraSceneNode* client_camera;

	bool send_update;
	irr::core::vector3df update_linvel;
	irr::core::vector3df update_angvel;
};

#endif	/* CLIENTOBJECT_H */
