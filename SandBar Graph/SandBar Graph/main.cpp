// SandBar Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Harry Turner
//SID: 9284906

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>
#include "Graph.h"

using namespace std;

void promptUser(vector<int>& numbers);

int calculateSand(vector<Graph*>& v, const vector<int>& nums);

void drawGraphVertically(const vector<Graph*>& v);

void drawGraphHorizontally(const vector<Graph*>& v);

bool isNumber(string s);

void promptUser(vector<int>& numbers)
{
	//get input from user
	string input = "";
	cout << "Harry Turner" << endl << "9284906" << endl;
	cout << "Please enter the bar graph data with spaces directly, or" << endl;
	cout << "enter a filename to read from a text file input, or" << endl;
	cout << "type 'Random' to randomly generate a bar graph:" << endl;

	getline(cin, input);

	//if user typed random, generate 7 random numbers
	if (input == "Random" || input == "random")
	{
		cout << "Generating 7 random numbers" << endl;

		for (int i = 0; i < 7; ++i) {
			//generate two numbers between 1 and 15
			int rand1 = 5 + rand() % 15;
			numbers.push_back(rand1);
		}


		cout << "Generation done!" << endl;
	}
	//if user entered digits
	else if (isdigit(input[0]))
	{
		int num = 0;
		istringstream s(input);
		while (s >> num)
		{
			numbers.push_back(num);
		}
	}
	//if user entered file name
	else if (input.find(".txt") != string::npos)
	{
		ifstream file(input);
		string num;
		if (!file.is_open())
		{
			cout << input << " is not found" << endl;
			exit(EXIT_FAILURE);
		}
		cout << input << " read successfully" << endl;
		while (!file.eof())
		{
			file >> num;
			if (isNumber(num))
			{
				numbers.push_back(stoi(num));
			}

		}
	}
	//unknown input
	else
	{
		cout << "Can't process your input" << endl;
	}

}

int calculateSand(vector<Graph*>& v, const vector<int>& nums)
{
	int max = 0;
	int totalSand = 0;
	bool removeSand = true;
	//make sure that vector is empty
	v.clear();
	//for every column calculate amount of sand
	for (int i : nums)
	{
		if (i > max)
			max = i;
		Graph* g = new Graph(i, max - i);
		v.push_back(g);
	}
	v[v.size() - 1]->setSand(0);
	//check if elements after max element are smaller then remove sand
	//first find the index
	size_t maxindex = 0;
	for (;maxindex < nums.size(); maxindex++)
	{
		if (nums[maxindex] == max)
			break;
	}

	for (size_t i = maxindex + 1; i < nums.size() - 1; i++)
	{
		if (nums[i] < nums[i + 1]) {
			removeSand = false;
			break;
		}
	}

	if (removeSand == true)
	{
		for (size_t i = maxindex + 1; i < nums.size(); i++)
		{
			v[i]->setSand(0);
		}
	}
	else
	{
		for (size_t i = maxindex + 1; i < nums.size() - 1; i++)
		{
			if (nums[i] < nums[i + 1])
			{
				for (size_t j = maxindex + 1; j < i + 1; ++j)
				{
					if (nums[j] < nums[i + 1])
					{
						v[j]->setSand(v[i + 1]->getBar() - v[j]->getBar());
					}
				}
			}
			else
				v[i]->setSand(0);
		}
	}

	for (auto k : v)
	{
		totalSand += k->getSand();
	}
	return totalSand;


}

void drawGraphVertically(const vector<Graph*>& v)
{
	for (auto graph : v)
	{
		//print bar values
		cout << setw(3) << graph->getBar() << " | ";
		//print actual bars
		for (int i = 0; i < graph->getBar(); i++)
		{
			cout << "- ";
		}
		//print actual sand dots
		for (int i = 0; i < graph->getSand(); i++)
		{
			cout << ". ";
		}
		//print sand values
		if (graph->getSand() == 0)
			cout << " ";
		else
			cout << graph->getSand() << " ";
		cout << endl;
	}
}

void drawGraphHorizontally(const vector<Graph*>& v)
{
	int max_value = 0;
	//get tallest column
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i]->getBar() > max_value)
		{
			max_value = v[i]->getBar();
		}
	}
	//print sand values
	for (auto i : v)
	{
		if (i->getSand() == 0)
		{
			cout << "   ";
		}
		else
			cout << " " << i->getSand() << " ";
	}
	cout << endl;

	// Print the columns
	for (int current = max_value; current > 0; current--)
	{
		for (auto val : v)
		{
			if (current <= val->getBar() || (val->getBar() + val->getSand() == current))
			{
				if (current <= val->getBar())
					std::cout << " | ";
				else
				{
					cout << " . ";
				}
			}
			else
			{
				if ((val->getBar() + val->getSand() > current))
					cout << " . ";
				else
				{
					cout << "   ";
				}
			}
		}
		cout << endl;
	}
	//print bar values
	for (unsigned int i = 0; i < v.size() * 3; i++)
		cout << "-";
	cout << endl;
	for (auto i : v)
	{
		cout << " " << i->getBar() << " ";
	}
}

bool isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

int main(int argc, char* argv[])
{
	srand(time(0));
	vector<Graph*> v;
	vector<int> numbers;
	string input;

	string repeat = "y";
	while (repeat[0] == 'y' || repeat[0] == 'Y')
	{
		input = "";
		numbers.clear();
		//prompt user for input
		while (numbers.size() == 0)
			promptUser(numbers);

		int sandAmount = calculateSand(v, numbers);
		cout << "Answer: This bar graph can hold a total of " << sandAmount << " units of sand" << endl;
		//prompt choose graph orientation
		while (input != "h" && input != "horizontally" && input != "v" && input != "vertically")
		{
			cout << "Would you like to plot horizontally or vertically?" << endl;
			cin >> input;
		}

		cout << "ASCII art bar graph plot showing sand on top of the graph: " << endl;

		if (input == "v" || input == "vertically")
			drawGraphVertically(v);
		else
			drawGraphHorizontally(v);

		cout << endl << "Total " << sandAmount << " units of sand." << endl;

		cout << "Please enter a filename to save bar graph to text file or enter 'n' to not save: ";
		cin >> repeat;
		while (repeat[0] != 'n' && repeat.find(".txt") == string::npos)
		{
			cout << "Please enter a filename to save bar graph to text file or enter 'n' to not save: ";
			cin >> repeat;

			//flush standard input
			cin.clear();
			fflush(stdin);
		}


		if (repeat.find(".txt") != string::npos)
		{
			std::ofstream ofs{ repeat };
			auto cout_buff = std::cout.rdbuf();
			std::cout.rdbuf(ofs.rdbuf());

			if (input == "v" || input == "vertically")
				drawGraphVertically(v);
			else
				drawGraphHorizontally(v);

			std::cout.rdbuf(cout_buff);
			cout << "The bar graph with sand has been saved as " << repeat << endl;

		}

		cout << "Please enter 'Y' or 'y' to run again:  ";
		cin >> repeat;

		//flush standard input
		cin.clear();
		fflush(stdin);
	}
	cout << "Thank you for using the bar graph sand program. " << endl << "Goodbye!" << endl;
	return 0;
}

