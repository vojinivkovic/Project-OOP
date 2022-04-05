#ifndef STATISTICS_STRATEGY_BUS_LINE_H
#define STATISTICS_STRATEGY_BUS_LINE_H

#include "SetOfBusLines.h"
#include "StrategyBusLine.h"
#include <fstream>
using namespace std;

class StatisticsStrategyBusLine1 : public StrategyBusLine
{
public:

	StatisticsStrategyBusLine1(ofstream& output, SetOfBusLines* set_of_bus_lines);
	virtual void execute(BusLine* bus_line) const override;

private:

	ofstream& output_;
	SetOfBusLines* set_of_bus_lines_;
};

#endif
