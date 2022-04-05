#ifndef BUS_LINE_H
#define BUS_LINE_H



#include <string>
#include <vector>

class SetOfStations;

using namespace std;


class BusLine
{
public:

	BusLine(const string& name_of_line, const string& time_of_first_departure, const string& time_of_last_departure, 
		const int& interval_between_departures, const vector<int>& id_of_stations);

	string get_name_of_line() const;
	string get_time_of_first_departure() const;
	string get_time_of_last_departure() const;
	int get_interval_between_departures() const;
	vector<int> get_id_of_stations() const;
	
	int number_of_departures() const;
	
	vector<string> get_names_of_stations_of_bus_line(SetOfStations* set_of_stations);
	int if_bus_line_goes_to_station(const int& id_of_station) const;
	int if_same_station(BusLine* bus_line) const; 
	int arrival_at_station(const int& time_of_arrival, const int& id_of_station) const;
	int next_station(const int& id_of_station) const;
	

private:

	string name_of_line_;
	string time_of_first_departure_;
	string time_of_last_departure_;
	int interval_between_departures_;
	vector<int> id_of_stations_;

	static int get_minutes_from_time(const string& time);

};


#endif