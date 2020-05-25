#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>
#include "command.h"

#include "Server.h"


		WSAData wsa;
		WORD Version;

		SOCKADDR_IN Socket;
		int socketsize;
		
		SOCKET Connect;
		SOCKET Listen;

#pragma warning(disable: 4996)
using namespace std;

Server::Server(){

		
		Version = MAKEWORD(2, 1);
		


		WSAStartup(Version, &wsa);

		socketsize = sizeof(Socket);

		Connect = socket(AF_INET, SOCK_STREAM, NULL);
		Listen = socket(AF_INET, SOCK_STREAM, NULL);

		
		
	

}


int Server::transfer(float xpos, float ypos, float zpos, int STATE,char ipaddress[], int port,float *pxpos, float *pypos, float *pzpos){

	command cob;

	if (STATE == 1){
		
		cob.draw( "Creating Client...",2); 
	

		Socket.sin_addr.s_addr = inet_addr(ipaddress);
		Socket.sin_family = AF_INET;
		Socket.sin_port = htons(port);
	

		
	
		cob.draw("Connecting to ip: ",2);
		cob.draw(ipaddress,2);
		cob.draw(" at port: ",2);
		char tmpstr[7];
		itoa(port,tmpstr, 10);
		cob.draw(tmpstr,2);
		cob.draw("...",2);
		
		for(;;){
	
			if(connect(Connect, (SOCKADDR*)&Socket, sizeof(Socket))){
			cob.draw("Connection sent\n",2);
		

				break;
			}

		}


	}//end client


	if (STATE == 2){
		
		cob.draw("Creating Server...",2); 


		
		Socket.sin_addr.s_addr = inet_addr(ipaddress);
		Socket.sin_family = AF_INET;
		Socket.sin_port = htons(port);
	
		
	
	
		bind(Listen, (SOCKADDR*)&Socket, sizeof(Socket));

		listen(Listen, 1);
		
		cob.draw("done...",2); 
		cob.draw("Waiting for connection on ipaddress: ",2);
		cob.draw(ipaddress,2);
		cob.draw(" at port: ",2);
		char tmpstr[7];
		itoa(port,tmpstr, 10);
		cob.draw(tmpstr,2);
		cob.draw("...",2);
		
		for(;;){
	
			if(Connect = accept(Listen, (SOCKADDR*)&Socket, &socketsize)){
				cob.draw("...Connection was found ",2);
		

				break;
			}

		}
		

	}//end server



		

		char cxpos[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		char cypos[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		char czpos[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		char scoords[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		char recv[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		
		sprintf(cxpos,"%0.3f",xpos);
		sprintf(cypos,"%0.3f",ypos);
		sprintf(czpos,"%0.3f",zpos);
		
		strcat(scoords, "X");
		strcat(scoords, cxpos);
		
		strcat(scoords, "Y");
		strcat(scoords, cypos);
		
		strcat(scoords, "Z");
		strcat(scoords, czpos);
		
		
		if (STATE == 4){
			sendto(Connect, "KILLED", 7, NULL, (SOCKADDR*)&Socket, socketsize);
		
		} else {
			sendto(Connect, "GOOD", 5, NULL, (SOCKADDR*)&Socket, socketsize);
			
		}

		sendto(Connect, scoords, 30, NULL, (SOCKADDR*)&Socket, socketsize);
		
		xpos=0.0;
		ypos=-0.8;
		zpos=0.0;
		strcpy(cxpos, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
		strcpy(cypos, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"); 
		strcpy(czpos, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"); 
		
		char tmpc;
		for (int x = 0 ; x < 2; x++){

			recvfrom(Connect, recv, sizeof(recv), NULL, (SOCKADDR*)&Socket, &socketsize);
			cout<< "recv " << recv << endl; 
			if(recv[0] == 'X'){
			tmpc = 'X';
			
			
				

					
						for(int x = 1;x < 30; x++){
							
							
							
						if (recv[x] == 'Y')
							tmpc = 'Y';
						else if(recv[x] == 'Z')
							tmpc = 'Z';
						else if(recv[x] == 0)
							break;
						else if(tmpc == 'X'){
							for(int j = 0;;j++){
								if (cxpos[j] == 0){

								cxpos[j] = recv[x];
								 
								break;
								}
							}
						}
						else if(tmpc == 'Y'){
								for(int k = 0;;k++){
								if (cypos[k] == 0){
								cypos[k] = recv[x];
								
								break;
								}
							}
						}
						else if(tmpc == 'Z'){
								for(int l = 0;;l++){
								if (czpos[l] == 0){
								czpos[l] = recv[x];
								
								break;
								}

							}
						}
						
						}
						
						

					
					
			
			}
						
			
			

			
			if(recv[0] == 'K' && recv[1] == 'I' && recv[2] == 'L' && recv[3] == 'L' && recv[4] == 'E' && recv[5] == 'D'){
				STATE = 5;
			
			}
			
		}
		
		xpos = atof(cxpos);
		ypos = atof(cypos);
		zpos = atof(czpos);
		
		cout << "x: " << cxpos << " y: " << cypos << " z: " << czpos << endl;
		cout << "x: " << xpos << " y: " << ypos << " z: " << zpos << endl;
		
		if (xpos != 0.0 && ypos != -0.8 && zpos != 0.0){
		*pxpos = xpos;
		*pypos = ypos;
		*pzpos = zpos;
		}
		if (STATE == 5){
			return 1;
		}

	return 0;
}


Server::~Server(void)
{

	WSACleanup();

}
