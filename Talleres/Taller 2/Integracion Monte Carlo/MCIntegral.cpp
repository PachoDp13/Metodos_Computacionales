#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include <math.h>

double average(double *x, int n_points);
double average_sq(double *x, int n_points);
double Funcion(double r, double theta);

int main(int argc, char *argv[])
{
    //Parámetros de entrada:
    int NPoints = std::stof(argv[1]);
    double r;
    double theta;
    double limits = 2*pow(M_PI,2);

    double *f = new double[NPoints]; 
    for(int i=0; i<NPoints; i++)
    {
        r = drand48();
        theta = drand48()*M_PI;
        f[i] = Funcion(r, theta);
    }

    double integral = average(f, NPoints)*limits;

    fprintf(stdout, "El valor estimado de la integral es: %f\n", integral);
    return 0;
}

double average(double *x, int N_)
{
    double sum = 0.0;
    for(int i=0;i<N_; i++)
    {
        sum += x[i];
    }
    sum = sum/N_;
    return sum;
}

double average_sq(double *x, int N_)
{
    double sum = 0.0;
    for(int i=0;i<N_;i++)
    {
        sum += x[i]*x[i];
    }
    sum =sum/N_;
    return sum;
}

double Funcion(double r, double theta)
{
    return pow(r,2)*exp(r)*sin(theta);
}