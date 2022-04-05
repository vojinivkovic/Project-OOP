#include "Simulator.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Simulator::Simulator(const int& time, const int& id_of_first_station, const int& id_of_last_station,
	SetOfBusLines* set_of_bus_lines) : id_of_last_station_(id_of_last_station), set_of_bus_lines_(new SetOfBusLines(*set_of_bus_lines))
{
	root = new Node(nullptr, time, id_of_first_station, nullptr, 1);
	add_additional_lines();
	build_simulator();
}

Simulator::~Simulator()
{
	delete set_of_bus_lines_;

	vector<Node*> layer_of_nodes = root->set_of_next_nodes_;
	vector<Node*> temp_vector;

	while (!layer_of_nodes.empty()) {
		temp_vector = {};
		for (auto e : layer_of_nodes) {
			add_vectors(temp_vector, e->set_of_next_nodes_);
		}
		for (auto e : layer_of_nodes) {
			delete e;
		}
		layer_of_nodes = temp_vector;
	}

}

void Simulator::build_simulator()
{
	
	add_nodes_of_root(root);

	vector<Node*> layer_of_nodes = root->set_of_next_nodes_;
	vector<Node*> temp_vector;


	while (!layer_of_nodes.empty()) {
		temp_vector = {};
		for (auto e : layer_of_nodes) {
			add_nodes(e);
			add_vectors(temp_vector, e->set_of_next_nodes_);
		}
		layer_of_nodes = temp_vector;
	}


	
}

Node* Simulator::get_root() const
{
	return root;
}

int Simulator::get_id_of_last_station() const
{
	return id_of_last_station_;
}

void Simulator::add_nodes_of_root(Node *root)
{
	vector<BusLine*> bus_lines_at_station = {};
	for (auto e : set_of_bus_lines_->get_set_of_bus_lines()) {
		if (e->if_bus_line_goes_to_station(root->id_of_station_)) {
			bus_lines_at_station.push_back(e);
		}
	}
	
	for (auto e : bus_lines_at_station) {
		root->set_of_next_nodes_.push_back( new Node(root, e->arrival_at_station(root->time_, root->id_of_station_), root->id_of_station_, e, 1));
	}
}

void Simulator::add_nodes(Node* node)
{
	node->set_of_next_nodes_ = {};
	if (node->id_of_station_ == id_of_last_station_) {
		return;
	}

	if (node->id_of_station_ ==
		node->bus_line_->get_id_of_stations()[node->bus_line_->get_id_of_stations().size() - 1]) {
		return;
	}


	int next_station = node->bus_line_->next_station(node->id_of_station_);
	int flag_end = 0;
	int flag_last_station_of_bus = 0;


	if (station_at_path(node, next_station)) {
		return;
	}

	if (next_station == id_of_last_station_) {
		flag_end = 1;
	}

	if (next_station == node->bus_line_->get_id_of_stations()[node->bus_line_->get_id_of_stations().size() - 1]) {
		flag_last_station_of_bus = 1;
	}

	vector<BusLine*> bus_lines_at_station = {};
	for (auto e : set_of_bus_lines_->get_set_of_bus_lines()) {
		if (e->if_bus_line_goes_to_station(next_station)) {
			bus_lines_at_station.push_back(e);
		}
	}

	int time_of_arrival_at_next_station = node->time_ + 3;

	if (flag_end) {
		node->set_of_next_nodes_.push_back(new Node(node, time_of_arrival_at_next_station, next_station,
			node->bus_line_, node->number_of_bus_change_));
	}
	else if (flag_last_station_of_bus) {
		node->set_of_next_nodes_.push_back(new Node(node, time_of_arrival_at_next_station, next_station, 
			node->bus_line_, node->number_of_bus_change_));
	}
	else {
		for (auto e : bus_lines_at_station) {
			if (node->bus_line_->get_name_of_line() == e->get_name_of_line()) {
				node->set_of_next_nodes_.push_back(new Node(node,
					e->arrival_at_station(time_of_arrival_at_next_station, next_station),
					next_station, e, node->number_of_bus_change_));
			}
			else {
				node->set_of_next_nodes_.push_back(new Node(node,
					e->arrival_at_station(time_of_arrival_at_next_station, next_station),
					next_station, e, node->number_of_bus_change_ + 1));
			}
		}
	}
}



void Simulator::add_additional_lines()
{
	vector<BusLine*> bus_lines = {};
	for (BusLine* e : set_of_bus_lines_->get_set_of_bus_lines()) {
		bus_lines.push_back(new BusLine(*e));
		vector<int> id_of_stations = reverse_station(e->get_id_of_stations());

		bus_lines.push_back(new BusLine(e->get_name_of_line(), e->get_time_of_first_departure(), e->get_time_of_last_departure(),
			e->get_interval_between_departures(), id_of_stations));
	}

	set_of_bus_lines_->set_bus_lines(bus_lines);
}



vector<int> Simulator::reverse_station(vector<int> id_of_stations)
{


	vector<int> new_id_od_stations = {};
	int i;
	int size = id_of_stations.size();
	for (i = size - 1; i >= 0; i--) {
		new_id_od_stations.push_back(id_of_stations[i]);
	}
	return new_id_od_stations;
}

int Simulator::station_at_path(Node* node, const int& id_of_next_station)
{
	Node* temp = node->previous_node_;
	while (temp->previous_node_) {
		if (temp->id_of_station_ == id_of_next_station) {
			return 1;
		}
		temp = temp->previous_node_;
	}
	return 0;
}

void Simulator::add_vectors(vector<Node*>& vector1, vector<Node*> vector2)
{
	vector1.insert(vector1.end(), vector2.begin(), vector2.end());
}

