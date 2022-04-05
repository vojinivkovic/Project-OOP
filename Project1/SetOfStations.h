#ifndef SET_OF_STATIONS_H
#define SET_OF_STATIONS_H

#include "Station.h"
#include <vector>


class SetOfStations
{
public:
	SetOfStations(const string& filepath);
	~SetOfStations();

	vector<Station*> get_set_of_stations() const;
	bool if_station_in_set_of_stations(const int& id_of_station) const;
	


	SetOfStations(const SetOfStations& sos);
	SetOfStations(SetOfStations&& sos);

	SetOfStations& operator = (const SetOfStations& sos);
	SetOfStations& operator = (SetOfStations&& sos);

private:


	vector<Station*> set_of_stations_;

	void clear();
	void copy(const SetOfStations& sos);
	void move(SetOfStations& sos);

	static vector<Station*> get_set_of_stations_from_file(const string& filepath);
	static int get_id_of_station(const string& station);
	static string get_name_of_station(const string& station);

};
#endif 
