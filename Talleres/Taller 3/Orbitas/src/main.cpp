#include <../inc/Particle.h>
#include <../inc/Anim.h>
#define pi 2.0*asin(1.0)


std::ofstream *File;

double Random(double a, double b)
{	
    return a+(b-a)*drand48();
}

int main(int argc, char *argv[])
{
	// Seed
	srand48(time(0));

	// Parametros de la simulacion
	int NParticles = std::stoi(argv[1]);
	double tmax = std::stof(argv[2]);
	double deltat = std::stof(argv[3]);
	int Fuerza = std::stoi(argv[4]);
	double limits = std::stof(argv[5]);
	int fps = std::stoi(argv[6]);
	bool Animate = std::stoi(argv[7]);

	// Nuestro sistema de planetario
	Particle *AllParticles[NParticles];

	// G en unidades Gaussianas
	double G = 6.674e-11;
	G /= pow(1.496e+11, 3); // Distancia Tierra Sol en 
	G *= 1.989e+30; // 1 Masa Solar en Kg
	G /= pow(1.157e-5,2); // 1 segudos en dias
	// Usando Tercera Ley de Kepler
	//G = 4*pow(2.0*asin(1.0),2)/pow(365.2421,2);
	G = 4*pow(2.0*asin(1.0),2);

	// Datos de Mercurio
	double mM = 1.65158371e-7;
	double e = 0.205630;
    double a =  0.387098;

	// Variables para la iteración de la evolución del sistema
	int it = 0;
 	double t = 0.;

	// Simulación para la generación de la simulación del sistema planetario
	if(Animate)
	{	
		// Inicializamos el sistema sol-Mercurio
		if (NParticles ==2)
		{
			double x0T = a*(1.+e);
			double vy0T = sqrt(G*(1-e)/(a*(1+e)));
			Particle *p1 = new Particle(0., 0., 0., 0., 1., 0.1, 0);
   			Particle *p2 = new Particle(x0T, 0., 0., vy0T, mM, 0.01, 1);
   			AllParticles[0] = p1;
   			AllParticles[1] = p2;
		}
		// Inicializamos nuestro sistema planetario aleatorio
		else
		{
			Particle *p1 = new Particle(0., 0., 0., 0., 1., 0.1, 0);
			AllParticles[0] = p1;
			for(int i = 1; i <NParticles; i++)
			{	
				double m = Random(1,100);
				m = m*pow(10,-7);
				double e = Random(0,0.8);
    			double a =  Random(0.3,1);
				double r = Random(0.001,0.04);
				double x0T = a*(1.+e);
				double vy0T = sqrt(G*(1-e)/(a*(1+e)));

				Particle *p = new Particle(x0T, 0., 0., vy0T, m, r, i);
				AllParticles[i] = p;
			}
		}
		
		// Archivo con los datos de energía y momento del sistema
		std::string Folder = "data/";
		std::string File1 = Folder + "Totales.dat";
		File = new std::ofstream[2];
		File[0].open(File1.c_str(), std::ofstream::trunc);

		// Inicializamos el objeto para generar la animación de la simulación
		Anim *A = new Anim(limits);
	 	A->NewAnim();

		// Evolución del sistema
		while (t <= tmax)
		{
    		double TEk = 0.;
    		double TEp = 0.;
    		double TPx = 0.;
    		double TPy = 0.;

			if(it%fps == 0)
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

				//Nos movemos con las aceleraciones ya calculadas
				AllParticles[i]->MoveVerlet(t,deltat,it);
	
				TEk += AllParticles[i]->GetEk();
				TEp += AllParticles[i]->GetEp();
				TPx += AllParticles[i]->GetPx();
				TPy += AllParticles[i]->GetPy();
	
				if(it%fps == 0)
				{
    				AllParticles[i]->Print();
					AllParticles[i]->WritetoFile();
				}		
			}

			TEp = 0.5*TEp; 

			if(it%fps == 0)
			{
				File[0] << t << " " << TEk << " " << TEp << " " << TEk + TEp << " " << TPx << " " << TPy << std::endl;	
			}

			if(it%fps == 0)
			{
    			A->EndLine();
			}

			t += deltat;
			it ++; 
		}
	 // Cerramos los archivos Output
    	for(int i = 0; i < NParticles; i++)
		{
    		AllParticles[i]->CloseFile();
    	}
    	File[0].close();
	}

	// Simulación para la generación de los datos de la preseción de mercurio
	else
	{	
		// Archivo con los datos correspondientes al perihelio de la órbita de Mercurio
		std::string Folder = "data/";
		std::string File1 = Folder + "Perihelio.dat";
		File = new std::ofstream[2];
		File[0].open(File1.c_str(), std::ofstream::trunc);

		// Datos de iteraciones del presente, el futuro y el "futuro" del futuro
		// Descripción del presente
		double r = 0.0; 
    	double x = 0.0;
		double y = 0.0;  
    	double ax = 0.0; 
    	double ay = 0.0; 
    	double vx = 0.0; 
    	double vy = 0.0; 
		// Descripción del futuro
		double rf = 0.0; 
		double xf = 0.0; 
		double yf = 0.0; 
		double afx = 0.0; 
		double afy = 0.0;
		double vfx = 0.0; 
		double vfy = 0.0; 		
		// Descripción del futuro del futuro
		double rf2 = 0.0;
		double xf2 = 0.0;
		double yf2 = 0.0;

		// Variables correspondientes al perihelio de Mercurio
 		double rmin = a*(1.-e);
 		double thetamin = 0.;
 		double Periodo = 0.24109;
		double alpha = 1.1e-8;

		// Estado inicial del sistema (estado inicial de mercurio pues se considera el sol totalmente estático)
  		x = a*(1.+e);
		vy = sqrt(G*(1-e)/(a*(1+e)));

		// Variables para conocer el estado de la simulación
		long int itmax = int(tmax/deltat);
 		int itmaxten = itmax/10;

		//Evolución del sistema
		while (t <= tmax)
		{
			// Realizamos la integración de Verlet para los tres momentos (Presente, futuro y "futuro" del futuro)
			//Mi presente
	  		r = sqrt(x*x + y*y); 
      		ax = -(G/pow(r,2))*(1.0+(alpha/pow(r,2)))*(x/r);  
     		ay = -(G/pow(r,2))*(1.0+(alpha/pow(r,2)))*(y/r);  
    
      		//Mi futuro
      		xf = x + (vx*deltat) + ax*(pow(deltat,2)/2); 
      		yf = y + (vy*deltat) + ay*(pow(deltat,2)/2); 
      		rf = sqrt(pow(xf,2)+ pow(yf,2));  
      		afx = -(G/pow(rf,2))*(1.0+(alpha/pow(rf,2)))*(xf/rf);  
     		afy = -(G/pow(rf,2))*(1.0+(alpha/pow(rf,2)))*(yf/rf);  
      		vfx = vx + (ax+afx)*(deltat/2); 
      		vfy = vy + (ay+afy)*(deltat/2); 

      		//El futuro de mi futuro
      		xf2 = xf + (vfx*deltat) + afx*(pow(deltat,2)/2);  
      		yf2 = yf + (vfy*deltat) + afy*(pow(deltat,2)/2);  
      		rf2 = sqrt(pow(xf2,2)+ pow(yf2,2));  

      		//Me actualizo finalmente
      		x = xf;
      		y = yf;
      		vx = vfx;
      		vy = vfy;
    
			// Imprimimos los datos que analizaremos para la preseción de la órbita filtrandolos según la condición de un mínimo local (en este caso es un mínimo absoluto correspondiente al perihelio)
			if( r > rf &&  rf < rf2 )
			{	
				if ( (xf > 0.) && (yf > 0.) )
				{
					thetamin  = atan(yf/xf);
				}
				else if( (xf < 0.) && (yf > 0.) )
				{
					thetamin  = atan(yf/xf) + 2.0*asin(1.0);
				}
				else if( (xf < 0.) && (yf < 0.) )
				{
					thetamin  = atan(yf/xf) + 2.0*asin(1.0);
				}
				else
				{
					thetamin = atan( yf/xf ) + 4.0*asin(1.0);
				}
				rmin = rf;
				thetamin = thetamin*180./(2.0*asin(1.0));
				Periodo = t;

				File[0]  << std::setprecision(12) << Periodo << " " << rmin  << " " << thetamin << std::endl;
			}

			if ( it%itmaxten == 0 )
			{
				std::cout << 10*int(it/itmaxten) << "%-" << std::flush;
			}
			t += deltat;
			it ++; 
		}

		// Cerramos el archivo de salida
    	File[0].close();
	}
	
	return 0;
}	
