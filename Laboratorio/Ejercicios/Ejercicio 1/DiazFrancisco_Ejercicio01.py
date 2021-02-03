#!/usr/bin/env python
# coding: utf-8

# In[1]:


def angulo_sol(hora_):
    horas = hora_[0]+hora_[1]
    minutos = hora_[3]+hora_[4]

    horas= int(horas)
    minutos = int(minutos)
    
    if horas >= 6 and horas <= 18:
        total = (horas-6)*60 + minutos
        angulo = total/4
        return(angulo)
    else:
        return ("No hay sol.")

print(angulo_sol("12:30"))
print(angulo_sol("07:00"))
print(angulo_sol("05:55"))
        

