//NetEngineLocal.cpp

#include "NetEngineLocal.h"


//======== global Variables ==========
vector<NetEngineLocal*> netNodes;
//====================================



NetEngineLocal::NetEngineLocal()
{
	netNodes.push_back(this);
}
void NetEngineLocal::Init()
{

}
void NetEngineLocal::Send( Packet* packet, char* target )
{
	for( unsigned int i = 0; i < netNodes.size(); i++ )
	{
		if( netNodes[i]->GetAddress() == (unsigned int)*target )
		{
			netNodes[i]->GetInbox()->push_back( packet );
		}
	}
}
void NetEngineLocal::SetTarget( char* target )
{
	this->target = (unsigned int)*target;
}
void NetEngineLocal::SetAddress( char* address )
{
	this->address = address;
}
void NetEngineLocal::Send( Packet* packet )
{
	for( unsigned int i = 0; i < netNodes.size(); i++ )
	{
		if( netNodes[i]->GetAddress() == target )
		{
			netNodes[i]->GetInbox()->push_back( packet );
		}
	}
}
Packet*	NetEngineLocal::GetFirstPacketFromInbox()
{
	if( inbox.size() > 0 )
	{
		Packet* tmp = inbox[0];
		inbox.pop_back();
		return tmp;
	}
	return NULL;
}
bool NetEngineLocal::InboxEmpty()
{
	if( inbox.size() == 0 )
	{
		return false;
	}
	return true;
}
bool NetEngineLocal::InboxFull()
{
	return false;
}
unsigned int NetEngineLocal::NumPacketsInInbox()
{
	return inbox.size();
}
char* NetEngineLocal::GetAddress()
{
	return (char*)address;
}
vector<Packet*>* NetEngineLocal::GetInbox()
{
	return &inbox;
}