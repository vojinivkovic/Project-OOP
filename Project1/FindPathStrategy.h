#ifndef FIND_PATH_STRATEGY_H
#define FIND_PATH_STRATEGY_H

#include "SimulatorStrategy.h"
#include <fstream>

void add_vectors(vector<Node*>& vector1, vector<Node*> vector2);
void write_in_file(vector<Node*> path, ofstream& output);

class AnyPathStrategy : public SimulatorStrategy
{
public:

	AnyPathStrategy(ofstream& output);
	virtual void find_path(Simulator* simulator)  override;

private:

	ofstream& output_;

};

class ShortestPathStrategy : public SimulatorStrategy {
public:

	ShortestPathStrategy(ofstream& output);
	virtual void find_path(Simulator* simulator) override;

private:

	ofstream& output_;
	static int find_shortest_time(Simulator* simulator);

};

class MinimumBusChangeStrategy : public SimulatorStrategy {
public:

	MinimumBusChangeStrategy(ofstream& output);
	virtual void find_path(Simulator* simulator) override;

private:

	ofstream& output_;
	static int find_minimum_change(Simulator* simulator);

};

#endif