#include "Client.h"


Client::Client( GameManager* Game, NETID NetID ) : Entity( Game, NetID )
{
	// TODO
}

Client::~Client()
{
	// TODO
}

bool Client::OnEvent( const irr::SEvent& Event )
{
	// TODO
	return true;
}

string Client::getDebugInfo() const
{
	return string("Client");
}
