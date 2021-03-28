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
double Particle::MyK()
{
	return K;
}
double Particle::Mym()
{
	return m;
}
int Particle::darID()
{
	return ID;
}

void Particle::SetWallLimits(double Wxmin_, double Wxmax_, double Wymin_, double Wymax_){
Wxmin = Wxmin_;
Wxmax = Wxmax_;
Wymin = Wymin_;
Wymax = Wymax_;
}

void Particle::CheckWallLimits(){

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

bool Particle::Intersects(Particle *p_)
{
    double dx = abs(x - p_->PosX());
    double dy = abs(y - p_->PosY());
    double d = sqrt(dx * dx + dy * dy);
    if (d <= (r + p_->Radius()) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Particle::Colision(Particle *p_, bool state)
{
	//double m1 = p_1->Mym();
	//double m2 = p_2->Mym();
	//double vx1 = p_1->darVx();
	//double vx2 = p_2->darVx();
	//double vy1 = p_1->darVy();
	//double vy2 = p_2->darVy();
	//double vx = (m1 - m2) * vx1 / (m1 + m2) + 2 * m2 * vx2 / (m1 + m2);
	//double vy = (m1 - m2) * vy1 / (m1 + m2) + 2 * m2 * vy2 / (m1 + m2);

	double dx = abs(x - p_->PosX());
    double dy = abs(y - p_->PosY());
    double d = sqrt(dx * dx + dy * dy);

	double rx = x - p_->PosX();
	double ry = y - p_->PosY();

	ax += K*(pow(d,5))*rx;
	ay += K*(pow(d,5))*ry;

	if(state)
	{
		Colision(this, false);
	}
}

void Particle::RevisarColisiones(Particle *particles[], int NParticles_)
{
	for (int i = 0; i< NParticles_; i++)
	{	
		if(particles[i] ->darID() != ID and Intersects(particles[i]))
		{
			Colision(particles[i], true);
		}
	}

	}

