all: hw14.c
	gcc hw14.c
run: all
	./a.out -c 4
	./a.out -v
	./a.out -c 3
	./a.out -v
	./a.out -r
