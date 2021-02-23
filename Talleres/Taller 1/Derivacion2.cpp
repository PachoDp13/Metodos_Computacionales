#include<iostream>
#include<vector>
#include<math.h> 
#include<fstream>

double f(double x_)
{
    double f_ = x_ - sin(x_);
    return f_;
}
double segundaDerivada1(double x_ , double h_)
{
    double df2_ = (f(x_+h_)-2*f(x_)+f(x_-h_))/(h_*h_);
    return df2_;
}
double segundaDerivada2(double x_  , double h_)
{
    double df2_ = (f(x_+2*h_)-2*f(x_)+f(x_-2*h_))/(4*h_*h_);
    return df2_;
}
double segundaDerivadaExacta(double x_ )
{
    double dfe_ = sin(x_);
    return dfe_;
}
int main(){
    
    // output file
    std::ofstream out;
    out.open("derivada2.dat", std::ofstream::trunc);
    
    double h = 0.05;
    double xi = -1.;
    double xf = 1.;
    int Npoints = ((xf-xi)/h) +1;
    
    // Dynamic arrays like-pointers
    
    double *x = new double[Npoints]; 
    double *df21 = new double[Npoints];
    double *df22 = new double[Npoints];
    double *df2e = new double[Npoints];
    double *localError1 = new double[Npoints];
    double *localError2 = new double[Npoints];
    
    // Filling the array and functions
    for(int i=0; i<Npoints;++i){
        x[i] = xi + double(i)*h;
        df21[i] = segundaDerivada1(x[i], h);
        df22[i]= segundaDerivada2(x[i] , h);        
        df2e[i]= segundaDerivadaExacta(x[i]);
        localError1[i] = abs(segundaDerivadaExacta(x[i] )-segundaDerivada1(x[i] , h)) ;
        localError2[i] = abs(segundaDerivadaExacta(x[i] )-segundaDerivada2(x[i] , h)) ;
    }
    
    
    double Sum_num1 = 0. ;
    double Sum_den1 = 0. ;
    double Sum_num2 = 0. ;
    double Sum_den2 = 0. ;

    for(int i=0; i<Npoints;++i)
    {
        Sum_num1 = Sum_num1 + localError1[i]*localError1[i];
        Sum_den1 = Sum_den1 +df2e[i]*df2e[i];
        
        Sum_num2 = Sum_num2 + localError2[i]*localError2[i];
        Sum_den2 = Sum_den2 +df2e[i]*df2e[i];
       
    }
    
    
    double ErrorGlobal1 = sqrt(Sum_num1/Sum_den1);
    double ErrorGlobal2 = sqrt(Sum_num2/Sum_den2);
    
    
    out << Npoints << " " <<  ErrorGlobal1 << " " << ErrorGlobal2 <<std::endl;
    
    // Printing and saving the information
    
    for(int i=0; i<Npoints;i++){
        out << x[i] << " " << df21[i] << " " << df22[i] <<" " << df2e[i] <<" " << localError1[i] <<" " << localError2[i]<<std::endl;
    }
    
   
    
    // Free up memory  
    
    delete[] x;
    delete[] df21;
    delete[] df22;    
    delete[] df2e;      
    delete[] localError1;
    delete[] localError2;
    
    // Close the output file
    
    out.close();
    
    return 0;
}
