/*
 * stdnamespaces.h
 *
 *  Created on: 07.01.2015
 *      Author: chris
 */

#ifndef STDNAMESPACES_H_
#define STDNAMESPACES_H_

// We use a fixed compiler level of C++14, so shared_ptr should be in <memory> (like it is in C++11)
//#include <memory>
//using std::shared_ptr;
#include <tr1/memory>
using std::tr1::shared_ptr;

#endif /* STDNAMESPACES_H_ */
