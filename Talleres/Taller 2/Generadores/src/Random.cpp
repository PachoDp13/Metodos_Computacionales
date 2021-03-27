#include "../inc/Random.h"
using namespace std;

Random::Random(){
   r = 0;
   method = "simple";
}


Random::Random(long int seed_, string method_){
	r = seed_;
    method = method_;
}


void Random::SetSeed(long int seed_){r = seed_;}

void Random::SetMethod(string method_){
    
    if ( method_.compare("simple") == 0)
    {
        a = 57;
        c = 1;
        m=265; 
    }
    
    else if ( method_.compare("drand48") == 0)
    {
        a = 0x5DEECE66D;
        c = 0xB;
        m=pow(2,48);  
    }
    
    else {
        std::cout << "Generador no reconocido" << std::endl;
    }
}

double Random::rand(double A_, double B_){

	return A_ + (B_-A_)*Random::rand();
}

double Random::rand(){

	r = (a*r + c)%m;

	return double(r)/double(m);	

}

Random::~Random(){

}