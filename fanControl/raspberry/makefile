CC=g++
CFLAGS= -g -lwiringPi -lwiringPiDev -std=c++0x -Wall -Wextra -pedantic-errors -Werror



all: main.cpp Communicator.cpp controlPanel.cpp fanStatusManager.cpp 
	$(CC) main.cpp Communicator.cpp controlPanel.cpp fanStatusManager.cpp $(CFLAGS) -o main

clean:
	rm -f fanStatusManagerTest controlPanelTest CommunicatorTest main

#syntax
#
#
#target: dependencies
#	action	
