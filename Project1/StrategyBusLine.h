#ifndef STRATEGY_BUS_LINE_H
#define STRATEGY_BUS_LINE_H

#include "BusLine.h"
class StrategyBusLine
{
public:

	virtual void execute(BusLine* bus_line) const = 0;
};

#endif
