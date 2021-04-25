set terminal png size 500,500
set output 'Px.png'
set title 'Momentum X'
set xlabel 't'
set ylabel 'Px'
plot "data/Totales.dat" using 1:5
