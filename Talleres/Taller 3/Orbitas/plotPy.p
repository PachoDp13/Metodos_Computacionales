set terminal png size 500,500
set output 'Py.png'
set title 'Momentum Y'
set xlabel 't'
set ylabel 'Py'
plot "data/Totales.dat" using 1:6
