all: lanParty

lanParty: *.c
	gcc $^ -Wall -g -o lanParty	
clean:
	rm -f lanParty
	rm -f *.out