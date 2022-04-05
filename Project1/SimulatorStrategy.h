#ifndef SIMULATOR_STRATEGY_H
#define SIMULATOR_STRATEGY_H

#include "Simulator.h"

class SimulatorStrategy
{
public:
	virtual void find_path(Simulator* simulator) = 0;

};

#endif