#include <../inc/Particle.h>

Particle::Particle(){
}

Particle::Particle(double x_,double y_, double vx_, double vy_, double m_, double r_, double ID_): x(x_), y(y_), vx(vx_), vy(vy_), m(m_), r(r_), ID(ID_){
 
}

Particle::~Particle(){
}

// Methods

double Particle::PosX()
{
	return x;
}
double Particle::PosY()
{
	return y;
}
double Particle::darVx()
{
	return vx;
}
double Particle::darVy()
{
	return vy;
}
double Particle::Radius()
{
	return r;
}
double Particle::darM()
{
	return m;
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
	x += vx*deltat + 0.5*ax*pow(deltat,2);
	y += vy*deltat + 0.5*ay*pow(deltat,2);
	vx += ax*deltat;
	vy += ay*deltat;
}

double Particle::Interaccion(Particle *p_)
{
    double dx = x - p_->PosX();
    double dy = y - p_->PosY();
    double d = sqrt(pow(dx,2) + pow(dy,2));
	
    if (d <= (r + p_->Radius()) )
	{
		return K*(pow(d,5));
	}
	else
	{
		return 0;
	}
}

void Particle::Colision(Particle *p_, bool state)
{
	double rx = x - p_->PosX();
	double ry = y - p_->PosY();
	double norm = (sqrt(pow(ry,2) + pow(rx,2)));
	if(state)
	{
		p_->Colision(this, false);
	}
	double interaccion = Interaccion(p_);
	if (norm != 0 and norm != 0)
	{
		double coef = pow(norm*m, -1);
		ax = interaccion*rx*coef;
		ay = interaccion*ry*coef;
	}
	else
	{
		double coef = pow(m,-1);
		ax = interaccion*coef;
		ay = interaccion*coef;
	}
	
}

