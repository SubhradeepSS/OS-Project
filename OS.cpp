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

int main()
{
	int type_of_fit; //Type of algorithm to run
	cout<<"Press 1 for first fit,2 for best fir , and 3 for worst fit";
	cin>>type_of_fit;
	while(type_of_fit<1||type_of_fit>3)
	{
		cout<<"Enter a valid number between 1-3";
		cin>>type_of_fit;
	}
	cout<<"Enter the number of processes";
	int n_processes; //Total Processes
	int mem_size;
	cin>>n_processes;
	cout<<"Enter Memory Size";
	cin>>mem_size;
	int i,j,k ;   //Helper variables
	cout<<"Enter all process attributes";
	// run a for loop to get all the attributes of the input
	for(i=0;i<n_processes;i++)
	{
		int p_id,p_arrival_time,p_lifetime,p_segments;
		Process p;
		cin >> p_id; //Get id
		cin >> p_arrival_time >> p_lifetime ; //Get arrival time and lifetime
		cin >> p_segments; //Get number of segments
		p.id = p_id;
		p.arrival_time = p_arrival_time;
		p.lifetime = p_lifetime;
		//loop over the number of segments and take their inputs
		for(j=0;j<p_segments;j++)
		{
			int seg_size;
			cin>>seg_size;
			p.segments.push_back(seg_size);
		}
		input_array.push_back(p);
	}
}
