CC=g++
CFLAGS= -g -lwiringPi -lwiringPiDev -std=c++0x -Wall -Wextra -pedantic-errors -Werror
REMOTEHOST=pi@10.209.10.221
CLEAN=rm -f fanStatusManagerTest controlPanelTest CommunicatorTest main

main: main.cpp Communicator.cpp controlPanel.cpp 
	$(CC) main.cpp Communicator.cpp controlPanel.cpp $(CFLAGS) -o main

clean:
	rm -f $(CLEAN) && ssh $(REMOTEHOST) 'cd /home/pi/FanChicken/fanControl/raspberry/ && $(CLEAN)' 

upload:
	rsync -av ../../../FanChicken $(REMOTEHOST):/home/pi --exclude=".git*" --exclude="main" --delete && ssh $(REMOTEHOST) 'cd /home/pi/FanChicken/fanControl/raspberry/ && make && sudo /home/pi/FanChicken/fanControl/raspberry/main'

#syntax
#
#
#target: dependencies
#	action	
