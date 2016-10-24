/*
 * author: Koen Schoute, koen@gorgabal.nl (october 2016)
 * Provides internal communication template. 
 */
#ifndef fanstatus_t
#define fanstatus_t

	/*
	 * The fanstatus struct is meant for holding information about the individual fansystems. 
	 * The communicator refers to this struct when doing anything fanstatus related. (update)
	 *
	 */
	struct fanstatus_t {
		 int id
		 std::string devicepath
		 bool:acitve
		 boor:error
		 float:temperature
		 float:humidity
	};

#endif /* end include geard*/
