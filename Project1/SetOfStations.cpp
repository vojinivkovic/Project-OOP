#include "SetOfStations.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;


SetOfStations::SetOfStations(const string& filepath) : set_of_stations_(get_set_of_stations_from_file(filepath))
{
	
}

SetOfStations::~SetOfStations()
{
	clear();
}

vector<Station*> SetOfStations::get_set_of_stations() const
{
	return set_of_stations_;
}

bool SetOfStations::if_station_in_set_of_stations(const int& id_of_station) const
{
	for (auto e : set_of_stations_) {
		if (e->get_id_of_station() == id_of_station) {
			return true;
		}
	}
	return false;
}



SetOfStations::SetOfStations(const SetOfStations& sos)
{
	copy(sos);
}

SetOfStations::SetOfStations(SetOfStations&& sos)
{
	move(sos);
}

SetOfStations& SetOfStations::operator=(const SetOfStations& sos)
{
	if (this != &sos)
	{
		clear();
		copy(sos);
	}
	return *this;
}

SetOfStations& SetOfStations::operator=(SetOfStations&& sos)
{
	if (this != &sos)
	{
		clear();
		move(sos);
	}
	return *this;
}

void SetOfStations::clear()
{
	for (auto e : set_of_stations_) {
		delete e;
	}
	set_of_stations_ = {};
}

void SetOfStations::copy(const SetOfStations& sos)
{
	set_of_stations_ = sos.set_of_stations_;
}

void SetOfStations::move(SetOfStations& sos)
{
	set_of_stations_ = sos.set_of_stations_;
	sos.set_of_stations_ = {};
}

vector<Station*> SetOfStations::get_set_of_stations_from_file(const string& filepath)
{
	vector<Station*> set_of_stations = {};
	ifstream input(filepath);
	string s;
	if (input.is_open()) {
		while (getline(input, s, '\n')) {
			set_of_stations.push_back(new Station(get_id_of_station(s), get_name_of_station(s)));
		}
	}
	else {

	}
	return set_of_stations;
}

int SetOfStations::get_id_of_station(const string& station)
{

	int i = 0;
	while (i < station.length()) {
		if (station[i] == ' ') {
			break;
		}
		else {
			i++;
		}
	}

	return stoi(station.substr(0, i));
}

string SetOfStations::get_name_of_station(const string& station)
{
	int i = 0;
	while (i < station.length()) {
		if (station[i] == ' ') {
			i++;
			break;
		}
		else {
			i++;
		}
	}
	return station.substr(i, station.length());
}
