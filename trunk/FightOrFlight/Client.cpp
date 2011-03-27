#include "Client.h"


Client::Client( GameManager* Game, NETID NetID ) : Entity( Game, NetID )
{

}

Client::~Client()
{

}

bool Client::OnEvent( const irr::SEvent& Event )
{
	return false;
}

string Client::getDebugInfo() const
{
	return string("Client");
}
