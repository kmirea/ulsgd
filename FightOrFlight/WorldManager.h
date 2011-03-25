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

protected:
	virtual string getDebugInfo() const;

private:
	GameManager* Game;
	E_MANAGER_MODE Mode;
};

#endif	/* WORLDMANAGER_H */

