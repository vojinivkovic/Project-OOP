#include "PrintStrategyStation.h"
#include <iostream>
using namespace std;


PrintStrategyStation1::PrintStrategyStation1(ofstream& output, SetOfBusLines* set_of_bus_lines) : output_(output), set_of_bus_lines_(set_of_bus_lines)
{
	
}

void PrintStrategyStation1::execute(Station* station) const
{
	int i = 0;
	output_ << station->get_id_of_station() << " " << station->get_name_of_station() << " [";
	for (auto e : station->get_set_of_bus_lines_on_station(set_of_bus_lines_)) {
		i++;
		if (i == station->get_set_of_bus_lines_on_station(set_of_bus_lines_).size()) {
			output_ << e << "]";
		}
		else {
			output_ << e << " ";
		}
	}
}
