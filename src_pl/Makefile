CC=g++
CFLAGS=-std=c++11 -Wall -O2

##### SOKOBAN
r0: main.cpp
	$(CC) $(CFLAGS) main.cpp -o $@
	
r0_exe: 
	./r0 ../Data/Screens-$(S)/screen-$(N).txt
	
clean:
	rm r0