punch: punch.o
	g++ punch.o -o punch -lsfml-graphics -lsfml-window -lsfml-system

punch.o: punch.c++
	g++ -c punch.c++
