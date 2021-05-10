set terminal png size 500,500
set output 'data/Energia_Potencial.png'
set title 'Energía Potencial'
set xlabel 't'
set ylabel 'Ep'
plot "data/Totales.dat" using 1:3
