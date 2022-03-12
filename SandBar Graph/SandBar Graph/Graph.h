#pragma once
#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>

class Graph {
private:
	int bar; //represents the bar number
	int sand; //represents the sand number on top of bar
public:
	//default ctor
	Graph();
	//overloaded ctor
	Graph(int, int);
	~Graph();
	//set bar to value
	void setBar(int);
	//return current bar value
	int getBar();
	//set sand to value
	void setSand(int);
	//return current sand value
	int getSand();
};

#endif /* GRAPH_H_ */


