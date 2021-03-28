#include <../inc/Particle.h>

void StartAnim(){

  //std::cout<<"set terminal gif transparent animate nooptimize delay 10 size 300,300 font 'Helvetica-Bold,10'"<<std::endl;
  
  	
	std::cout<<"set terminal pngcairo"<<std::endl;
    std::cout<<"set output 'Colisiones.png'"<<std::endl;
	std::cout<<"unset key"<<std::endl;
  	std::cout<<"set xrange [-50:50]"<<std::endl;
  	std::cout<<"set yrange [-50:50]"<<std::endl;
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


	Particle *p1 = new Particle(2,3,2,3.3,5,6,0);
	p1->SetWallLimits(-50,50,-50,50);



	// Evolucion 
	double time = 0.;
	double deltat = 0.0001;

	double tmax = std::stof(argv[1]);
	int it = 0;

        int films = 5000;

        
	int NParticles = 20;

	srand48(0);


	Particle *AllParticles[NParticles];

	for(int i = 0; i< NParticles; i++){
		Particle *p = new Particle(2*drand48(),3*drand48(),2*drand48(),3.3,5,6,i);
		p->SetWallLimits(-50,50,-50,50);
		AllParticles[i] = p;
	}


	// Evolucion
	
	// 
	
	while (time < tmax){

        if(it%films == 0){
	 StartAnim();
	StartLine();
	}

	for(int i = 0; i< NParticles; i++){
		
		AllParticles[i]->Move(time,deltat,it);
		AllParticles[i]->CheckWallLimits();
	

	//p1->Move(time,deltat,it);
	//p1->CheckWallLimits();

        if(it%films == 0)
	{
	//p1->Print();
	
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
