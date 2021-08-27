#include <iostream>
class Triangle
{
private:
float a;
float b;
float c;
public:

float get_a()
{
return a;
}
float get_b()
{
return b;
}
float get_c()
{
return c;
}
void set_a(float a_param)
{
a = a_param;
}
void set_b(float b_param)
{
b = b_param;
}
void set_c(float c_param)
{
c = c_param;
}
    
float perimeter()
{
return a+b+c;
}
};
int main() 
{
    Triangle triangulo;
    float a;
    float b;
    float c;
 
    std::cin >> a >> b >> c;
    triangulo.set_a(a);
    triangulo.set_b(b);
    triangulo.set_c(c); 
    
    std::cout << "Los lados del triangulo son: \n" << triangulo.get_a() <<" " << triangulo.get_b() << " " << triangulo.get_c() << "\n" <<"El perimetro del triangulo es " << triangulo.perimeter()<< "\n";;
    
    return 0;
    
     
}