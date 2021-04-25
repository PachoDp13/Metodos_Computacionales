set terminal png size 500,500
set output 'Energia_Cinetica.png'
set title 'Energía Cinética'
set xlabel 't'
set ylabel 'Ek'
plot "data/Totales.dat" using 1:2
