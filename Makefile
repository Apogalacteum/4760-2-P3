oss: main.o
	cc -o master main.o
	
chproc: chproc.o
	cc -o chproc chproc.o

main.o: main.c
	cc -c main.c
	
chproc.o: chproc.c
	cc -c chproc.c
  
clean :
	rm oss chproc main.o chproc.o