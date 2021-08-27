#include <../inc/Particle.h>

Particle::Particle(){
}

Particle::Particle(double x_,double y_, double vx_, double vy_, double m_, double r_, double ID_): x(x_), y(y_), vx(vx_), vy(vy_), m(m_), r(r_), ID(ID_){
 
}

Particle::~Particle(){
}

// Methods

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

void Particle::Move(double t_, double deltat, int it){


	t = t_;
	
	x += vx*deltat;
	y += vy*deltat;

}

