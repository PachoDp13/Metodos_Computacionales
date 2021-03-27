#include "../inc/Random.h"
using namespace std;


int main(){

        Random *r1 = new Random(); 
        Random *r2 = new Random(); 
	
        r1->SetSeed(6625);
        r2->SetSeed(6625);
    
        r1->SetMethod("simple");
        r2->SetMethod("drand48");

	for(int i = 0; i < 1000; i++)
		//std::cout << r->rand(-10.,10.) << std::endl;
		std::cout << r1->rand()  << " " << r2->rand() << std::endl;


	delete r1;
    delete r2;
	return 0;

}

