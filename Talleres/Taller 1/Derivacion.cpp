#include<iostream>
#include<vector>
#include<math.h> 
#include<fstream>

double f(double x_)
{
    double f_ = x_ - sin(x_);
    return f_;
}

double derivadaCentral(double x_ , double h_)
{
    double df_ = (f(x_+h_)-f(x_-h_))/(2*h_);
    return df_;
}
double derivadaExacta(double x_ )
{
    double dfe_ = 1- cos(x_);
    return dfe_;
}
int main(){
    
    // output file
    std::ofstream out;
    out.open("derivada.dat", std::ofstream::trunc);
    
    double  x0 = 0.;
    double h = 0.05;
    double DC0 = derivadaCentral(x0,h);
    
    
    
    double xi = -1.;
    double xf = 1.;
    int Npoints = ((xf-xi)/h) +1;
    
    // Dynamic arrays like-pointers
    
    double *x = new double[Npoints]; 
    double *fx = new double[Npoints];
    double *dfc = new double[Npoints];
    double *dfe = new double[Npoints];
    double *localError = new double[Npoints];
    
    // Filling the array and functions
    for(int i=0; i<Npoints;++i){
        x[i] = xi + double(i)*h;
        fx[i] = f(x[i]);
        dfc[i]= derivadaCentral(x[i] , h);        
        dfe[i]= derivadaExacta(x[i] );
        localError[i] = abs(derivadaExacta(x[i] )-derivadaCentral(x[i] , h)) ;
    }
    
    
    double Sum_num = 0. ;
    double Sum_den = 0. ;

    for(int i=0; i<Npoints;++i)
    {
        Sum_num = Sum_num + localError[i]*localError[i];
        Sum_den = Sum_den +dfe[i]*dfe[i];
       
    }
    
    
    double ErrorGlobal = sqrt(Sum_num/Sum_den);
    
    
    out << Npoints << " " << DC0 << " " << ErrorGlobal  <<std::endl;
    
    // Printing and saving the information
    
    for(int i=0; i<Npoints;i++){
        out << x[i] << " " << fx[i] << " " << dfc[i] <<" " << dfe[i] <<" " << localError[i] <<std::endl;
    }
    
   
    
    // Free up memory  
    
    delete[] x;
    delete[] fx;
    delete[] dfc;    
    delete[] dfe;      
    delete[] localError;
    
    // Close the output file
    
    out.close();
    
    return 0;
}