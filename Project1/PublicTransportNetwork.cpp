#include "PublicTransportNetwork.h"
#include "Exceptions.h"
#include <iostream>
using namespace std;

PublicTransportNetwork::PublicTransportNetwork(const string& file_with_set_of_stations, const string& file_with_set_of_bus_lines) : 
set_of_stations_(new SetOfStations(file_with_set_of_stations)), 
set_of_bus_lines_(new SetOfBusLines(file_with_set_of_bus_lines))
{

}

PublicTransportNetwork::~PublicTransportNetwork()
{
    clear();
}

void PublicTransportNetwork::information_about_station(const int& id_of_station, StrategyStation& strategy) const
{
    Station* station = nullptr;
    for (auto e : set_of_stations_->get_set_of_stations()) {
        if (e->get_id_of_station() == id_of_station) {
            station = e;
            break;
        }
    }
    strategy.execute(station);
}

void PublicTransportNetwork::information_about_bus_line(const string& name_of_line, StrategyBusLine& strategy) const
{
    BusLine* bus_line = nullptr;
    for (auto e : set_of_bus_lines_->get_set_of_bus_lines()) {
        if (e->get_name_of_line() == name_of_line) {
            bus_line = e;
            break;
        }
    }
    strategy.execute(bus_line);
}

void PublicTransportNetwork::statistics_about_bus_line(const string& name_of_line, StrategyBusLine& strategy) const
{
    BusLine* bus_line = nullptr;
    for (auto e : set_of_bus_lines_->get_set_of_bus_lines()) {
        if (e->get_name_of_line() == name_of_line) {
            bus_line = e;
            break;
        }
    }
    strategy.execute(bus_line);
}

void PublicTransportNetwork::activation_of_simulator(const int& time, const int& id_of_first_station, 
    const int& id_of_last_station)
{
    simulator_ = new Simulator(time, id_of_first_station, id_of_last_station, set_of_bus_lines_);
    
}

void PublicTransportNetwork::find_path(SimulatorStrategy& strategy) const
{
    strategy.find_path(simulator_);
}

void PublicTransportNetwork::find_error_station(const string& id_of_station) const
{
    int i;
    for (i = 0; i < id_of_station.size(); i++) {
        if (isalpha(id_of_station[i])) {
            throw Exceptions("Sifra stajalista je sastavljena samo od brojeva. ");
        }
    }
    
    if (!set_of_stations_->if_station_in_set_of_stations(string_to_integer(id_of_station))) {
        throw Exceptions("Izabrano stajaliste ne postoji.");
    }
    
}

void PublicTransportNetwork::find_error_bus_line(const string& name_of_line) const
{
    if (!set_of_bus_lines_->if_bus_line_in_set_of_bus_lines(name_of_line)) {
        throw Exceptions("Izabrana linija ne postoji.");
    }
}

SetOfBusLines* PublicTransportNetwork::get_set_of_bus_lines() const
{
    return set_of_bus_lines_;
}

SetOfStations* PublicTransportNetwork::get_set_of_stations() const
{
    return set_of_stations_;
}

PublicTransportNetwork::PublicTransportNetwork(const PublicTransportNetwork& ptn)
{
    copy(ptn);
}

PublicTransportNetwork::PublicTransportNetwork(PublicTransportNetwork&& ptn)
{
    move(ptn);
}

PublicTransportNetwork& PublicTransportNetwork::operator=(const PublicTransportNetwork& ptn)
{
    if (this != &ptn)
    {
        clear();
        copy(ptn);
    }
    return *this;
}

PublicTransportNetwork& PublicTransportNetwork::operator=(PublicTransportNetwork&& ptn)
{
    if (this != &ptn)
    {
        clear();
        move(ptn);
    }
    return *this;
}

void PublicTransportNetwork::clear()
{
    delete simulator_;
    delete set_of_bus_lines_;
    delete set_of_stations_;

    simulator_ = nullptr;
    set_of_bus_lines_ = nullptr;
    set_of_stations_ = nullptr;
}

void PublicTransportNetwork::copy(const PublicTransportNetwork& ptn)
{
    set_of_bus_lines_ = new SetOfBusLines(*ptn.set_of_bus_lines_);
    set_of_stations_ = new SetOfStations(*ptn.set_of_stations_);
    simulator_ = new Simulator(*ptn.simulator_);
}

void PublicTransportNetwork::move(PublicTransportNetwork& ptn)
{
    set_of_bus_lines_ = ptn.set_of_bus_lines_;
    set_of_stations_ = ptn.set_of_stations_;
    simulator_ = ptn.simulator_;
    ptn.set_of_bus_lines_ = nullptr;
    ptn.set_of_stations_ = nullptr;
    ptn.simulator_ = nullptr;
}

int PublicTransportNetwork::string_to_integer(const string& line) 
{
    
    int number = 0;
    for (int i = 0; i < line.size(); i++) {
        number = 10 * number + line[i] - '0';
    }
    return number;
    
}
