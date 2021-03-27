#ifndef Random_h
#define Random_h

#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Random{

	public:
		Random();
		Random(long int seed_ , string method_);
        	~Random();

		void SetSeed(long int seed_);
		void SetMethod(string method_);
		double rand();
		double rand(double A_, double B_);

	private:

	unsigned long int a ;
	unsigned long int c;
  	unsigned long int m;


	unsigned long int r;
    string method;



};



#endif
