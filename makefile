diningOut: diningOut.o
	gcc -Wall -pthread util.o diningOut.o -o diningOut

diningOut.o: diningOut.c util.c
	gcc -Wall -pthread -c util.c diningOut.c
