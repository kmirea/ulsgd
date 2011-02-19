#include "Object.h"

Object::Object( Room* R, const vector<u32>& P, const vector<u32>& V ) : room(R), Position(P), Velocity(V)
{
}

const vector<u32>& Object::getPosition() const	// [0] == X, [1] == Y
{
	return Position;
}

const vector<u32>& Object::getVelocity() const // [0] == S, [1] == R
{
	return Velocity;
}

const u32& Object::X() const	// X or row
{
	return Position[0];
}

const u32& Object::Y() const	// Y or column
{
	return Position[1];
}

const u32& Object::S() const	// Speed
{
	return Velocity[0];
}

const u32& Object::R() const	// Rotation (0,90,180,270)
{
	return Velocity[1];
}

const Room* Object::getRoom() const
{
	return room;
}

void Object::setPosition(const vector<u32>& P)
{
	Position = P;
}

void Object::setVelocity(const vector<u32>& V)
{
	Velocity = V;
}