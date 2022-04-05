#ifndef STRATEGY_STATION_H
#define STRATEGY_STATION_H

#include "Station.h"

class StrategyStation
{
public:

	virtual void execute(Station* station) const = 0;
};

#endif