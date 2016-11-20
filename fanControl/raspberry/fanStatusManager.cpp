
/*
 * author: Koen Schoute, koen@gorgabal.nl (october 2016)
 * (description of responsibilities of class)
 */

#include "fanStatusManager.h"
#include <assert.h>
#include <stdexcept>
std::vector<fanstatus_t> fanList;


fanStatusManager::fanStatusManager(){
	//default constructor TODO
}

fanstatus_t fanStatusManager::setFanStatus(fanstatus_t status){
	for (std::size_t i = 0; i != fanList.size(); ++i) {
		if(status.id == fanList[i].id){
			fanList[i] = status;
			return fanList[i];
		}
	} 
	// if this for-loop has been completed, that means that the elemente has not been added to the list yet.
	fanList.push_back(status);
}

fanstatus_t fanStatusManager::getFanStatus(int id){
	for (std::size_t i = 0; i != fanList.size(); ++i) {
		if(id == fanList[i].id){
			return fanList[i];
		}
	} 
	throw std::invalid_argument( "fanStatusManager::getFanStatus Asked element is not in the list" );
}

std::vector<fanstatus_t> getFanStatus(){
	 return fanList;
}