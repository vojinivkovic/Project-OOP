#ifndef STATION_H
#define STATION_H


#include <string>
#include <vector>

class SetOfBusLines;

using namespace std;

class Station
{
public:

	Station(const int& id_of_station, const string& name_of_station);
	int get_id_of_station() const;
	string get_name_of_station() const;
	vector<string> get_set_of_bus_lines_on_station(SetOfBusLines* set_of_bus_lines) const;


private:

	int id_of_station_;
	string name_of_station_;

	void sort_names_set_of_bus_lines(vector<string> set_of_bus_lines_on_station) const;

};

#endif