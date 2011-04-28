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
	void CalculateForces();
	
	irr::scene::ISceneNode* camera_target;
	irr::scene::ISceneNode* camera_up;
	irr::scene::ISceneNode* camera_side;
	irr::scene::ICameraSceneNode* client_camera;

	bool send_ang_update;
	bool send_lin_update;
	irr::core::vector3df update_lin_force;
	irr::core::vector3df update_ang_force;
};

#endif	/* CLIENTOBJECT_H */

