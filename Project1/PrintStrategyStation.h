#ifndef PRINT_STRATEGY_STATION_H
#define PRINT_STRATEGY_STATION_H

#include "SetOfBusLines.h"
#include "StrategyStation.h"

#include <fstream>

using namespace std;
class PrintStrategyStation1 : public StrategyStation
{
public:

	PrintStrategyStation1(ofstream& output, SetOfBusLines* set_of_bus_lines);
	virtual void execute(Station* station) const override;

private:

	ofstream& output_;
	SetOfBusLines* set_of_bus_lines_;

};

#endif

