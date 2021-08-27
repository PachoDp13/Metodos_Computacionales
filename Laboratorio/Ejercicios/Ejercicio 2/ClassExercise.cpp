#include <iostream>



void swap(int* pa, int* pb)
{
    
    int b_temp = *pb; 
    *pb = *pa; // b=a
    *pa = b_temp; //a=b
    
}

int main()
{
    int a;
    int b;
    
    std::cin >> a;
    std::cin >> b;
    std::cout <<"a = " <<a << " b = " << b <<"\n";
    int* pa = &a;
    int* pb= &b;
    swap(pa, pb);
    
    std::cout <<"a = " <<a << " b = " << b<<"\n";
    //printf("%p \n" , pa);
    //std::cout << a << "" << b;
    return 0;
}