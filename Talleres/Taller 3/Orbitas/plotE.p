set terminal png size 500,500
set output 'Energia_Total.png'
set title 'Energía Total'
set xlabel 't'
set ylabel 'E Total'
plot "data/Totales.dat" using 1:4
