#ifndef PUBLIC_TRANSPORT_NETWORK_H
#define PUBLIC_TRANSPORT_NETWORK_H

#include "SetOfBusLines.h"
#include "SetOfStations.h"
#include "Simulator.h"
#include "SimulatorStrategy.h"
#include "StrategyBusLine.h"
#include "StrategyStation.h"



class PublicTransportNetwork
{
public:
	PublicTransportNetwork(const string& file_with_set_of_stations, const string& file_with_set_of_bus_lines);
	~PublicTransportNetwork();
	
	void information_about_station(const int& id_of_station, StrategyStation& strategy) const;
	void information_about_bus_line(const string& name_of_line, StrategyBusLine& strategy) const;
	void statistics_about_bus_line(const string& name_of_line, StrategyBusLine& strategy) const;
	void activation_of_simulator(const int& time, const int& id_of_first_station, const int& id_of_last_station);

	void find_path(SimulatorStrategy& strategy) const;
	void find_error_station(const string& id_of_station) const;
	void find_error_bus_line(const string& name_of_line) const;

	SetOfBusLines* get_set_of_bus_lines() const;
	SetOfStations* get_set_of_stations() const;

	PublicTransportNetwork(const PublicTransportNetwork& ptn);
	PublicTransportNetwork(PublicTransportNetwork&& ptn);

	PublicTransportNetwork& operator = (const PublicTransportNetwork& ptn);
	PublicTransportNetwork& operator = (PublicTransportNetwork&& ptn);

private:

	SetOfStations* set_of_stations_;
	SetOfBusLines* set_of_bus_lines_;
	Simulator* simulator_;

	void clear();
	void copy(const PublicTransportNetwork& ptn);
	void move(PublicTransportNetwork& ptn);
	static int string_to_integer(const string& line);
};

#endif