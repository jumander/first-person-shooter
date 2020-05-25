#include "bullet.h"
#include <iostream>
#include <cmath>


void bullet::Initbullet(float yaw, float pitch, float x, float y, float z){



	Bulletyaw[nextbullet] = -yaw*(PI/180);
	Bulletpitch[nextbullet] = pitch*(PI/180);
	Bulletcoordx[nextbullet] = -x;
	Bulletcoordy[nextbullet] = -y;
	Bulletcoordz[nextbullet] = -z;
	
	
	nextbullet++;
	if (nextbullet > 1000)
		nextbullet = 0;
}

void bullet::Movement(){
	PI = 3.14159265;
	speed = 0.5;
	for(int i = 0; i <= 1000; i++){
	
		if(Bulletcoordx[i] != 0.0 && Bulletcoordy[i] != 0.0 && Bulletcoordz[i] != 0.0){
			
			Bulletcoordx[i] = Bulletcoordx[i] + ( speed * sin(Bulletpitch[i]) ) * cos(Bulletyaw[i]);

			Bulletcoordy[i] = Bulletcoordy[i] +  speed  * sin(Bulletyaw[i]);

			Bulletcoordz[i] = Bulletcoordz[i] - ( speed * cos(Bulletpitch[i]) ) * cos(Bulletyaw[i]);
		}
	}

}

int bullet::Collision(float x, float y, float z){

	for(int i = 0; i <= 1000; i++){
		if(Bulletcoordx[i] != 0.0 && Bulletcoordy[i] != 0.0 && Bulletcoordz[i] != 0.0){
			if(Bulletcoordx[i] >= x-0.25 && Bulletcoordx[i] <= x+0.25){
				if(Bulletcoordz[i] >= z-0.25 && Bulletcoordz[i] <= z+0.25){
					if(Bulletcoordy[i] >= y-0.25 && Bulletcoordy[i] <= y+0.25){
						return 1;
		
		
					}
				}
			}
		} 
	}
	
	return 0;
}