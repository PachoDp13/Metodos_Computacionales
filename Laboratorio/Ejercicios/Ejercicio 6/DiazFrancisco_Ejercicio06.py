#Laboratorio métodos computacionales: Ejercicio 6
#Estudiante: Francisco Javier Díaz Perdomo 201912252

#Importamos las librerias que utilizaremos.

import numpy             as np
import matplotlib.pyplot as plt
from matplotlib          import rc 
from tqdm import tqdm
import math

#Definiendo las funciones que utilizaremos.

def pi(x):
    return np.piecewise(x, [x>=0. and x<=1., x>1. and x<0.], [lambda x:1,lambda x:0.])
    
def Likelihood(x,alpha,beta):
    return (x**(alpha-1))*((1-x)**(beta-1))
    
def PosteriorF(x, alpha_, beta_):
    return Likelihood(x,alpha_,beta_)*pi(x)
    
def Metropolis(H0_,WidthSteps,NSteps = int(1e5), alpha_ = 0.5, beta_ = 0.5):
    
    MCMC = np.array([])
    
    for i in tqdm(range(int(NSteps))):
        
        # Present
        P0 = PosteriorF(H0_,alpha_ , beta_ )
        
        Hn_ = H0_ + WidthSteps*np.random.uniform(-1.,1.)
        
        # Futuro
        
        Pn = PosteriorF(Hn_, alpha_ , beta_ )
        
        alpha = Pn/P0
        
        r = np.random.rand()
        
        if np.minimum(1,alpha) > r:
            
            H0_ = Hn_
            MCMC = np.append(MCMC,Hn_) 
            
        else:
            
            MCMC = np.append(MCMC,H0_)  
        
    return MCMC

#Calculando los datos para valores de alpha y beta. Adicionalmente graficamos.

alpha_, beta_= 0.5, 0.5
Npoints = int(1e5)
MCMC = Metropolis(0.9,0.08,Npoints, alpha_ , beta_ )

x=np.linspace(0,1,Npoints)
y = (math.gamma(alpha_+beta_)/(math.gamma(alpha_)*math.gamma(beta_)))*Likelihood(x,alpha_,beta_)

fig = plt.figure(figsize=(12,12/1.6))
ax = fig.add_subplot(1, 1, 1)
ax.set_facecolor('k')
ax.plot(x,y,linewidth=3,color='r', alpha = 1)
ax.hist(MCMC, bins=150,density=True,color=(0.3,0.8,0.7,0.4), alpha = 1)
plt.ylim(0,11)
plt.xlim(0,1)
plt.savefig('DiazFrancisco_grafica.png')
plt.show()