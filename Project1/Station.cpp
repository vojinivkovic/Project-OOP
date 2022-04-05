#include "SetOfBusLines.h"
#include "Station.h"


Station::Station(const int& id_of_station, const string& name_of_station) : id_of_station_(id_of_station), name_of_station_(name_of_station)
{
}

int Station::get_id_of_station() const
{
	return id_of_station_;
}

string Station::get_name_of_station() const
{
	return name_of_station_;
}

vector<string> Station::get_set_of_bus_lines_on_station(SetOfBusLines* set_of_bus_lines) const
{
	vector<string> set_of_bus_lines_on_station = {};
	for (auto e : set_of_bus_lines->get_set_of_bus_lines()) {
		if (e->if_bus_line_goes_to_station(id_of_station_)) {
			set_of_bus_lines_on_station.push_back(e->get_name_of_line());
		}
	}
	sort_names_set_of_bus_lines(set_of_bus_lines_on_station);
	return set_of_bus_lines_on_station;
	
}

void Station::sort_names_set_of_bus_lines(vector<string> set_of_bus_lines_on_station) const
{
	int i, j;
	int size = set_of_bus_lines_on_station.size();
	string tmp;
	for (i = 0; i < size; i++) {
		for (j = i + 1; j < size; j++) {
			if (set_of_bus_lines_on_station[i] > set_of_bus_lines_on_station[j]) {
				tmp = set_of_bus_lines_on_station[i];
				set_of_bus_lines_on_station[i] = set_of_bus_lines_on_station[j];
				set_of_bus_lines_on_station[j] = tmp;
			}
		}
	}
}


