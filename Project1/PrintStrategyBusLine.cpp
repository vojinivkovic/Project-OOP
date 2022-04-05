#include "PrintStrategyBusLine.h"
#include <vector>


PrintStrategyBusLine1::PrintStrategyBusLine1(ofstream& output, SetOfStations* set_of_stations) : output_(output), 
set_of_stations_(set_of_stations)
{
}

void PrintStrategyBusLine1::execute(BusLine* bus_line) const
{
	int i;
	vector<string> names_of_stations_of_bus_line = {};
	names_of_stations_of_bus_line = bus_line->get_names_of_stations_of_bus_line(set_of_stations_);
	output_ << bus_line->get_name_of_line() << " " << names_of_stations_of_bus_line[0] << "->"
		<< names_of_stations_of_bus_line[names_of_stations_of_bus_line.size() - 1] << endl;

	for (i = 0; i < bus_line->get_id_of_stations().size(); i++) {
		output_ << bus_line->get_id_of_stations()[i] << " " 
			<< names_of_stations_of_bus_line[i] << endl;
	}
}
