#include <../inc/Particle.h>
#include<iostream>
#include<fstream>
#include <iterator>


void StartAnim(double limits)
{
	std::cout<<"set terminal gif animate delay 5"<<std::endl;
    std::cout<<"set output 'Colisiones.gif'"<<std::endl;
	std::cout<<"unset key"<<std::endl;
  	std::cout<<"set xrange [-"<<limits << ":"<<limits <<"]"<<std::endl;
  	std::cout<<"set yrange [-"<<limits << ":"<<limits <<"]"<<std::endl;
 	std::cout<<"set size ratio 1"<<std::endl;
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
	double r = ((double) rand() / (RAND_MAX));
	return a+(b-a)*r;
}

int main(int argc, char *argv[]){

	//Parámetros de entrada:
	int NParticles = std::stof(argv[1]);
	double tmax = std::stof(argv[2]);
	double deltat = std::stof(argv[3]);
	double limits = std::stof(argv[4]);
	int films = std::stof(argv[5]);
	
	Particle *AllParticles[NParticles];

	if (NParticles ==2)
	{
		Particle *p1 = new Particle(-10.0,4,40.0,0.0,10.0,5.0,0);
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
			Particle *p = new Particle(Random(-46,46),Random(-46,46),Random(-50,50),Random(-50,50),10,4,i);
			p->SetWallLimits(-limits,limits,-limits,limits);
			AllParticles[i] = p;
			
		}
	}
	std::ofstream out;
    out.open("data/data.dat", std::ofstream::trunc);

	// Evolucion 
	double time = 0.;
	int it = 0;
	// 
	StartAnim(limits);
	while (time < tmax)
	{
		double Ek = 0;
		double Ep = 0;
		double Px = 0;
		double Py = 0;
        if(it%films == 0)
		{
			StartLine();
		}
		for(int i = 0; i< NParticles; i++)
		{
			AllParticles[i]->UpdateAceleracion(AllParticles, NParticles);
		}


		for(int i = 0; i< NParticles; i++)
		{		
			AllParticles[i]->CheckWallLimits();
			AllParticles[i]->Move(time,deltat,it);		    			
	
        	if(it%films == 0)
			{	
				AllParticles[i]->Print();
				
			}
			
			Px +=  AllParticles[i]->darM()*AllParticles[i]->darVx() ;
			Py +=  AllParticles[i]->darM()*AllParticles[i]->darVy() ;
			Ek += (0.5)*(AllParticles[i]->darM())*(pow(AllParticles[i]->darVy(),2)+pow(AllParticles[i]->darVy(),2));
		}
		time += deltat;
		it ++;
        if(it%films == 0)	
			EndLine();

		// out << Px << " " << Py  << " " << Ek << " " << Ep << std::endl;
	}

	out.close();
	return 0;
}	
