#pragma once
class bullet
{
public:
	int nextbullet;
	float Bulletcoordx[1000];
	float Bulletcoordy[1000];
	float Bulletcoordz[1000];
	float Bulletpitch[1000];
	float Bulletyaw[1000];
	void Initbullet(float yaw, float pitch, float x, float y, float z);
	void Movement();
	int Collision(float x, float y, float z);
private:
	float speed;
	double PI;
};

