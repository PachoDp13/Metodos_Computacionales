#include <../inc/Particle.h>
#include <../inc/Anim.h>



std::ofstream *File;


int main(int argc, char *argv[]){

	// Seed
	srand48(time(0));

	// Output File for the Energy and Momentum
	std::string Folder = "data/";
	std::string File1 = Folder + "Totales.dat";
	std::string File2 = Folder + "Afelio.dat";
	std::string File3 = Folder + "Perihelio.dat";
	File = new std::ofstream[3];
	File[0].open(File1.c_str(), std::ofstream::trunc);
	File[1].open(File2.c_str(), std::ofstream::trunc);
	File[2].open(File3.c_str(), std::ofstream::trunc);


	// Parametros de la simulacion
	int NParticles = std::stoi(argv[1]);
	double tmax = std::stof(argv[2]);
	double deltat = std::stof(argv[3]);
	int Fuerza = std::stoi(argv[4]);
	double limits = std::stof(argv[5]);
	int fps = std::stoi(argv[6]);
	bool Animate = std::stoi(argv[7]);

	tmax = tmax;

	// objetos
	Anim *A = new Anim(limits);
  //  A->StartLine();
  //  A->EndLine();
	Particle *AllParticles[NParticles];

	// G en unidades Gaussianas
	double G = 6.674e-11;
	G /= pow(1.496e+11, 3); // Distancia Tierra Sol en 
	G *= 1.989e+30; // 1 Masa Solar en Kg
	G /= pow(1.157e-5,2); // 1 segudos en dias
	// Usando Tercera Ley de Kepler
	//G = 4*pow(2.0*asin(1.0),2)/pow(365.2421,2);
	G = 4*pow(2.0*asin(1.0),2);

	
	//Datos de Mercurio
	double mM = 1.65158371e-7;
	double e = 0.205630;
    double a =  0.387098;

	double x0T = a*(1.+e);
	double vy0T = sqrt(G*(1-e)/(a*(1+e)));
	
	
	Particle *p1 = new Particle(  0., 0., 0., 0., 1., 0.1, 0);
   	Particle *p2 = new Particle(  x0T, 0., 0., vy0T, mM, 0.01, 1);
   	
   	AllParticles[0] = p1;
   	AllParticles[1] = p2;
    
	int it = 0;
 	double t = 0.;

 	int itmax = int(tmax/deltat);
 	int itmaxten = itmax/10;


 	double rmin = a*(1.-e)+0.000001;
 	double Thetamin = 0.;
	double rmax = 0.;
 	double Thetamax = 0.;
 	double Periodo = 50.;
 		
	// Evolucion
	if(Animate) A->NewAnim();

	while (t <= tmax){

    double TEk = 0.;
    double TEp = 0.;
    double TPx = 0.;
    double TPy = 0.;

	if(Animate && it%fps == 0)
	{
    	A->StartLine();
	}
	// Iniciamos las aceleraciones de cada partícula del sistema.


	for(int i = 0; i< NParticles; i++)
	{
		AllParticles[i]->ResetForce();
		for(int j = 0;j < NParticles; j++)
		{	
			if (i!=j)
			{
			AllParticles[i]->GetForce(*AllParticles[j],Fuerza);
			}
		}
	
	AllParticles[i]->MoveVerlet(t,deltat,it);

	if (AllParticles[1]->GetR() > rmax)
	{
		rmax = AllParticles[1]->GetR();
		Thetamax = AllParticles[1]->GetTheta();
		Periodo = t;
		File[1]  << std::setprecision(12) << 2.0*Periodo << " " << rmax << " " << Thetamax << std::endl;
	}

	if (AllParticles[1]->GetR() < rmin)
	{
		rmin = AllParticles[1]->GetR();
		Thetamin = AllParticles[1]->GetTheta();
		Periodo = t;
		File[2]  << std::setprecision(12) << 2.0*Periodo << " " << rmin << " " << Thetamin << std::endl;
	}
	
	
	
	TEk += AllParticles[i]->GetEk();
	TEp += AllParticles[i]->GetEp();
	TPx += AllParticles[i]->GetPx();
	TPy += AllParticles[i]->GetPy();
	
	if(Animate && it%fps == 0){
    	AllParticles[i]->Print();	 
	}


	if(it%fps == 0)
		AllParticles[i]->WritetoFile();
	}

	TEp = 0.5*TEp; // Para evitar sumas repetidas

	if(it%fps == 0)
	File[0] << t << " " << TEk << " " << TEp << " " << TEk + TEp << " " << TPx << " " << TPy << std::endl;

  
  	
	if(Animate && it%fps == 0){
    	A->EndLine();
	}

	
	if(!Animate){
		if ( it%itmaxten == 0 )
			std::cout << 10*it/double(itmaxten) << "%-" << std::flush;
		if ( it == itmax)
			std::cout << std::endl; 
	}	

	t += deltat;
	it ++;
        
	}

	

	 // Closing the data files
    for(int i = 0; i < NParticles; i++){
    	AllParticles[i]->CloseFile();
    }

    File[0].close();
	File[1].close();
	File[2].close();


	return 0;
}	
