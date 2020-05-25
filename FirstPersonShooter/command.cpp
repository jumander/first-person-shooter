#include <iostream>
#include <string>

#include "command.h"
#include "Server.h"
#include "glut.h"

char sline[10][55];
int newline=0;
int Stage;
char ipaddress[20];
int port;

using namespace std;
int command::console(string scommand){
	
	float tmp;
	float *ptmp = &tmp;


	//if 0
	if(Stage == 0){

	glutPostRedisplay();
	if (scommand[0] == 'c' && scommand[1] == 'l' && scommand[2] == 'o' && scommand[3] == 's' && scommand[4] == 'e'){
		
		return 0;

	}

	else if (scommand[0] == 'o' && scommand[1] == 'p' && scommand[2] == 'e' && scommand[3] == 'n'){
		
		Stage = 10;
		draw("Enter ip address: ", 2);

	}

	else if (scommand[0] == 'h' && scommand[1] == 'o' && scommand[2] == 's' && scommand[3] == 't'){
		
		Stage = 20;
		draw("Enter ip address: ", 2);
		
	} else{
		draw("Invalid command!", 2);

	}


	//if 10 or 20
	}else if(Stage == 10 || Stage == 20){
		
		strcpy(ipaddress, scommand.c_str());
		draw("Enter port number: ", 2);
		Stage++;

	}else if(Stage == 11 || Stage == 21){
	
		
		port =  atoi(scommand.c_str());
		
		
		Server so;
		if (Stage == 11){
		so.transfer(0.0, 0.0, 0.0, 1, ipaddress, port,ptmp ,ptmp ,ptmp);
		Stage = 0;
		return 1;
		}
		if (Stage == 21){
		so.transfer(0.0, 0.0, 0.0, 2, ipaddress, port, ptmp, ptmp, ptmp);
		Stage = 0;
		return 2;
		}

		
	}
		
	
	return 0;
}

int command::draw(char commandline[50], int State){

	
	char cline[10][55];

	

	glColor4f(0.0,0.0,0.0,0.3);
	glBegin(GL_QUADS);
	glVertex3f(-2.6, 1.45, -2.0);
	glVertex3f(-1.5, 1.45, -2.0);
	glVertex3f(-1.5, 0.98, -2.0);
	glVertex3f(-2.6, 0.98, -2.0);
	glEnd();

	
	if(State == 1){
		strcpy_s(sline[newline], commandline);
		newline++;
		if (newline > 9)
			newline = 0;
		for(int i = 0; i < 51; i++){
			
			commandline[i] = 0; 
			
		}
	}

	if(State == 2){
	strcpy_s(sline[newline], commandline);
	
	newline++;
		if (newline > 9)
			newline = 0;
	}

	

	for (int i = 0; i < 10; i++){
	glColor3f(1.0,1.0,1.0);
	write(-2.6, 1.4 -(0.04*i), -2.0, "> ", 1);
	}
	write(-2.6, 1.4 -(0.4), -2.0, "<< ", 1);
	
	for (int i = 0; i < 10; i++){
	glColor3f(1.0,1.0,1.0);
	write(-2.53, 1.4 -(0.04*i), -2.0, sline[i], 1);

	}

	write(-2.55, 1.4 -(0.4), -2.0, commandline, 1);
	

	return 0;

}

void command::write(float x, float y, float z, char *string, int size)
{
  unsigned int  i;
  glRasterPos3f(x, y, z);
  for (i = 0; i < strlen(string); i++)
  {
	  if (size == 1) 
		 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);

	  if (size == 3)
		  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	  
  }
}