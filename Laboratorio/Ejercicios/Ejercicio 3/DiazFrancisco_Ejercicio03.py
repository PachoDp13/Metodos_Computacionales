import numpy as np
import matplotlib.pyplot as plt
#Definimos una función auxiliar para determinar si dos valores están lo suficientemente cercanos.
#Note que el valor de epsilon debe depender del parámetro de error (delta). Acá lo tomamos como 10*epsilon
def vecindad(a, b, epsilon):
    return abs(a-b) <= epsilon*10

#Definimos la función de bisección
def bisection(f,a,b,error):
    prec = b-a
    while (f(a)*f(b) != 0) and prec > error:
        c=(a+b)/2
        if f(a)*f(c) < 0:
            b=c
        else:
            a=c
        prec=b-a
#Seleccionamos la raíz encontrada estimada
    if vecindad(f(b),0,error):
        return b
    elif vecindad(f(a),0,error):
        return a
    
#Definimos nuestra precisión, la función de interés y el intervalo en dónde queremos encontrar las raíces.

err=1e-8
Function =  lambda x: (x+2)*(x-2)*(x-4)
roots = []
I =np.linspace(-10,10,50) 

#Realizamos el barrido para encontrar todas las raíces en el intervalo I
i= 0
while i  <  len (I)-1:
    a =I[i]
    b = I[i+1]
    root = bisection(Function,a,b,err)
    if root != None and ((root in roots) == False):
        roots.append(root)
    i+=1

print("La raíces encontradas fueron:  " +str(roots))