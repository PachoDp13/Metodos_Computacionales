#Ejercicio 8: Laboratorio métodos computacionales
#Estudiante: Francisco Javier Díaz Perdomo
import numpy as np
def MatrizDiagonal(A_):
    B = A_.copy().astype(float)
    n = B.shape[0]
    for i in range(n - 1, -1, -1):

        for j in range(i - 1, -1, -1):

            B[j] = (B[j, i]/B[i, i]) * B[i] - B[j]

        B[i] = B[i] / B[i, i]
    return B
def MatrizTriangularSuperior(A_):
    B = A_.copy().astype(float)
    n = B.shape[0]
    for i in range(n):

        indi_max = np.argmax(np.abs(B[i:, i]))
        if indi_max > 0:
            C = B[i].copy()
            B[i] = B[i + indi_max]
            B[i + indi_max] = C

        for j in range(i + 1, n):
            B[j] = (B[j, i]/B[i, i]) * B[i] - B[j]
    return B

V0 = 5
A = np.array([[4, -1, -1, -1, V0],[1, -3, 0, 1, 0],[-1, 0, 3, -1, V0],[-1, -1, -1, 4, 0]])

At = MatrizTriangularSuperior(A)
D = MatrizDiagonal(At)
V1, V2, V3, V4 = D[:, -1][0], D[:, -1][1], D[:, -1][2], D[:, -1][3]
print(f"V_one = {V1}, V_two = {V2}, V_three = {V3}, V_four = {V4}")