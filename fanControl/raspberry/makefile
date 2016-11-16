CC=g++
CFLAGS=

all: main.cpp Communicator.cpp controlPanel.cpp fanStatusManager.cpp 
	$(CC) main.cpp -o main

fanstatusmanager: fanStatusManager.cpp
	$(CC) fanStatusManager.cpp fanStatusManager.h $(CFLAGS) -o fanStatusManagerTest

controlpanel: controlPanel.cpp
	$(CC) controlPanel.cpp -lwiringPi -L/usr/local/include -o controlPanelTest

communicator: Communicator.cpp
	$(CC) Communicator.cpp -o CommunicatorTest

clean:
	rm fanStatusManagerTest controlPanelTest CommunicatorTest main

#syntax
#
#
#target: dependencies
#	action	
