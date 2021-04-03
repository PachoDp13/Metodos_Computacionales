#include <../inc/Particle.h>
#include <string>

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
int Particle::darID()
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
    double rx = x - p_->PosX();
    double ry = y - p_->PosY();
    double d = sqrt(pow(rx,2) + pow(ry,2));
	
    if (d < (r + p_->Radius()) )
	{
		return K*(pow(d,5));
	}
	else
	{
		return 0;
	}
}
void Particle::UpdateAceleracion(Particle *AllParticles[], int NParticles)
{	
	double new_ax = 0;
	double new_ay = 0;
	for(int i = 0; i< NParticles; i++)
	{	if(AllParticles[i]->darID() != ID)
		{
			Particle *p_ = AllParticles[i];
			double rx = x - p_->PosX();
			double ry = y - p_->PosY();
			double norm = sqrt(pow(ry,2) + pow(rx,2));
			double interaccion = Interaccion(p_);
			if (norm != 0 and norm != 0)
			{
				double coef = norm*m;
				new_ax += interaccion*rx/coef;
				new_ay += interaccion*ry/coef;
			}
			else
			{
				double coef = m;
				new_ax += interaccion*rx/coef;
				new_ay += interaccion*ry/coef;
			}
		}
	}
	ax = new_ax;
	ay = new_ay;	
}

