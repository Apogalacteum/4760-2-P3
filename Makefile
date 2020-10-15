master: main.o
	cc -o master main.o
	
palin: palindrome.o
	cc -o palin palindrome.o
	
trial: trial.o
	cc -o trial trial.o

main.o: main.c
	cc -c main.c

palindrome.o: palindrome.c
	cc -c palindrome.c
	
trial.o: trial.c
	cc -c trial.c
  
clean :
	rm master palin trial main.o palindrome.o trial.o