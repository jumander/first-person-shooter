#include <windows.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <assert.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include "bullet.h"
#include "imageloader.h"
#include "ObjectLoader.h"
#include "command.h"
#include "Server.h"
#include <WinSock.h>
#include "glut.h"

#pragma warning(disable: 4996)




double PI = 3.14159265;


float camerapitch;
float camerayaw;
float yawx;
float yawz;
float angle;
float mousespeed = 0.060;
int movess;
float dir;
int movefb;
double velocity;
float speed;
int jump = 0;
float xpos;
float ypos;
float zpos;
bool SHOTING = false;
bool KILL = false;

char FPS[4];
int frames;
int c = 0;
clock_t frametime;
clock_t waittime;
clock_t timerstart;
clock_t timerend;

//text 
bool WRITING = false;
int SEND = 0;
char message[50];

bool JUMP = false;
bool FULLYLOADED = false;

float windowx;
float windowy;

GLuint _textureId[7];

void output(float x, float y, float z, char *string, int size);
GLuint loadTexture(Image* image);
void InitSkybox();

using namespace std;

void cameralock();
void mousemovement();
void movement();
void colision();

//network
int network;
float Mxpos;
float Mypos = -0.8;
float Mzpos = 10;

float *Pxpos = &Mxpos;
float *Pypos = &Mypos;
float *Pzpos = &Mzpos;

command co;
command *cpoint = &co;
Server so;
Server *spoint = &so;
bullet bo;
bullet *bpoint = &bo;

int monkey;
void Init(){

system("Color E5");

windowx = glutGet(GLUT_SCREEN_WIDTH);
windowy = glutGet(GLUT_SCREEN_HEIGHT);
glutSetCursor(GLUT_CURSOR_NONE);


glClearColor(0/255.0, 0/255.0, 0/255.0, 0.0);
glLoadIdentity();
glMatrixMode(GL_PROJECTION);
gluPerspective(75.0, windowx/windowy, 0.1, 1000.0);
glEnable(GL_DEPTH_TEST);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_NORMALIZE);
glEnable(GL_TEXTURE_2D);
Image* image0 = loadBMP("grassbmp.bmp");
	_textureId[0] = loadTexture(image0);
	delete image0;


glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


ObjectLoader ol;
ObjectLoader *objectloaderpointer = &ol;
monkey = objectloaderpointer->loadObject("ravenlord.obj","testmaterial.mtl");



	InitSkybox();

	Sleep(2000);

SetCursorPos(windowx/2, windowy/2);
}

void InitSkybox(){


Image* image1 = loadBMP("back.bmp");
	_textureId[1] = loadTexture(image1);
	delete image1;

Image* image2 = loadBMP("bottom.bmp");
	_textureId[2] = loadTexture(image2);
	delete image2;
	
Image* image3 = loadBMP("front.bmp");
	_textureId[3] = loadTexture(image3);
	delete image3;

Image* image4 = loadBMP("left.bmp");
	_textureId[4] = loadTexture(image4);
	delete image4;

Image* image5 = loadBMP("right.bmp");
	_textureId[5] = loadTexture(image5);
	delete image5;	

Image* image6 = loadBMP("top.bmp");
	_textureId[6] = loadTexture(image6);
	delete image6;

}


void calcpos(){

	angle = camerapitch + dir;

	cameralock();

	xpos += sin((angle)*(PI/180))*speed;

	zpos -= cos((angle)*(PI/180))*speed;

	
	//angle = (atan((xpos/zpos)))*(180/PI);


}



void mouse(int x, int y) {

		
		y = windowy - y;


		camerapitch += (x-(windowx/2))*mousespeed;

		camerayaw -= (y-(windowy/2))*mousespeed;



		if (camerapitch <= 90){
			yawx = (90-camerapitch)/90.0;
			yawz = (camerapitch)/90.0;		
		} else if (camerapitch <= 180) {
			yawx = (camerapitch-90)/-90.0;
			yawz = (180-camerapitch)/90.0;
		} else if (camerapitch <= 270) {
			yawx = (270-camerapitch)/-90.0;
			yawz = (camerapitch-180)/-90.0;
		} else if (camerapitch <= 360) {
			yawx = (camerapitch-270)/90.0;
			yawz = (360-camerapitch)/-90.0;
		}

		cameralock();

		if (SHOTING)
			bpoint->Initbullet(camerayaw, camerapitch, xpos, ypos, zpos);


}
void mouseyb(int button, int state, int x, int y) {

	if (state == GLUT_DOWN){

		if (button == GLUT_LEFT){
			SHOTING = true;
			

		}

	}

	if (state == GLUT_UP){

		if (button == GLUT_LEFT){
			SHOTING = false;

		}

	}

}

void drawskybox(){

	//skybox
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, _textureId[1]);

	glBegin(GL_QUADS);
		//front
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-200.0, 200.0, -200.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(200.0, 200.0, -200.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(200.0, -200.0, -200.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-200.0, -200.0, -200.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _textureId[5]);

	glBegin(GL_QUADS);

		// right
			glTexCoord2f(1.0, 1.0);
			glVertex3f(200.0, 200.0, 200.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(200.0, 200.0, -200.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(200.0, -200.0, -200.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(200.0, -200.0, 200.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _textureId[4]);
	
	glBegin(GL_QUADS);

		// left
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-200.0, 200.0, 200.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(-200.0, 200.0, -200.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-200.0, -200.0, -200.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-200.0, -200.0, 200.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _textureId[3]);
	
	glBegin(GL_QUADS);

	
		//back
			glTexCoord2f(1.0, 1.0);
			glVertex3f(-200.0, 200.0, 200.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(200.0, 200.0, 200.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(200.0, -200.0, 200.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-200.0, -200.0, 200.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _textureId[6]);

	glBegin(GL_QUADS);


		//top
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-200.0, 200.0, 200.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(200.0, 200.0, 200.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(200.0, 200.0, -200.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-200.0, 200.0, -200.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _textureId[2]);

	glBegin(GL_QUADS);


		//bot
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-200.0, -200.0, 200.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(200.0, -200.0, 200.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(200.0, -200.0, -200.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-200.0, -200.0, -200.0);


	glEnd();



	glEnable(GL_DEPTH_TEST);

	glDisable(GL_TEXTURE_2D);


}

void drawcube(float size){


	//cube
	glBegin(GL_QUADS);
	
	

		//front
			glNormal3f(0.0, 0.0, -size+1.0);
			glVertex3f(-size, size, -size);
			glVertex3f(size, size, -size);
			glVertex3f(size, -size, -size);
			glVertex3f(-size, -size, -size);

		// right
			glNormal3f(size+1.0, 0.0, 0.0);
			glVertex3f(size, size, size);
			glVertex3f(size, size, -size);
			glVertex3f(size, -size, -size);
			glVertex3f(size, -size, size);

		// left
			glNormal3f(-size-1.0, 0.0, 0.0);
			glVertex3f(-size, size, size);
			glVertex3f(-size, size, -size);
			glVertex3f(-size, -size, -size);
			glVertex3f(-size, -size, size);

		//back
			glNormal3f(0.0, 0.0, size-1.0);
			glVertex3f(-size, size, size);
			glVertex3f(size, size, size);
			glVertex3f(size, -size, size);
			glVertex3f(-size, -size, size);

		//top
			glNormal3f(0.0, size+1.0, 0.0);
			glVertex3f(-size, size, size);
			glVertex3f(size, size, size);
			glVertex3f(size, size, -size);
			glVertex3f(-size, size, -size);

		//bot
			glNormal3f(0.0, -size+1.0, 0.0);
			glVertex3f(-size, -size, size);
			glVertex3f(size, -size, size);
			glVertex3f(size, -size, -size);
			glVertex3f(-size, -size, -size);


	glEnd();


}

void drawplane(float xwidth, float ywidth,float zwidth, float translatex, float translatey, float translatez){



	glPushMatrix();

	glTranslatef(translatex, translatey, translatez);
	

	


	glBegin(GL_QUADS);
		glVertex3f(-xwidth, 0.0, zwidth);
		glVertex3f(xwidth, 0.0, zwidth);
		glVertex3f(xwidth, 0.0, -zwidth);
		glVertex3f(-xwidth, 0.0, -zwidth);
	glEnd();

	
	ywidth += translatey;
	


	if (xpos >= (-xwidth - translatex) && xpos <= (xwidth - translatex) &&
		zpos >= (-zwidth - translatez) && zpos <= (zwidth - translatez) && 
		ypos > -translatey-1.0 && ypos < -translatey){
			ypos = -translatey-1.0;
			velocity = 0;
			jump = 0;
		}

	glPopMatrix();

}

void Drawbullet(){
	glDisable(GL_LIGHTING);
	for (int i = 0; i <= 1000; i++){
		
		if(bpoint->Bulletcoordx[i] != 0.0 && bpoint->Bulletcoordy[i] != 0.0 && bpoint->Bulletcoordz[i] != 0.0){

			glPushMatrix();
			glTranslatef(bpoint->Bulletcoordx[i], bpoint->Bulletcoordy[i], bpoint->Bulletcoordz[i]);
			drawcube(0.02);
			glPopMatrix();
	
	
	
		}

	}
	glEnable(GL_LIGHTING);
}



void render(){

	frametime = clock();


	SetCursorPos(windowx/2, windowy/2);
	
	
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat ambientColor[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat lightColor0[] = {0.6, 0.6, 0.6, 1.0};
	GLfloat lightPosition0[] = { 200.0, 200.0, 200.0, 1.0};

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	
	
	glPushMatrix();

	glRotatef(camerapitch, 0.0, 1.0, 0.0);
	glRotatef(camerayaw, yawx, 0.0, yawz);

	glColor3f(1.0, 1.0, 1.0);
	drawskybox();
	
	glTranslatef(xpos, ypos, zpos);

	//TEXT in scene
	glPushMatrix();
	glTranslatef(-Mxpos, -Mypos, -Mzpos);
	glColor4f(0.0,0.0,1.0, 0.5);
	output(0.0, 0.5, 0.0, "Enemy", 1);


	glPopMatrix();
	
	glEnable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);
	
	if(!FULLYLOADED){
		glBindTexture(GL_TEXTURE_2D, _textureId[frames]);
		if (frames > 6)
			FULLYLOADED =true;
	} else
	glBindTexture(GL_TEXTURE_2D, _textureId[0]);
	


	
	


	//still plane
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		glNormal3f(0.0, 0.8, 1.0);
		glTexCoord2f(0.0, 20.0);
		glVertex3f(-5.0, -0.2, 5.0);
		glTexCoord2f(20.0, 20.0);
		glVertex3f(5.0, -0.2, 5.0);
		glTexCoord2f(20.0, 0.0);
		glVertex3f(5.0, -0.2, -5.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-5.0, -0.2, -5.0);
	glEnd();
	
	
	
	glPushMatrix();
	glTranslatef(0.0, 1.2, 7.5);



	//still plane
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 10.0);
		glVertex3f(-5.0, 1.4, 2.5);
		glTexCoord2f(20.0, 10.0);
		glVertex3f(5.0, 1.4, 2.5);
		glTexCoord2f(20.0, 0.0);
		glVertex3f(5.0, -1.4, -2.5);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-5.0, -1.4, -2.5);
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	

	//ambientlight
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	//positioned light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

	//multiplayer
	glColor4f(1.0,0.0,0.0,0.8);
	glPushMatrix();
	glTranslatef(-Mxpos,-Mypos, -Mzpos);
	drawcube(0.25);
	glPopMatrix();

	//bullets
	glColor3f(0.0,0.0,0.0);
	Drawbullet();


	//lägg din nivå mellan här...

	
	
	//glDisable(GL_LIGHTING);
	
	
	

	glColor3f(0.80, 0.80, 0.80);
	glPushMatrix();
	glTranslatef(0.0, -0.2, 3.0);
	glRotatef(180.0,0.0,1.0,0.0);
	glCallList(monkey);
	glPopMatrix();

	

	//glEnable(GL_LIGHTING);
	

	//...och här

	//sea
	glColor3f(0.0, 191/255.0, 255/255.0);
	drawplane(300.0, 0.0, 300.0, 0.0, -0.8, 0.0);
	
	//Smal blue
	glColor3f(0.0, 0.0, 1.0);
	drawplane(0.2, 0.0, 0.2, 2.0, 0.2, -4.0);
	glPushMatrix();
	glTranslatef(2.0, 0.001, -4.0);
	drawcube(0.2);
	glPopMatrix();

	//yellow cube
	glColor3f(1.0, 1.0, 0.0);
	drawplane(0.5, 0.0, 0.5, 4.0, 0.8, -4.0);
	glPushMatrix();
	glTranslatef(4.0, 0.301, -4.0);
	drawcube(0.5);
	glPopMatrix(); 

	//leaning purple
	glPushMatrix();
	glTranslatef(-3.0, 1.52, 7.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 1.0);
	drawcube(0.5);
	glPopMatrix();

	//big light blue
	glColor3f(0.0, 1.0, 1.0);
	drawplane(1.0, 0.0, 1.0, 4.0, 1.8, 1.0);
	glPushMatrix();
	glTranslatef(4.0, 0.801, 1.0);
	drawcube(1.0);
	glPopMatrix();

	glDisable(GL_LIGHTING);
	//HUD
	//console
	glPopMatrix();
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);

	if (SEND != 0)
		network = cpoint->console(message);
	SEND = cpoint->draw(message, SEND);
	


	//FPS counter
	glColor3f(1.0,1.0,1.0);
	output(2.0, 1.2, -2.0, "FPS: ", 3);
	output(2.13, 1.2, -2.0, FPS, 3);

	//info
	char tmpx[10];
	char tmpy[10];
	char tmpz[10];
	
		sprintf(tmpx,"%0.3f",xpos);
		sprintf(tmpy,"%0.3f",ypos);
		sprintf(tmpz,"%0.3f",zpos);

	output(2.05, 1.4, -2.0, "X:               Y:               Z:", 2);
	output(2.1, 1.4, -2.0, tmpx, 2);
	output(2.3, 1.4, -2.0, tmpy, 2);
	output(2.5, 1.4, -2.0, tmpz, 2);

	glEnable(GL_DEPTH_TEST);

	
	glPopMatrix();

	//time



	colision();
	movement();
	bpoint->Movement();
	if (bpoint->Collision(-Mxpos, -Mypos, -Mzpos)){
	KILL = true;
	cpoint->draw("you killed the enemy", 2);
	Mxpos = 0.0;
	Mypos = -0.8;
	Mzpos = 0.0;
	}

	

	timerstart = clock();


	if ( (clock() - frametime) < 16) {
		waittime = 16-(clock() - frametime);
		//while((clock() - frametime) < waittime){}
	} else {
		//cout << "Get a better GPU!!" << endl;
		//cout << clock() - frametime << endl;
	}
		timerend = clock()-timerstart;
		velocity -= (15/60.0);
		ypos -= (velocity/60.0);

		calcpos();

		
		frames ++;

	



	glutSwapBuffers();
	glutPostRedisplay();
}

void movement(){

	if (movess == 1){
		dir = 90;
		speed = -0.08;
	}
	if (movess == -1){
		dir = 270;
		speed = -0.08;

	}
	if (movefb == 1){
		dir = 0;
		speed = -0.10;
	}

	if (movefb == 2){
		dir = 180;
		speed = 1.0;
	}

	if (movefb == -1){
		dir = 180;
		speed = -0.10;
	}


	if (movess == 1 && movefb == 1){
		dir = 45;
		speed = -0.09;
	}
	if (movess == 1 && movefb == -1){
		dir = 135;
		speed = -0.09;
	}
	if (movess == -1 && movefb == -1){
		dir = 225;
		speed = -0.09;
	}
	if (movess == -1 && movefb == 1){
		dir = 315;
		speed = -0.09;
	}

	if (JUMP){
	velocity += 7;
	JUMP = false;
	}





}

void colision(){

	if (xpos >= -5.0 && xpos <= 5.0 &&
		zpos >= -5.0 && zpos <= 5.0 &&
		ypos > -0.8 && ypos < 1.0){
			ypos = -0.8;
			velocity = 0;
			jump = 0;
		}


	if (xpos >= -5.0 && xpos <= 5.0 &&
		zpos >= -10.0 && zpos <= -5.0 &&
		 ypos >= (zpos+5.0)*0.56-0.8 && ypos <= (zpos+5.0)*0.56 + 1.0){
		
		ypos = (zpos+5.0)*0.56-0.8;
		velocity = 0;
		jump = 0;
	
		
	}


}

void keyboard(unsigned char key, int x, int y){

	if(!WRITING){
		
		if (key == 'd')
			movess = 1;

		if (key == 'a')
			movess = -1;
	
		if (key == 'w')
			movefb = 1;

		if (key == 'r')
			movefb = 2;
	
		if (key == 's')
			movefb = -1;
	
		if (key == ' ' && jump <  20){
			jump++;
			JUMP = true;
		}
	
		if (key == 'x')
			exit(0);
		
		if (key == 'H'){
			spoint->transfer(xpos,ypos,zpos, 2, "192.168.1.15", 25565, Pxpos, Pypos, Pzpos);
			network = 2;
		}

		if (key == 'C'){
			spoint->transfer(xpos,ypos,zpos, 1, "46.236.82.62", 25565, Pxpos, Pypos, Pzpos);
			network = 1;
		}
	
		if (key == 13){
			WRITING = true;
		}
	} else {
		
		char type;
		type = (char)key;

		if (key == 13){
			WRITING = false;
			SEND = 1;
		}
		if (key == 8){
			
			for (int i = 50; i >= 0; i--){

				if (message[i] != 0){
					message[i] = 0;
					i=-1;

				}
				
			}
		} else {



		for (int i = 0; i <= 50; i++){
			if (message[i] < 32){
				message[i] = type;
				break;
			}
				
		}

		}

		//cout << message << endl;
		
		
	}
	
}

void keyboardUP(unsigned char key, int x, int y){

	if(!WRITING){

		if (key == 'd' && movess == 1){
			movess = 0;
			speed = 0;
			dir = 0;
		}
		if (key == 'a' && movess == -1){
			movess = 0;
			speed = 0;
			dir = 0;
		}
		if (key == 'w' && movefb == 1){
			movefb = 0;
			speed = 0;
			dir = 0;
		}
	
		if (key == 's' && movefb == -1){
			movefb = 0;
			speed = 0;
			dir = 0;
		}

	}

}

void cameralock(){

	if (camerapitch > 360)
		camerapitch -= 360;

	if (camerapitch < 0)
		camerapitch += 360;


	if (angle > 360)
		angle -= 360;

	if (angle < 0)
		angle += 360;

	if (camerayaw > 90)
		camerayaw = 90;

	if (camerayaw < -90)
		camerayaw = -90;
		
}




void updateonesec(int value){

	//cout << " x: " << xpos << " y: " << ypos << " z: " << zpos << endl;
	//cout << "camerapitch: " << camerapitch << endl;
	//cout << "camerayaw: " << -camerayaw << endl;

	//cout << "Fps: " << frames << endl;
	//cout << "timer : " << timerend << endl;
	//cout << "succsess " << endl;

	
	itoa(frames, FPS, 10);

	frames = 0;

	glutTimerFunc(1000,updateonesec, 0);
}

void updatefourpersec(int value){

	if (network > 0){
		
	if(KILL){
		if(spoint->transfer(xpos,ypos,zpos, 4, "", 0, Pxpos, Pypos, Pzpos)){
		
			xpos = 0;
			ypos = -0.8;
			zpos = 0;
			cpoint->draw("you were shot!", 2);
			velocity = 0;
		
		}
		KILL = false;
	} else{
		if(spoint->transfer(xpos,ypos,zpos, 3, "", 0, Pxpos, Pypos, Pzpos)){
		
			xpos = 0;
			ypos = -0.8;
			zpos = 0;
			cpoint->draw("you were shot!", 2);
			velocity = 0;
		
		}
	}

	
	}

	glutTimerFunc(1000,updatefourpersec, 0);
}

int main(int iArgc, char** cppargv){
	glutInit( &iArgc, cppargv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("First Person Shooter");
	//FreeConsole();
	glutFullScreen();
	Init();

	glutPassiveMotionFunc(mouse);
	glutMotionFunc(mouse);
	glutMouseFunc(mouseyb);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUP);
	glutDisplayFunc(render);
	glutTimerFunc(1000,updatefourpersec, 0);
	glutTimerFunc(1000,updateonesec, 0);
	glutMainLoop();
	return 0;
}

void output(float x, float y, float z, char *string, int size)
{
  unsigned int  i;
  glRasterPos3f(x, y, z);
  for (i = 0; i < strlen(string); i++)
  {
	  if (size == 1) 
		 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);

	  if (size == 2) 
		 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);

	  if (size == 3)
		  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	  
  }
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}




