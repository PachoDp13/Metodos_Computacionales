#ifndef Particle_H
#define Particle_H


#include <iostream>
#include <fstream>
#include <math.h>
// Random

#include <random>
#include <cstdlib>
#include <ctime>

class Particle{
	
	public:
		Particle();
		Particle(double x_,double y_, double vx_, double vy_, double m_, double r_, double ID_);
		~Particle();

		void SetWallLimits(double Wxmin_, double Wxmax_, double Wymin_, double Wymax_);
		void CheckWallLimits();
		void Print();

		void Move(double t_, double deltat, int it);

		bool Intersects(Particle *p_);
		

		double PosX();
		double PosY();
		double darVx();
		double darVy();
		double Radius();
		double Mym();
		double MyK();
		int darID();
		
		void RevisarColisiones(Particle *particles[], int NParticles_);

	private:

		double x,y;
		double t;
		double vx,vy;
		double ax,ay;
		double Fx,Fy;

		double m,r;

		int ID;

		std::ofstream *File;

		double Wxmin,Wxmax;
		double Wymin,Wymax;

		double K = 100.;
		void Colision(Particle *p_, bool state);

	protected:


};

#endif
