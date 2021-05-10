make clean
make
rm data/*
#Simulación para la preseción de Mercurio
./Colisiones 2 5 0.00000001 2 0.50 10000 0 

#Simulación para la animación sisttema Sol-Mercurio o sistema planetario aleatorio
#./Colisiones 2 1 0.000001 2 2 1000 1 | gnuplot
#sh animOutput/CreatePlot.sh

