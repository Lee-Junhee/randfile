all: main.o
	gcc -o randgen main.o

main.o: main.c
	gcc -c main.c

run:
	./randgen

clean:
	touch a.o
	touch a.swp
	rm *.o
	rm *.swp
