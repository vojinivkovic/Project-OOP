#include "StatisticsStrategyBusLine.h"

StatisticsStrategyBusLine1::StatisticsStrategyBusLine1(ofstream& output, SetOfBusLines* set_of_bus_lines) : output_(output),
set_of_bus_lines_(set_of_bus_lines)
{
}

void StatisticsStrategyBusLine1::execute(BusLine* bus_line) const
{
	int flag = 1;
	output_ << bus_line->get_name_of_line() << endl;
	for (auto e : set_of_bus_lines_->get_set_of_bus_lines()) {
		if (e == bus_line) {
			continue;
		}
		if (bus_line->if_same_station(e)) {
			if (flag) {
				output_ << e->get_name_of_line();
				flag = 0;
				continue;
			}
			else {
				output_ << " " << e->get_name_of_line();
			}
		}
	}
	output_ << endl;
	output_ << bus_line->number_of_departures();
}
