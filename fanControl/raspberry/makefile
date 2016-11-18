CC=g++
CFLAGS=

all: main.cpp Communicator.cpp controlPanel.cpp fanStatusManager.cpp 
	$(CC) main.cpp Communicator.cpp controlPanel.cpp fanStatusManager.cpp -o main


# quick and dirty commands for easier testing. 
#DEPRICATED
fanstatusmanager: fanStatusManager.cpp
	$(CC) fanStatusManager.cpp fanStatusManager.h $(CFLAGS) -o fanStatusManagerTest

#DEPRICATED
controlpanel: controlPanel.cpp
	$(CC) controlPanel.cpp -lwiringPi -L/usr/local/include -o controlPanelTest

#DEPRICATED
communicator: Communicator.cpp
	$(CC) Communicator.cpp -o CommunicatorTest

clean:
	rm -f fanStatusManagerTest controlPanelTest CommunicatorTest main

#syntax
#
#
#target: dependencies
#	action	
