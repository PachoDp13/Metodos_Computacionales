#include <../inc/Particle.h>

Particle::Particle(){
}

Particle::Particle(double x_,double y_, double vx_, double vy_, double m_, double r_, double ID_): x(x_), y(y_), vx(vx_), vy(vy_), m(m_), r(r_), ID(ID_){

       Fx = Fy = 0.;
       ax = Fx/m;
       ay = Fy/m;

       Ep = 0.;

       std::string Folder = "data/";

       Folder += std::to_string(ID) +".dat";

       File = new std::ofstream[1];

       File[0].open(Folder.c_str(), std::ofstream::trunc);

       //Unidades Gaussianas


       G /= pow(1.496e+11, 3); // Distancia Tierra Sol en m
	   G *= pow(1.989e+30,1); // Masa Solar en kg
	   G /= pow(1.157e-5,2); // 1 segundo en Dias

	   // Usando Tercera Ley de Kepler
		//G = 4*pow(2.0*asin(1.0),2)/pow(365.2421,2);
		G = 4*pow(2.0*asin(1.0),2);

}

Particle::~Particle(){
}

// Methods


double Particle::Getd(double x1_,double y1_,double x2_,double y2_){
double d=0.;
d = sqrt(pow( x2_-x1_ ,2) + pow( y2_-y1_ ,2));
return d;
}

void Particle::ResetForce(){
ax = Fx = 0.;
ay = Fy = 0.;
Ep = 0.;
}


void Particle::GetForce(Particle &p, int type){

	d = Getd(x,y,p.x,p.y);
	
 
	if(type == 1){

		if(d >= 2.0*r){

		Fn = (-G*m*p.m/pow(d,2))*(1+((1.1e-8)/pow(d,2)));

		Fx += -Fn*(p.x-x)/d;
		Fy += -Fn*(p.y-y)/d;

		ax += Fx/m;
		ay += Fy/m;

		Ep = -G*m*p.m/pow(d,1);

		}

	}

}


void Particle::MoveVerlet(double t_, double deltat, int it){

	t = t_;


	if(it == 0){

		xp = x;
		yp = y;

		x = xp + vx*deltat;
		y = yp + vy*deltat;

	}

	else{

		
		double xf = 2.0*x - xp + ax*pow(deltat,2);
		double yf = 2.0*y - yp + ay*pow(deltat,2);

		// actualizamos velocidad
		vx = (xf-xp)/(2.*deltat);
		vy = (yf-yp)/(2.*deltat);

		px = m*vx;
		py = m*vy;

		xp = x;
		yp = y;

		x = xf;
		y = yf;

	}

}


void Particle::Print(){
std::cout <<","<<x<<"+"<<r<<"*cos(t),"<<y<<"+"<<r<<"*sin(t)";
}


void Particle::WritetoFile(){

	File[0] << t << " "
		<< x << " "
		<< y << " "
		<< GetR() << " "
		<< GetTheta() << " " 
	    << vx << " "
	    << vy << " "
	  //  << sqrt(pow(vx,2)+pow(vy,2)) << " "
	  //  << pow(vx,2)+pow(vy,2) << " "
	  //  << GetPx() << " " 
	  //  << GetPy() << " "
	  //  << GetEp() << " " 	
	  //  << GetEk() << " " 
	  //  << Fx << " " 
	  //  << Fy << " "
		<< std::endl;

}

void Particle::CloseFile(){
File[0].close();
}

double Particle::GetEk(){
	return 0.5*m*(pow(vx,2)+pow(vy,2));
}

double Particle::GetEp(){
	return Ep;
}

double Particle::GetPx(){
	return px;
}

double Particle::GetPy(){
	return py;
}

double Particle::GetR(){
	return sqrt(pow(x,2)+pow(y,2));

}


double Particle::GetTheta(){

	double theta = 0.;

	if ( (x > 0.) && (y > 0.) )
		theta = atan(y/x);
	else if( (x < 0.) && (y > 0.) )
		theta = atan(y/x) + 2.0*asin(1.0);
	else if( (x < 0.) && (y < 0.) )
		theta = atan(y/x) + 2.0*asin(1.0);
	else
		theta = atan( y/x ) + 4.0*asin(1.0);

	return theta*180./(2.0*asin(1.0));
}