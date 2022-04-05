#include "SetOfBusLines.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

SetOfBusLines::SetOfBusLines(const string& filepath) : set_of_bus_lines_(get_set_of_bus_lines_from_file(filepath))
{
	
}

SetOfBusLines::~SetOfBusLines()
{
	clear();
}

vector<BusLine*> SetOfBusLines::get_set_of_bus_lines() const
{
	return set_of_bus_lines_;
}

void SetOfBusLines::set_bus_lines(vector<BusLine*> set_of_bus_lines)
{
	set_of_bus_lines_ = set_of_bus_lines;
}

bool SetOfBusLines::if_bus_line_in_set_of_bus_lines(const string& name_of_line) const
{
	for (auto e : set_of_bus_lines_) {
		if (e->get_name_of_line() == name_of_line) {
			return true;
		}
	}
	return false;
}



SetOfBusLines::SetOfBusLines(const SetOfBusLines& sobl)
{
	copy(sobl);
}

SetOfBusLines::SetOfBusLines(SetOfBusLines&& sobl)
{
	move(sobl);
}

SetOfBusLines& SetOfBusLines::operator=(const SetOfBusLines& sobl)
{
	if (this != &sobl)
	{
		clear();
		copy(sobl);
	}
	return *this;
}

SetOfBusLines& SetOfBusLines::operator=(SetOfBusLines&& sobl)
{
	if (this != &sobl)
	{
		clear();
		move(sobl);
	}
	return *this;
}

vector<BusLine*> SetOfBusLines::get_set_of_bus_lines_from_file(const string& filepath) const
{
	vector<BusLine*> set_of_bus_lines = {};
	ifstream input(filepath);
	string s;
	if (input.is_open()) {
		while (getline(input, s, '\n')) {
			set_of_bus_lines.push_back(new BusLine(get_name_of_line(s),get_time_of_first_departure(s),
				get_time_of_last_departure(s), get_interval_between_departures(s), get_id_of_stations(s)));
		}
	}
	else {
		
	}
	return set_of_bus_lines;
}

void SetOfBusLines::clear()
{
	for (auto e : set_of_bus_lines_) {
		delete e;
	}
	set_of_bus_lines_ = {};
}

void SetOfBusLines::copy(const SetOfBusLines& sobl)
{
	set_of_bus_lines_ = sobl.set_of_bus_lines_;

}

void SetOfBusLines::move(SetOfBusLines& sobl)
{
	set_of_bus_lines_ = sobl.set_of_bus_lines_;
	sobl.set_of_bus_lines_ = {};
}

string SetOfBusLines::get_name_of_line(const string& bus_line)
{
	int i = 0;
	while (i < bus_line.length()) {
		if (bus_line[i] == ' ') {
			break;
		}
		else {
			i++;
		}
	}
	return bus_line.substr(0, i);
}

string SetOfBusLines::get_time_of_first_departure(const string& bus_line) 
{
	int i = 0, t;
	while (i < bus_line.length()) {
		if (bus_line[i] == '[') {
			t = ++i;
		}
		else if (bus_line[i] == '-') {
			break;
		}
		else {
			i++;
		}

	}
	return bus_line.substr(t, i - t);
}

string SetOfBusLines::get_time_of_last_departure(const string& bus_line)
{
	int i = 0, t;
	while (i < bus_line.length()) {
		if (bus_line[i] == '-') {
			t = ++i;
		}
		else if (bus_line[i] == '#') {
			break;
		}
		else {
			i++;
		}
	}
	return bus_line.substr(t, i - t);
}

int SetOfBusLines::get_interval_between_departures(const string& bus_line)
{
	int i = 0, t;
	while (i < bus_line.length()) {
		if (bus_line[i] == '#') {
			i++;
			t = i;
		}
		else if (bus_line[i] == ']') {
			break;
		}
		else {
			i++;
		}
	}

	return stoi(bus_line.substr(t, i - t));
}

vector<int> SetOfBusLines::get_id_of_stations(const string& bus_line)
{
	int i = 0, t;
	vector<int> id_of_stations = {};
	while (i < bus_line.length()) {
		if (bus_line[i] == ']') {
			t = i + 2;
			i = t;
			break;
		}
		else {
			i++;
		}
	}

	while (i < bus_line.length()) {
		if (bus_line[i] == ' ') {
			id_of_stations.push_back(stoi(bus_line.substr(t, i - t)));
			t = ++i;
		}
		else {
			i++;
		}
	}
	id_of_stations.push_back(stoi(bus_line.substr(t, i - t)));
	return id_of_stations;
}
