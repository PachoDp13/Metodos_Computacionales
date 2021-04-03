#include <../inc/Particle.h>
#include<iostream>
#include<fstream>


void StartAnim(double limits, double delay)
{
	std::cout<<"set terminal gif animate delay "<<delay <<std::endl;
    std::cout<<"set output 'data/Colisiones.gif'"<<std::endl;
	std::cout<<"unset key"<<std::endl;
  	std::cout<<"set xrange [-"<<limits << ":"<<limits <<"]"<<std::endl;
  	std::cout<<"set yrange [-"<<limits << ":"<<limits <<"]"<<std::endl;
 	std::cout<<"set size ratio -1"<<std::endl;
  	std::cout<<"set parametric"<<std::endl;
  	std::cout<<"set trange [0:7]"<<std::endl;
  	std::cout<<"set isosamples 12"<<std::endl;
}
void StartLine()
{
    std::cout <<"plot 0,0";
}
void EndLine()
{
    std::cout<<std::endl;
}
double Random(double a, double b)
{	
    return a+(b-a)*drand48();
}
void PlotGraph(double t)
{	std::cout<<std::endl;
	std::cout<<"set terminal pngcairo"<<std::endl;
    std::cout<<"set output 'data/MomentumX.png'"<<std::endl;
	std::cout<<"unset key"<<std::endl;
	std::cout<<"set title 'Momento lineal (P_{x})'"<<std::endl;
	std::cout<<"set xrange [0:"<<t<<"]"<<std::endl;
  	std::cout<<"set yrange [*:*]"<<std::endl;
 	std::cout<<"set size ratio 1"<<std::endl;
  	std::cout<<"set isosamples 12"<<std::endl;
	std::cout<<"plot 'data/data.dat' using 1:2 with dots"<<std::endl;

	std::cout<<"set terminal pngcairo"<<std::endl;
    std::cout<<"set output 'data/MomentumY.png'"<<std::endl;
	std::cout<<"unset key"<<std::endl;
	std::cout<<"set title 'Momento lineal (P_{y})'"<<std::endl;
	std::cout<<"set xrange [0:"<<t<<"]"<<std::endl;
  	std::cout<<"set yrange [*:*]"<<std::endl;
 	std::cout<<"set size ratio 1"<<std::endl;
  	std::cout<<"set isosamples 12"<<std::endl;
	std::cout<<"plot 'data/data.dat' using 1:3 with dots"<<std::endl;

	std::cout<<"set terminal pngcairo"<<std::endl;
    std::cout<<"set output 'data/Energía cinética.png'"<<std::endl;
	std::cout<<"unset key"<<std::endl;
	std::cout<<"set title 'Energía cinética (E_{k})'"<<std::endl;
	std::cout<<"set xrange [0:"<<t<<"]"<<std::endl;
  	std::cout<<"set yrange [*:*]"<<std::endl;
 	std::cout<<"set size ratio 1"<<std::endl;
  	std::cout<<"set isosamples 12"<<std::endl;
	std::cout<<"plot 'data/data.dat' using 1:4 with dots"<<std::endl;
	 
	std::cout<<"set terminal pngcairo"<<std::endl;
    std::cout<<"set output 'data/Energía potencial.png'"<<std::endl;
	std::cout<<"unset key"<<std::endl;
	std::cout<<"set title 'Energía potencial (E_{p})'"<<std::endl;
	std::cout<<"set xrange [0:"<<t<<"]"<<std::endl;
  	std::cout<<"set yrange [-20000:20000]"<<std::endl;
 	std::cout<<"set size ratio 1"<<std::endl;
  	std::cout<<"set isosamples 12"<<std::endl;
	std::cout<<"plot 'data/data.dat' using 1:5 with dots"<<std::endl;

}

int main(int argc, char *argv[]){

	//Parámetros de entrada:
	int NParticles = std::stof(argv[1]);
	double tmax = std::stof(argv[2]);
	double deltat = std::stof(argv[3]);
	double limits = std::stof(argv[4]);
	int fps = std::stof(argv[5]);
	
	Particle *AllParticles[NParticles];
	srand48(time(0));

	if (NParticles ==2)
	{
		Particle *p1 = new Particle(-10.0,4,4.0,0.0,10.0,5.0,0);
		p1->SetWallLimits(-limits,limits,-limits,limits);
		Particle *p2 = new Particle(0.0,0,0.0,0,10.0,5.0,1);
		p2->SetWallLimits(-limits,limits,-limits,limits);
		AllParticles[0] = p1;
		AllParticles[1] = p2;
	}
	else
	{	
		for(int i = 0; i< NParticles; i++)
		{
			Particle *p = new Particle(Random(-46,46),Random(-46,46),Random(-5,5),Random(-5,5),10,4,i);
			p->SetWallLimits(-limits,limits,-limits,limits);
			AllParticles[i] = p;
			
		}
	}
	std::ofstream out;
    out.open("data/data.dat", std::ofstream::trunc);

	// Evolucion 
	double time = 0.;
	int it = 0;
	int frames = (tmax/deltat)/fps;
	int delay = (tmax/frames)*100;
	StartAnim(limits, delay);
	while (time < tmax)
	{
		double Ek = 0;
		double Ep = 0;
		double Px = 0;
		double Py = 0;
        if(it%fps == 0)
		{
			StartLine();
		}
		
		for(int i = 0; i< NParticles; i++)
		{	
			AllParticles[i]->setA(0,0);
		}

		for(int i = 0; i< NParticles; i++)
		{	
			for(int j = i+1;j < NParticles; j++)
			{	
				Particle *p1 = AllParticles[i]; Particle *p2 = AllParticles[j];
				double rx = p1->getX() - p2->getX();
				double ry = p1->getY() - p2->getY();
				double d = sqrt(pow(ry,2) + pow(rx,2));
				double interaccion =0;
				if (d < p1->getR() + p2->getR()) 
				{
					interaccion = p1->K*(pow(d,1.5));
					Ep+=p1->K/2.5*(pow(d,2.5));
				}
				if (d != 0)
				{
					double coef1 = d*p1->getM();
					double coef2 = d*p2->getM();
					p1->setA(p1->getAx()+interaccion*rx/coef1,p1->getAy()+ interaccion*ry/coef1);
					p2->setA(p2->getAx()+-interaccion*rx/coef2, p2->getAy()+-interaccion*ry/coef2);
					
				}
			}
			AllParticles[i]->CheckWallLimits();
			AllParticles[i]->Move(time,deltat,it);		    			
        	if(it%fps == 0)
			{	
				AllParticles[i]->Print();
			}	
			Px +=  AllParticles[i]->getM()*AllParticles[i]->getVx() ;
			Py +=  AllParticles[i]->getM()*AllParticles[i]->getVy() ;
			Ek += (0.5)*(AllParticles[i]->getM())*(pow(AllParticles[i]->getVx(),2)+pow(AllParticles[i]->getVy(),2));
		}
		time += deltat;
		it ++;
        if(it%fps == 0)
		{
			EndLine();
			
			
			
		}
		out << time << " " << Px << " " << Py  << " " << Ek << " " << Ep << std::endl;
		
		 
	}

	out.close();
	PlotGraph(tmax);
	return 0;
}	
