#include "Graph.h"

Graph::Graph() {
	this->sand = 0;
	this->bar = 0;

}

Graph::Graph(int b, int s)
{
	if (b < 0 || s < 0)
	{
		this->sand = 0;
		this->bar = 0;
	}
	else
	{
		this->sand = s;
		this->bar = b;
	}
}

Graph::~Graph() {

}

int Graph::getBar()
{
	return this->bar;
}

void Graph::setBar(int b)
{
	if (b >= 0)
		this->bar = b;
}

int Graph::getSand()
{
	return this->sand;
}

void Graph::setSand(int s)
{
	if (s >= 0)
		this->sand = s;
}
