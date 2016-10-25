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
		 int id = -1
		 std::string devicepath = "/dev/null"
		 bool:active = false
		 bool:error = false
		 float:temperature = 0.0
		 float:humidity = 0.0
	};

#endif /* end include geard*/
