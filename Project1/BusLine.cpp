#include "BusLine.h"
#include <iostream>

#include "SetOfStations.h"
using namespace std;


BusLine::BusLine(const string& name_of_line, const string& time_of_first_departure, const string& time_of_last_departure,
    const int& interval_between_departures, const vector<int>& id_of_stations) :
    name_of_line_(name_of_line),
    time_of_first_departure_(time_of_first_departure),
    time_of_last_departure_(time_of_last_departure),
    interval_between_departures_(interval_between_departures),
    id_of_stations_(id_of_stations)
{
}

string BusLine::get_name_of_line() const
{
    return name_of_line_;
}

string BusLine::get_time_of_first_departure() const
{
    return time_of_first_departure_;
}

string BusLine::get_time_of_last_departure() const
{
    return time_of_last_departure_;
}

int BusLine::get_interval_between_departures() const
{
    return interval_between_departures_;
}

vector<int> BusLine::get_id_of_stations() const
{
    return id_of_stations_;
}

int BusLine::number_of_departures() const
{
    int time1, time2;
    int number_of_departures;
    time1 = get_minutes_from_time(time_of_first_departure_);
    time2 = get_minutes_from_time(time_of_last_departure_);
    number_of_departures = (time2 - time1) / interval_between_departures_ + 1;
    return number_of_departures;
    
}

vector<string> BusLine::get_names_of_stations_of_bus_line(SetOfStations* set_of_stations)
{
    vector<string> names_of_stations_of_bus_line = {};
    for (auto ei : id_of_stations_) {
        for(auto ej : set_of_stations->get_set_of_stations())
            if (ei == ej->get_id_of_station()) {
                names_of_stations_of_bus_line.push_back(ej->get_name_of_station());
            }
    }
    return names_of_stations_of_bus_line;
}

int BusLine::if_bus_line_goes_to_station(const int& id_of_station) const
{
    for (auto e : id_of_stations_) {
        if (e == id_of_station) {
            return 1;
        }
    }
    return 0;
}

int BusLine::if_same_station(BusLine* bus_line) const
{
    for (auto ei : id_of_stations_) {
        for (auto ej : bus_line->get_id_of_stations()) {
            if (ei == ej) {
                return 1;
            }
        }
    }
    return 0;
}

int BusLine::arrival_at_station(const int& time_of_arrival, const int& id_of_station) const
{
    int bus_arrival;
    int time = get_minutes_from_time(time_of_first_departure_);
    int time_of_last_departure = get_minutes_from_time(time_of_last_departure_);
    int number_of_station = 0;
    

    for (auto e : id_of_stations_) {
        if (e == id_of_station) {
            break;
        }
        number_of_station++;
    }
    while (time <= time_of_last_departure) {
        bus_arrival = time + number_of_station * 3;
        if (bus_arrival >= time_of_arrival) {
            return bus_arrival;
        }
        time = time + interval_between_departures_;
        
    }
     
    
    

}



int BusLine::next_station(const int& id_of_station) const
{
    int flag = 0;
    for (auto e : id_of_stations_) {
        if (flag) {
            return e;
        }
        if (e == id_of_station) {
            flag = 1;
        }
    }
}



int BusLine::get_minutes_from_time(const string& time)
{
    int index_of_dots;
    int hours = 0, minutes = 0;
    int i;
    for (i = 0; i < time.length(); i++) {
        if (time[i] == ':') {
            index_of_dots = i;
            break;
        }
    }
    for (i = 0; i < index_of_dots; i++) {
        hours = 10 * hours + time[i] - '0';
    }
    for (i = index_of_dots + 1; i < time.length(); i++) {
        minutes = minutes * 10 + time[i] - '0';

    }
    
    return (hours * 60 + minutes);
}


