#!/usr/bin/env python
# coding: utf-8
# Estudiante: Francisco Javier Díaz Perdomo 201912252

import numpy as np
import math

def VolumenNBola_MonteCarlo(R_, m_, n):
    
    m = int(m_)
    R = ( np.random.rand(m)*(R_))
    function = (R**(n-1))
    
    for i in range(1,n-1):
        wi =  np.random.rand(m)*(np.pi)
        function *= (np.sin(wi))**(n-(i+1))
        
    integral = sum(function)
    integral *= 2*(np.pi**(n-1))*R_
    integral *= (1/m)
    
    return integral

def VolumenNBola_Real(R,n):
    
    volumen = (((np.pi)**(n/2))*(R**n))/(math.gamma((n/2)+1))
    
    return volumen
    
    
    
m = 1e6
n = 10
R = 1

volumen_sphere_10d = VolumenNBola_MonteCarlo(R,m,n)
volumen_sphere_10d_real = VolumenNBola_Real(R,n)

print(f"Volumen esfera en 10D = {volumen_sphere_10d}")

