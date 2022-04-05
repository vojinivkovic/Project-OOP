#include "FindPathStrategy.h"
#include <iostream>

using namespace std;

AnyPathStrategy::AnyPathStrategy(ofstream& output): output_(output)
{
}

void AnyPathStrategy::find_path(Simulator* simulator) 
{
	Node* root = simulator->get_root();
	vector<Node*> layer_of_nodes = root->set_of_next_nodes_;
	vector<Node*> path = {};
	int flag_find_last_node = 0;

	Node* last_node = nullptr;

	while (!layer_of_nodes.empty()) {
		for (auto e : layer_of_nodes) {
			if (e->id_of_station_ == simulator->get_id_of_last_station()) {
				last_node = e;
				flag_find_last_node = 1;
				break;
			}
		}

		if (flag_find_last_node) {
			break;
		}
		vector <Node*> temp_vector = {};

		for (auto e : layer_of_nodes) {
			add_vectors(temp_vector, e->set_of_next_nodes_);
		}
		layer_of_nodes = temp_vector;
	}
	
	while (last_node->previous_node_) {
		path.push_back(last_node);
		last_node = last_node->previous_node_;
	}

	write_in_file(path, output_);
}



void add_vectors(vector<Node*>& vector1, vector<Node*> vector2)
{
	vector1.insert(vector1.end(), vector2.begin(), vector2.end());
}

void write_in_file(vector<Node*> path, ofstream& output)
{
	int size = path.size();
	int i = size - 1;
	string name_of_line = "";

	while (i >= 0) {
		output << name_of_line << "->" << path[i]->bus_line_->get_name_of_line() << endl;
		name_of_line = path[i]->bus_line_->get_name_of_line();
		while (path[i]->bus_line_->get_name_of_line() == name_of_line) {
			output << path[i]->id_of_station_ << " ";
			if (i == 0) {
				break;
			}
			i--;
		}
		if (i == 0) {
			break;
		}
		output << path[i]->id_of_station_ << endl;
	}
}

ShortestPathStrategy::ShortestPathStrategy(ofstream& output) : output_(output)
{
}

void ShortestPathStrategy::find_path(Simulator* simulator)
{
	Node* root = simulator->get_root();
	int min_time = find_shortest_time(simulator);
	vector<Node*> layer_of_nodes = root->set_of_next_nodes_;
	vector<Node*> path = {};
	Node* last_node = nullptr;

	int flag_find_last_node = 0;

	while (!layer_of_nodes.empty()) {
		for (auto e : layer_of_nodes) {
			if (e->id_of_station_ == simulator->get_id_of_last_station()) {
				if (e->time_ == min_time) {
					last_node = e;
					flag_find_last_node = 1;
					break;
				}
			}
		}

		if (flag_find_last_node) {
			break;
		}

		vector <Node*> temp_vector = {};

		for (auto e : layer_of_nodes) {
			add_vectors(temp_vector, e->set_of_next_nodes_);
		}
		layer_of_nodes = temp_vector;
	}

	while (last_node->previous_node_) {
		path.push_back(last_node);
		last_node = last_node->previous_node_;
	}
	write_in_file(path, output_);

}

int ShortestPathStrategy::find_shortest_time(Simulator* simulator)
{
	Node* root = simulator->get_root();
	vector <Node*>layer_of_nodes = root->set_of_next_nodes_;
	int min_time = 0;

	while (!layer_of_nodes.empty()) {
		for (auto e : layer_of_nodes) {
			if (e->id_of_station_ == simulator->get_id_of_last_station()) {
				min_time = e->time_;
				break;
			}
		}
	
		if (min_time) {
			break;
		}
		vector <Node*> temp_vector = {};

		for (auto e : layer_of_nodes) {
			for (auto e1 : e->set_of_next_nodes_) {
				temp_vector.push_back(e1);
			}
		}
		layer_of_nodes = temp_vector;
	}

	layer_of_nodes = root->set_of_next_nodes_;
	while (!layer_of_nodes.empty()) {
		for (auto e : layer_of_nodes) {
			if (e->id_of_station_ == simulator->get_id_of_last_station()) {
				if (e->time_ < min_time) {
					min_time = e->time_;
				}
				
			}
		}


		vector <Node*> temp_vector = {};

		for (auto e : layer_of_nodes) {
			for (auto e1 : e->set_of_next_nodes_) {
				temp_vector.push_back(e1);
			}
		}
		layer_of_nodes = temp_vector;
	}

	return min_time;
}

MinimumBusChangeStrategy::MinimumBusChangeStrategy(ofstream& output) : output_(output)
{
}

void MinimumBusChangeStrategy::find_path(Simulator* simulator)
{
	Node* root = simulator->get_root();
	int min_change = find_minimum_change(simulator);
	vector<Node*> layer_of_nodes = root->set_of_next_nodes_;
	vector<Node*> path = {};
	Node* last_node = nullptr;

	int flag_find_last_node = 0;

	while (!layer_of_nodes.empty()) {
		for (auto e : layer_of_nodes) {
			if (e->id_of_station_ == simulator->get_id_of_last_station()) {
				if (e->number_of_bus_change_ == min_change) {
					last_node = e;
					flag_find_last_node = 1;
					break;
				}
			}
		}

		if (flag_find_last_node) {
			break;
		}

		vector <Node*> temp_vector = {};

		for (auto e : layer_of_nodes) {
			add_vectors(temp_vector, e->set_of_next_nodes_);
		}
		layer_of_nodes = temp_vector;
	}

	while (last_node->previous_node_) {
		path.push_back(last_node);
		last_node = last_node->previous_node_;
	}
	write_in_file(path, output_);
}

int MinimumBusChangeStrategy::find_minimum_change(Simulator* simulator)
{
	Node* root = simulator->get_root();
	vector <Node*>layer_of_nodes = root->set_of_next_nodes_;
	int min_change = 0;

	while (!layer_of_nodes.empty()) {
		for (auto e : layer_of_nodes) {
			if (e->id_of_station_ == simulator->get_id_of_last_station()) {
				min_change = e->number_of_bus_change_;
				break;
			}
		}

		if (min_change) {
			break;
		}
		vector <Node*> temp_vector = {};

		for (auto e : layer_of_nodes) {
			for (auto e1 : e->set_of_next_nodes_) {
				temp_vector.push_back(e1);
			}
		}
		layer_of_nodes = temp_vector;
	}


	layer_of_nodes = root->set_of_next_nodes_;

	while (!layer_of_nodes.empty()) {
		for (auto e : layer_of_nodes) {
			if (e->id_of_station_ == simulator->get_id_of_last_station()) {
				if (e->number_of_bus_change_ < min_change) {
					min_change = e->number_of_bus_change_;
				}

			}
		}


		vector <Node*> temp_vector = {};

		for (auto e : layer_of_nodes) {
			for (auto e1 : e->set_of_next_nodes_) {
				temp_vector.push_back(e1);
			}
		}
		layer_of_nodes = temp_vector;
	}

	return min_change;
}
