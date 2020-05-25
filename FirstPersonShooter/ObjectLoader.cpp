#include "ObjectLoader.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <assert.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include "glut.h"



using namespace std;

int ObjectLoader::loadObject(const char* filename,const char* materialname){
        std::vector<std::string*> coord;  
		std::vector<std::string*> cooord; //read every single line of the obj file as a string
        std::vector<coordinate*> vertex;
        std::vector<face*> faces;
        std::vector<coordinate*> normals;       //normal vectors for every face
        std::ifstream in(filename);     //open the .obj file
        if(!in.is_open())       //if not opened, exit with -1
        {
                std::cout << "Could not open object" << std::endl;
                return -1;
        }
        char buf[256];
		int faace=0;
		int curmat=0;
		string materialnames;
        //read in every line to coord
        while(!in.eof())
        {
                in.getline(buf,256);
                coord.push_back(new std::string(buf));
        }
        //go through all of the elements of coord, and decide what kind of element is that
        for(unsigned int i=0;i<coord.size();i++)
        {
                if(coord[i]->c_str()[0]=='#')   //if it is a comment (the first character is #)
                        continue;       //we don't care about that
                else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' ') //if vector
                {
                        float tmpx,tmpy,tmpz;
                        sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);       //read in the 3 float coordinate to tmpx,tmpy,tmpz
                        vertex.push_back(new coordinate(tmpx,tmpy,tmpz));       //and then add it to the end of our vertex list
                }else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n')        //if normal vector
                {
                        float tmpx,tmpy,tmpz;   //do the same thing
                        sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
                        normals.push_back(new coordinate(tmpx,tmpy,tmpz)); 

                }else if(coord[i]->c_str()[0]=='f')     //if face
                {
                        int a,b,c,d,e;
                        if(count(coord[i]->begin(),coord[i]->end(),' ')==3)     //if it is a triangle (it has 3 space in it)
						
                        {


								sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
                                faces.push_back(new face(b,a,c,d));     //read in, and add to the end of the face list



                        }else{
                                sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
                                faces.push_back(new face(b,a,c,d,e));   //do the same, except we call another constructor, and we use different pattern
                        }

				faace++;

                }else if(coord[i]->c_str()[0]=='u' && coord[i]->c_str()[1]=='s'&& coord[i]->c_str()[3]=='m')        //if normal vector
                {
                       

                }else if(coord[i]->c_str()[0]=='m' && coord[i]->c_str()[1]=='t')        //if material
                {
					std::ifstream fin(materialname);     //open the .mtl file
					 if(!fin.is_open())       //if not opened, exit with -1
					{
						std::cout << "Could not find material" << std::endl;
						return -1;
					}

					 int mater=0;
					 char buff[256];
				//read in every line to coord
				  while(!fin.eof())
				 {
					fin.getline(buff,256);
					cooord.push_back(new std::string(buff));  
				}
				  for(unsigned int i=0;i<cooord.size();i++){

					
				  }
					if(cooord[i]->c_str()[0]=='K' && cooord[i]->c_str()[1]=='d') {
						float r,g,bl;
	
						sscanf(cooord[i]->c_str(),"Kd %f %f %f",&r,&g,&bl);
						materialred[mater] = r;
						materialgreen[mater] = g;
						materialblue[mater] = bl;
						//cout << materialred[0] << " " << materialgreen[0] << " " << materialblue[0] << endl; 
						mater++;
						
					}
				  
				  
				  
				  
                          
                }
				
				
        }
	
//raw
        int num;        //the id for the list
        num=glGenLists(1);      //generate a uniqe
        glNewList(num,GL_COMPILE);      //and create it
        for(unsigned int i=0;i<faces.size();i++)
        {

			if (i > 0)
				glColor3f(100/255.0, 50/255.0, 0/255.0);

			if (i > 48)
				glColor3f(0/255.0, 100/255.0, 0/255.0);

			if (i > 186)
				glColor3f(255/255.0, 255/255.0, 255/255.0);

			if (i > 268)
				glColor3f(100/255.0, 50/255.0, 0/255.0);

			if (i > 848)
				glColor3f(200/255.0, 200/255.0, 0/255.0);

			if (i > 1044)
				glColor3f(100/255.0, 50/255.0, 0/255.0);

			if (i > 1671)
				glColor3f(200/255.0, 200/255.0, 0/255.0);

			if (i > 1969)
				glColor3f(30/255.0, 30/255.0, 60/255.0);





                if(faces[i]->four)      //if it's a quad draw a quad
                {
                        glBegin(GL_QUADS);
                                //basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
                                //I subtract 1 because the index start from 0 in C++
                                glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
                                //draw the faces
                                glVertex3f((vertex[faces[i]->faces[0]-1]->x),vertex[faces[i]->faces[0]-1]->y,(vertex[faces[i]->faces[0]-1]->z));
                                glVertex3f((vertex[faces[i]->faces[1]-1]->x),vertex[faces[i]->faces[1]-1]->y,(vertex[faces[i]->faces[1]-1]->z));
                                glVertex3f((vertex[faces[i]->faces[2]-1]->x),vertex[faces[i]->faces[2]-1]->y,(vertex[faces[i]->faces[2]-1]->z));
                                glVertex3f((vertex[faces[i]->faces[3]-1]->x),vertex[faces[i]->faces[3]-1]->y,(vertex[faces[i]->faces[3]-1]->z));
                        glEnd();
                }else{

                        glBegin(GL_TRIANGLES);
                                glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
                                glVertex3f((vertex[faces[i]->faces[0]-1]->x),vertex[faces[i]->faces[0]-1]->y,(vertex[faces[i]->faces[0]-1]->z));
                                glVertex3f((vertex[faces[i]->faces[1]-1]->x),vertex[faces[i]->faces[1]-1]->y,(vertex[faces[i]->faces[1]-1]->z));
                                glVertex3f((vertex[faces[i]->faces[2]-1]->x),vertex[faces[i]->faces[2]-1]->y,(vertex[faces[i]->faces[2]-1]->z));
                        glEnd();
                }
        }
        glEndList();
        //delete everything to avoid memory leaks
        for(unsigned int i=0;i<coord.size();i++)
                delete coord[i];
		for(unsigned int i=0;i<cooord.size();i++)
                delete cooord[i];
        for(unsigned int i=0;i<faces.size();i++)
                delete faces[i];
        for(unsigned int i=0;i<normals.size();i++)
                delete normals[i];
        for(unsigned int i=0;i<vertex.size();i++)
                delete vertex[i];
        return num;     //return with the id
}