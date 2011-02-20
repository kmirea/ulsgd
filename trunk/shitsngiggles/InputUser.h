/* 
 * File:   InputUser.h
 * Author: chris
 *
 * Created on February 19, 2011, 1:19 PM
 */

#ifndef INPUTUSER_H
#define	INPUTUSER_H

#include "Types.h"
#include "BinarySearchTree.h"

class World;

class InputUser
{
	World* world;

	BinarySearchTree<u8> BST;
	
public:
	InputUser( World* world );
	void SendInput(const vector<u8>& input);
protected:
	void registerInputVal(const u8 Key); // TODO: Extend this to use more inputs
	void registerInput();
	virtual void InputEvent(const u8 key) = 0;
};

#endif	/* INPUTUSER_H */

