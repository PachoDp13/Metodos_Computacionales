#include <../inc/Particle.h>

void StartAnim(double limits){

  //std::cout<<"set terminal gif transparent animate nooptimize delay 10 size 300,300 font 'Helvetica-Bold,10'"<<std::endl;
  
  	
	std::cout<<"set terminal gif animate delay 5"<<std::endl;
    std::cout<<"set output 'Colisiones.gif'"<<std::endl;
	std::cout<<"unset key"<<std::endl;
  	std::cout<<"set xrange [-"<<limits << ":"<<limits <<"]"<<std::endl;
  	std::cout<<"set yrange [-"<<limits << ":"<<limits <<"]"<<std::endl;
 	std::cout<<"set size ratio -1"<<std::endl;
  	std::cout<<"set parametric"<<std::endl;
  	std::cout<<"set trange [0:7]"<<std::endl;
  	std::cout<<"set isosamples 12"<<std::endl;


}

void StartLine(){
        std::cout <<"plot 0,0";
}

void EndLine(){
        std::cout<<std::endl;
}

int main(int argc, char *argv[]){






	
	//Parámetros de entrada:
	int NParticles = std::stof(argv[1]);
	double tmax = std::stof(argv[2]);
	double deltat = std::stof(argv[3]);
	double limits = std::stof(argv[4]);
	int films = std::stof(argv[5]);

        

	srand48(0);


	Particle *AllParticles[NParticles];

	if (NParticles ==2)
	{
		Particle *p1 = new Particle(-10.0,0,4.0,0.0,10.0,1.0,0);
		p1->SetWallLimits(-limits,limits,-limits,limits);
		Particle *p2 = new Particle(0.0,0,0.0,0,10.0,1.0,1);
		p2->SetWallLimits(-limits,limits,-limits,limits);
		AllParticles[0] = p1;
		AllParticles[1] = p2;
	}
	else
	{	
		for(int i = 0; i< NParticles; i++)
		{
			Particle *p = new Particle(96*drand48()-48,96*drand48()-48,200*drand48()-100,200*drand48()-100,10,4,i);
			p->SetWallLimits(-limits,limits,-limits,limits);
			AllParticles[i] = p;
		}
	}


	// Evolucion 
	double time = 0.;
	int it = 0;
	// 
	StartAnim(limits);
	while (time < tmax)
	{

        if(it%films == 0)
		{
	 		
			StartLine();
		}

		for(int i = 0; i< NParticles; i++)
		{
			
			AllParticles[i]->Move(time,deltat,it);	
			
			AllParticles[i]->RevisarColisiones(AllParticles, NParticles);
			AllParticles[i]->CheckWallLimits();
			

        	if(it%films == 0)
			{	
				AllParticles[i]->Print();
			}

		}

		time += deltat;
		it ++;
        if(it%films == 0)	
			EndLine();
	}
	return 0;
}	
