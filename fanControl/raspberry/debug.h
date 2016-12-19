/* 
 * File:   debug.h
 * Author: Koen Schoute, koen@gorgabal.nl
 *
 * Created on December 19, 2016, 11:21 AM
 * 
 * Quick and dirty implementation for an debug logger
 */

#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>

//debug on
#define DEBUG_MSG(msg) std::cout << msg << '\n'; std::flush(std::cout)

//debug off
//#define DEBUG_MSG(msg)


#endif /* DEBUG_H */

