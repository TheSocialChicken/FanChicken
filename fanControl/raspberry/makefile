CC=g++
CFLAGS= -g -lwiringPi -lwiringPiDev -std=c++0x -Wall -Wextra -pedantic-errors -Werror
REMOTEHOST=pi@10.209.10.221

#TODO: improve makefile to only compile what is neccesary
all: main.cpp Communicator.cpp controlPanel.cpp 
	$(CC) main.cpp Communicator.cpp controlPanel.cpp $(CFLAGS) -o main

clean:
	rm -f fanStatusManagerTest controlPanelTest CommunicatorTest main

upload:
	rm -f main && rsync -av ../../../FanChicken $(REMOTEHOST):/home/pi --exclude=".git*" --delete && ssh $(REMOTEHOST) 'cd /home/pi/FanChicken/fanControl/raspberry/ && make'

#syntax
#
#
#target: dependencies
#	action	
