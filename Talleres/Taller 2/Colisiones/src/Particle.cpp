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
double Particle::getAx()
{
	return ax;
}
double Particle::getAy()
{
	return ay;
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
void Particle::setA(double ax_ , double ay_)
{
	ax = ax_;
	ay = ay_;
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

void Particle::Move(double t_, double deltat, int it)
{
	t = t_;
	x += (vx*deltat) + (0.5*ax*pow(deltat,2));
	y += (vy*deltat) + (0.5*ay*pow(deltat,2));
	vx += ax*deltat;
	vy += ay*deltat;
}

double Particle::Interaccion(Particle *p_)
{
    double rx = x - p_->getX();
    double ry = y - p_->getY();
    double d = sqrt(pow(rx,2) + pow(ry,2));
	
    if (d < (r + p_->getR()) )
	{
		return K*(pow(d,5));
	}
	else
	{
		return 0;
	}
}


