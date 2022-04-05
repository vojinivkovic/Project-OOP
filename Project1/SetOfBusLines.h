#ifndef SET_OF_BUS_LINES_H
#define SET_OF_BUS_LINES_H

#include "BusLine.h"
#include <vector>

using namespace std;


class SetOfBusLines
{
public:

	SetOfBusLines(const string& filepath);
	~SetOfBusLines();

	vector<BusLine*> get_set_of_bus_lines() const;
	void set_bus_lines(vector<BusLine*> set_of_bus_lines);
	bool if_bus_line_in_set_of_bus_lines(const string& name_of_line) const;


	SetOfBusLines(const SetOfBusLines& sobl);
	SetOfBusLines(SetOfBusLines&& sobl);

	SetOfBusLines& operator = (const SetOfBusLines& sobl);
	SetOfBusLines& operator = (SetOfBusLines&& sobl);

private:
	vector <BusLine*> set_of_bus_lines_;
	vector <BusLine*> get_set_of_bus_lines_from_file(const string& filepath) const;

	void clear();
	void copy(const SetOfBusLines& sobl);
	void move(SetOfBusLines& sobl);

	static string get_name_of_line(const string& bus_line);
	static string get_time_of_first_departure(const string& bus_line);
	static string get_time_of_last_departure(const string& bus_line);
	static int get_interval_between_departures(const string& bus_line);
	static vector<int> get_id_of_stations(const string& bus_line);
};
#endif
