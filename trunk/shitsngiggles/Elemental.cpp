#include "Elemental.h"

Elemental::Elemental( Room* room, const vector<u32>& Position, const vector<u32>& Velocity, E_ELEMENT_TYPE Element )
	: Object( room, Position, Velocity ), ElementType(Element), NextElement(Element)
{
}

E_ELEMENT_TYPE Elemental::getElementyType() const
{
	return ElementType;
}
