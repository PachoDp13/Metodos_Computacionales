#Laboratorio métodos computacionales: Ejercicio 4
#Estudiante: Francisco Javier Díaz Perdomo

#Primero importaremos los paquetes que usaremos.

import numpy as np
import random as rd

#Definimos la función generadora de nuestro espacio muestral y las dos funciones de conteo para Alice y Bob.

def nDados(n,m):
    lista = []
    for j in range(m):
        x = [np.random.randint(1, 7) for i in range(0, n)]
        lista.append(x)
    return lista
def Alice(lista):
    N=0
    for i in lista:
        state = True
        for j in range(len(i)-1):
            
            if i[j] != i[j+1]:
                state = False 
        if state == True:
            N+=1
            #print("Alice: " +str(i))
    return N
def Bob(lista):
    N=0
    for i in lista:
        state = True
        sorted = np.sort(i)
        for j in range(len(i)-1):
            if sorted[j+1] != sorted[j]+1:
                state = False 
        if state == True:
            #print("Bob: " +str(i))
            N+=1
    return N

#Finalmente, calculamos e imprimimos nuestros resultados.
NTiros, NSeries=3, 10000     
EspMuestral = nDados(NTiros, NSeries)

NAlice = Alice (EspMuestral)
NBob = Bob(EspMuestral)

prob_same = NAlice / len(EspMuestral)
prob_consecutive = NBob / len(EspMuestral)

print(f"Prob Alice = {prob_same}, Prob Bob = {prob_consecutive}")