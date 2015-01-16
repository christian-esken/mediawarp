/*
 * FilterFactory.h
 *
 *  Created on: 15.01.2015
 *      Author: chris
 */

#ifndef SRC_FILTER_FILTERFACTORY_H_
#define SRC_FILTER_FILTERFACTORY_H_

#include "BaseFilter.h"

class FilterFactory
{
public:
	static BaseFilter* build(QString filterString);

protected:
	FilterFactory();
	virtual ~FilterFactory();
};

#endif /* SRC_FILTER_FILTERFACTORY_H_ */
