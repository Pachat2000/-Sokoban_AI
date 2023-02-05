CC=g++
CFLAGS=-std=c++11 -Wall -O2

##### SOKOBAN
r0: mysok.h r0.cpp
	$(CC) $(CFLAGS) r0.cpp -o $@
	
r0_exe: 
	./r0 ../Data/Screens-$(S)/screen-$(N).txt
	
clean:
	rm r0
