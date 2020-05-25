#pragma once
class Server
{
public:
	Server();
	int Server::transfer(float xpos, float ypos, float zpos, int STATE,char ipaddress[], int port,float *pxpos, float *pypos, float *pzpos);
	~Server(void);
};

