#include "../inc/Random.h"
#include<iostream>
#include<vector>
#include<math.h> 
#include<fstream>

using namespace std;


int main(){
        //Creamos los objetos que utilizaremos. Cada uno con su respectiva raíz y método.
        Random *r1 = new Random(); 
        Random *r2 = new Random(); 
        r1->SetSeed(6625);
        r2->SetSeed(6625);
        r1->SetMethod("simple");
        r2->SetMethod("drand48");

        //Declaramos el archivo de salida.
        std::ofstream out;
        out.open("data_Ck.dat", std::ofstream::trunc);
        
        //Ahora generamos los números aleatorios y los almacenamos en dos listas.
        int Npoints = 1000;
        double *Random1 = new double[Npoints]; 
        double *Random2 = new double[Npoints];

        for(int i=0; i<Npoints;++i)
        {
        Random1[i] = r1->rand();
        Random2[i] = r2->rand();

        }
        
        //Ahora calculamos los coeficientes C(k) estimados para cada uno de los métodos.

        int k = 20;

        double *Ck1 = new double[k]; 
        double *Ck2 = new double[k];

        for(int i=0; i < k; i++)
        {
            double sum1 = 0;
            double sum2 = 0;
            for(int j=0; j < Npoints-i-1; j++)
            {
                sum1 = sum1 + Random1[j]*Random1[j+i+1];
                sum2 = sum2 + Random2[j]*Random2[j+i+1];

                
            }
            sum1 = sum1/Npoints;
            sum2 = sum2/Npoints;
            Ck1[i] = sum1;
            Ck2[i] = sum2;
        }

        // Imprimiendo los coeficientes en la consola y guardándolos en el archivo .dat
        std::cout << " --- Coeficientes C(k) --- "  << std::endl;

        for(int i=0; i<k;i++)
        {
            std::cout  << Ck1[i] << " " << Ck2[i] << std::endl;
            out << Ck1[i] << " " << Ck2[i] << std::endl;
        }


	delete r1;
    delete r2;
    delete[] Random1;
    delete[] Random2;
    delete[] Ck1;
    delete[] Ck2;

    out.close();

	return 0;

}

