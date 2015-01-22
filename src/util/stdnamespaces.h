/*
 * stdnamespaces.h
 *
 *  Created on: 07.01.2015
 *      Author: chris
 */

#ifndef STDNAMESPACES_H_
#define STDNAMESPACES_H_

// We use a fixed compiler level of C++11, so shared_ptr should be in <memory>
// But it isn't, which may be a sign that the compile switches are not perfectly set.
//#include <memory>
//using std::shared_ptr;
#include <tr1/memory>
using std::tr1::shared_ptr;

using std::cout;
using std::cerr;
using std::endl;

#endif /* STDNAMESPACES_H_ */
