#include<iostream>
#include<fstream>
#include <math.h>

double Average(double *x, int n_points);
double Funcion(double r, double theta);

int main(int argc, char *argv[])
{
    //Parámetros de entrada:
    int NPoints = std::stof(argv[1]);
    double r;
    double theta;
    double limits = 2*pow(M_PI,2);
    srand48(time(0));

    double *f = new double[NPoints]; 
    for(int i=0; i<NPoints; i++)
    {
        r = drand48();
        theta = drand48()*M_PI;
        f[i] = Funcion(r, theta);
    }

    double integral = Average(f, NPoints)*limits;

    fprintf(stdout, "El valor estimado de la integral utilizando %d puntos muestrales es: %f\n", NPoints, integral);
    return 0;
}

double Average(double *x, int N_)
{
    double sum = 0.0;
    for(int i=0;i<N_; i++)
    {
        sum += x[i];
    }
    sum = sum/N_;
    return sum;
}
double Funcion(double r, double theta)
{
    return pow(r,2)*exp(r)*sin(theta);
}