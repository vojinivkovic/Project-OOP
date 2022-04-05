#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "SetOfBusLines.h"

struct Node {
	Node* previous_node_;
	vector<Node*> set_of_next_nodes_;
	BusLine* bus_line_;
	int time_;
	int id_of_station_;
	int number_of_bus_change_;
	Node(Node* previous_node, int time, int id_of_station, BusLine* bus_line, int number_of_bus_change) :
		previous_node_(previous_node), time_(time), id_of_station_(id_of_station),
		bus_line_(bus_line), number_of_bus_change_ (number_of_bus_change) {}
};

class Simulator
{
public:
	Simulator(const int& time, const int& id_of_first_station, const int& id_of_last_station,
		SetOfBusLines* set_of_bus_lines);
	~Simulator();

	Node* get_root() const;
	int get_id_of_last_station() const;

private:

	Node* root;
	SetOfBusLines* set_of_bus_lines_;

	int id_of_last_station_;

	void add_nodes_of_root(Node* root);
	void add_nodes(Node* node);
	static void add_vectors(vector<Node*>& vector1, vector<Node*> vector2);
	void add_additional_lines();
	void build_simulator();

	static vector<int> reverse_station(vector<int> id_of_stations);
	static int station_at_path(Node* node, const int& id_of_next_station);
};

#endif