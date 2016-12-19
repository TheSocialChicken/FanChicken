CC=g++
CFLAGS= -g -lwiringPi -lwiringPiDev -std=c++0x -Wall -Wextra -pedantic-errors -Werror



all: main.cpp Communicator.cpp controlPanel.cpp 
	$(CC) main.cpp Communicator.cpp controlPanel.cpp $(CFLAGS) -o main

clean:
	rm -f fanStatusManagerTest controlPanelTest CommunicatorTest main

upload:
	rm main && rsync -av ../../../FanChicken pi@10.209.10.221:/home/pi --exclude=".git*" --delete

#syntax
#
#
#target: dependencies
#	action	
