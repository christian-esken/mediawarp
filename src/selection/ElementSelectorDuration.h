/*
 * ElementSelectorDuration.h
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#ifndef ELEMENTSELECTOR_Duration_H_
#define ELEMENTSELECTOR_Duration_H_

#include <vector>       // std::vector

#include "../selection/ElementSelector.h"
#include "../model/MediaItem.h"
#include "../util/Constants.h"
#include "../util/stdnamespaces.h"

class ElementSelectorDuration : public ElementSelector
{
public:
	ElementSelectorDuration(int count, mediawarp::Constants::Unit unit);
	virtual ~ElementSelectorDuration();

	std::vector<shared_ptr<MediaItem> > select(std::vector<shared_ptr<MediaItem> > ventries) override;

protected:
	mediawarp::Constants::Unit unit;
};

#endif /* ELEMENTSELECTORDuration_H_ */
