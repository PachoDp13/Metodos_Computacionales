#include <../inc/Particle.h>
#include <string>

Particle::Particle(){
}

Particle::Particle(double x_,double y_, double vx_, double vy_, double m_, double r_, double ID_): x(x_), y(y_), vx(vx_), vy(vy_), m(m_), r(r_), ID(ID_){
 
}

Particle::~Particle(){
}

// Methods

double Particle::getX()
{
	return x;
}
double Particle::getY()
{
	return y;
}
double Particle::getVx()
{
	return vx;
}
double Particle::getVy()
{
	return vy;
}
double Particle::getR()
{
	return r;
}
double Particle::getM()
{
	return m;
}
int Particle::getID()
{
	return ID;
}

void Particle::SetWallLimits(double Wxmin_, double Wxmax_, double Wymin_, double Wymax_)
{
Wxmin = Wxmin_;
Wxmax = Wxmax_;
Wymin = Wymin_;
Wymax = Wymax_;
}

void Particle::CheckWallLimits()
{

	if( (x+r) >= Wxmax || (x-r) <= Wxmin ) vx = -vx;
	if( (y+r) >= Wymax || (y-r) <= Wymin ) vy = -vy;

}

void Particle::Print(){
 std::cout <<" , "<<x<<"+"<<r<<"*cos(t),"<<y<<"+"<<r<<"*sin(t)";
}


void Particle::Move(double t_, double deltat, double newA[])
{
	t = t_;
	x += (vx*deltat) + (0.5*ax*pow(deltat,2));
	y += (vy*deltat) + (0.5*ay*pow(deltat,2));
	vx += (ax+newA[0])*(deltat/2);
	vy += (ay+newA[1])*(deltat/2);
	ax = newA[0];
	ay = newA[1];
}




