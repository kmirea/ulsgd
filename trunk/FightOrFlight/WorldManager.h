/* 
 * File:   WorldManager.h
 * Author: chris
 *
 * Created on March 21, 2011, 7:07 PM
 */

#ifndef WORLDMANAGER_H
#define	WORLDMANAGER_H

#include "ReferenceCountedObject.h"
#include "NetworkManager.h"

#include "Client.h"

#include <irrlicht/irrlicht.h>
#include <irrBullet/irrbullet.h>

class WorldManager : public ReferenceCountedObject
{
public:
	WorldManager( GameManager* Game, E_MANAGER_MODE Mode );
protected:
	virtual ~WorldManager();

public:
	bool run();
	void update();

	irr::IrrlichtDevice* getIrrlichtDriver() const;
	irrBulletWorld* getIrrBulletDriver() const;

	void setClient( Client* ClientEntity );

	void addAffector( PhysicsObject* Physics ) const;
	
protected:
	virtual string getDebugInfo() const;

private:
	GameManager* Game;
	E_MANAGER_MODE Mode;

	irr::IrrlichtDevice* Irrlicht;
	irrBulletWorld* irrBullet;
};

#endif	/* WORLDMANAGER_H */

