#ifndef Particle_H
#define Particle_H


#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
// Random

#include <random>
#include <cstdlib>
#include <ctime>
#include <time.h>

class Particle{
	
	public:

		Particle();
		Particle(double x_,double y_, double vx_, double vy_, double m_, double r_, double ID_);
		~Particle();
		
		double Getd(double x1_,double y1_,double x2_,double y2_);

		void ResetForce();
		void GetForce(Particle &p, int type);

		void MoveVerlet(double t_, double deltat, int it);

		void Print();
		void WritetoFile();
		void CloseFile();

		double GetR();
		

		double GetTheta();

		double GetEk();
		double GetEp();
		double GetPx();
		double GetPy();



	private:


		double t;
		double x,y;

		double xp,yp; //Para verlet

		double vx,vy;
		double px,py;
		double ax,ay;
		double Fx,Fy;
		double Fn;

		double Ep;
		double Ek;

		double d;
		double m,r;

		

		int ID;

		std::ofstream *File;


		// Usando tercera ley de kepler podemos encontrar G
		// O cambio de unidades Gaussiano
		double G = 6.674e-11;
		
		


	protected:


};

#endif
