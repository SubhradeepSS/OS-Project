#include <bits/stdc++.h>
using namespace std;

class Process{
public:
	int id;   //Process id of the given process
	vector<int> segments; // Storing the memory of each segment of process
	int arrival_time; // arrival time of the process
	int lifetime;  // lifetime of the process
};

class mem_unit{
public:
	int size;    //size of the particular memory unit
	bool is_empty; // flag to tell if process is occupied or hole is present
	int start_location; // starting location of the memory unit >= 0 <= SIZE
	int end_location; // ending location <= SIZE
};

class Memory{
public:
	int SIZE; //Taken as input from user in the begining
	int fit_algo; // 1-first, 2-best, 3-worst ,also taken input in the beginning
	list<mem_unit> units; // SIZE = sum of all mem_units.size
};

queue<Process> Queue;
vector<Process> input_array ; //To store all the processes in Input 

