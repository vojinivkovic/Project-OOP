#ifndef PRINT_STRATEGY_BUS_LINE_H
#define PRINT_STRATEGY_BUS_LINE_H

#include "SetOfStations.h"
#include "StrategyBusLine.h"

#include <fstream>

using namespace std;

class PrintStrategyBusLine1 : public StrategyBusLine
{
public:

	PrintStrategyBusLine1(ofstream& output, SetOfStations* set_of_stations);
	virtual void execute(BusLine* bus_line) const override;

private:

	ofstream& output_;
	SetOfStations* set_of_stations_;
};

#endif
