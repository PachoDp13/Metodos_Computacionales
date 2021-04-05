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
		double K = 100.;
		double Interaccion(Particle *p_);
		void Move(double t_, double deltat, double newA[]);
	
		double getX();
		double getY();
		double getVx();
		double getVy();
		double getR();
		double getM();
		int getID();
		void setA(double ax_ , double ay_);

		

	private:

		double x,y;
		double t;
		double vx,vy;
		double ax,ay;
		double Fx,Fy;
		double Ep;

		double m,r;

		int ID;

		double Wxmin,Wxmax;
		double Wymin,Wymax;

		
		

	protected:


};

#endif
