#include <bits/stdc++.h>
using namespace std;
template <class Compare>
void sort(Compare comparator);
class Process
{
public:
    int id;               //Process id of the given process
    vector<int> segments; // Storing the memory of each segment of process
    int arrival_time;     // arrival time of the process
    int lifetime;
    int entry_time;
    // lifetime of the process
};
struct PlayerComparator
{
    // Compare 2 Player objects using name
    bool operator()(const Process &p1, const Process &p2)
    {

        return p2.arrival_time > p1.arrival_time;
    }
};
class mem_unit
{
public:
    Process p;
    int psegment;
    int size;           //size of the particular memory unit
    bool is_empty;      // flag to tell if process is occupied or hole is present
    int start_location; // starting location of the memory unit >= 0 <= SIZE
    int end_location;   // ending location <= SIZE
};

class Memory
{
public:
    int SIZE;     //Taken as input from user in the begining
    int fit_algo; // 1-first, 2-best, 3-worst ,also taken input in the beginning
};

void printu(list<mem_unit> units)
{
    cout << "Printing units\n";
    list<mem_unit>::iterator i, j;
    for (i = units.begin(); i != units.end(); ++i)
    {
        cout << (*i).start_location << " " << (*i).size << endl;
    }
}
void printQ(int t, list<Process> q)
{
    if (!q.empty())
    {
        cout << "---------------Queue Status-----------" << endl;
        cout << "At time " << t << " these are the processes present in Queue" << endl;
        // cout << "Done";
        list<Process>::iterator i;
        // cout << "Done";
        for (i = q.begin(); i != q.end(); i++)
        {
            //cout << "Done";
            Process temp = (*i);
            cout << "Process " << temp.id << " ";
            cout << "Arrival Time " << temp.arrival_time << " " << endl;
        }
    }
    else
    {
        cout << "Empty\n";
    }
    cout << endl;
}

int checkPossible(Process p, list<mem_unit> mem_list)
{
    list<mem_unit> m(mem_list);
    list<mem_unit>::iterator i;
    vector<int> seg = p.segments;

    sort(seg.begin(), seg.end());

    int status[seg.size()] = {};
    for (int j = 0; j < seg.size(); j++)
        status[j] = 0;
    for (int j = 0; j < seg.size(); j++)
    {
        int s; //size of segment i of process p;
        s = seg[j];
        list<mem_unit>::iterator ans_it = m.end();
        for (i = m.begin(); i != m.end(); i++)
        {
            mem_unit temp = (*i);
            if (temp.is_empty == 1)
            {
                if (temp.size >= s)
                {
                    ans_it = i;
                    break;
                }
            }
        }
        
        if(ans_it != m.end()){

            for (i = ans_it; i != m.end(); i++)
            {
                mem_unit temp = (*i);
                if (temp.is_empty == 1)
                {
                    if (temp.size >= s && temp.size < (*ans_it).size)
                    {
                        ans_it = i;
                    }
                }
            }

            status[j] = 1;
            mem_unit t1,temp;
            temp = *ans_it;
            t1.p = p;
            //t1.p.entry_time = t;
            t1.is_empty = 0;
            t1.size = s;
            (*ans_it).size -= s;

            t1.psegment = j;
            t1.start_location = temp.start_location;
            t1.end_location = t1.start_location + s - 1;
            (*ans_it).start_location = t1.end_location + 1;
            if ((*ans_it).size == 0)
                (*ans_it) = t1;
            else
                m.insert(ans_it, t1);
        }
    }
    int flag = 1;
    for (int j = 0; j < seg.size(); j++)
    {
        if (status[j] == 0)
            flag = 0;
        break;
    }
    return flag;
}

void printMem(list<mem_unit> units, int t)
{
    list<mem_unit>::iterator i;
    cout << "---------Memory STATUS---------------- at Time t = " << t << endl;
    for (i = units.begin(); i != units.end(); i++)
    {
        mem_unit temp = (*i);
        if (temp.is_empty == 1)
        {
            cout << "Hole Present :-"
                 << " Size :-" << temp.size
                 << " Location :-" << temp.start_location << "-" << temp.end_location << endl;
        }
        else
        {
            cout << "Process :-" << temp.p.id << " "
                 << "Segment :-" << temp.psegment << " Size :-" << temp.size
                 << " Location :-" << temp.start_location << "-" << temp.end_location << endl;
        }
        cout << endl;
    }
}

list<mem_unit> addProcess(Process p, list<mem_unit> m, int t)
{
    //list<mem_unit> m(mem_list);
    list<mem_unit>::iterator i;
    vector<int> seg = p.segments;
    sort(seg.begin(), seg.end());

    for (int j = 0; j < seg.size(); j++)
    {
        int s; //size of segment i of process p;
        s = seg[j];
        list<mem_unit>::iterator ans_it = m.end();
        for (i = m.begin(); i != m.end(); ++i)
        {
            mem_unit temp = (*i);
            if (temp.is_empty == 1)
            {
                if (temp.size >= s)
                {
                    ans_it = i;
                    break;
                }
            }
        }
        if(ans_it != m.end()){
            for (i = ans_it; i != m.end(); ++i)
            {
                mem_unit temp = (*i);
                if (temp.is_empty == 1)
                {
                    if (temp.size >= s && temp.size < (*ans_it).size)
                    {
                        ans_it = i;
                    }
                }
            }
            mem_unit t1,temp;
            temp = *ans_it;
            t1.p = p;
            t1.p.entry_time = t;
            t1.is_empty = 0;
            t1.size = s;
            (*ans_it).size -= s;

            t1.psegment = j;
            t1.start_location = temp.start_location;
            t1.end_location = t1.start_location + s - 1;
            (*ans_it).start_location = t1.end_location + 1;
            if ((*ans_it).size == 0)
                (*ans_it) = t1;
            else
                m.insert(ans_it, t1);
        }
    }
    printMem(m, t);

    return m;
}

list<mem_unit> checkifover(list<mem_unit> units, int t)
{
    list<mem_unit>::iterator i, j;
    if (units.size() > 1)
    {
        for (i = units.begin(); i != units.end(); ++i)
        {
            Process a;
            a = (*i).p;
            if ((*i).is_empty == 0)
            {
                if (a.entry_time + a.lifetime == t)
                {
                    (*i).is_empty = 1;
                    for (j = i; j != units.end(); j++)
                    {
                        if ((*j).p.id == a.id)
                        {
                            (*j).is_empty = 1;
                        }
                    }
                    cout << "Process " << a.id << " is completed and removed at time t = " << t << endl;
                    printMem(units, t);
                }
            }
        }
    }
    return units;
}

list<mem_unit> removeHoles(list<mem_unit> units, int t)
{
    list<mem_unit>::iterator i, j;

    for (i = units.begin(); (++i) != units.end(); ++i)
    {
        i--;
        if (units.begin() != units.end())
        {
            j = i;
            ++j;
            if (((*i).is_empty == 1) && ((*j).is_empty == 1))
            {
                mem_unit t1, temp = (*i);
                t1 = (*j);
                (*i).end_location = (*j).end_location;
                (*i).size += t1.size;
                j = units.erase(j);
                i--;
                //printMem(units, t);
            }
        }
    }
    for (i = units.begin(); (++i) != units.end(); ++i)
    {
        i--;
        if (units.begin() != units.end())
        {
            j = i;
            ++j;
            if (((*i).is_empty == 1) && ((*j).is_empty == 1))
            {
                mem_unit t1, temp = (*i);
                t1 = (*j);
                (*i).end_location = (*j).end_location;
                (*i).size += t1.size;
                j = units.erase(j);
                i--;
                //printMem(units, t);
            }
        }
    }
    for (i = units.begin(); (++i) != units.end(); ++i)
    {
        i--;
        if (units.begin() != units.end())
        {
            j = i;
            ++j;
            if (((*i).is_empty == 1) && ((*j).is_empty == 1))
            {
                mem_unit t1, temp = (*i);
                t1 = (*j);
                (*i).end_location = (*j).end_location;
                (*i).size += t1.size;
                j = units.erase(j);
                i--;
                //printMem(units, t);
            }
        }
    }
    for (i = units.begin(); (++i) != units.end(); ++i)
    {
        i--;
        if (units.begin() != units.end())
        {
            j = i;
            ++j;
            if (((*i).is_empty == 1) && ((*j).is_empty == 1))
            {
                mem_unit t1, temp = (*i);
                t1 = (*j);
                (*i).end_location = (*j).end_location;
                (*i).size += t1.size;
                j = units.erase(j);
                i--;
                printMem(units, t);
            }
        }
    }

    return units;
}
int checkP(list<mem_unit> units)
{
    list<mem_unit>::iterator i, j;
    int flag = 0;
    for (i = units.begin(); i != units.end(); ++i)
    {
        if ((*i).is_empty == 0)
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

//To store all the processes in Input
void firstfit(list<Process> input_array, int memory_size)
{
    list<Process> Queue;
    int i, j, k; //Helper
    int number_p = input_array.size();
    Memory M;
    list<mem_unit> units; // SIZE = sum of all mem_units.size
    M.SIZE = memory_size;
    M.fit_algo = 1;
    // Make a initial memory unit/hole with whole size
    mem_unit initial;
    initial.size = memory_size;
    initial.is_empty = 1;
    initial.start_location = 0;
    initial.end_location = memory_size - 1;
    units.push_back(initial);

    int t = 0, checkp = 1;
    while ((input_array.size() != 0) || (Queue.size() != 0) || (checkp))
    {

        Process a, b, c, f;

        if (!input_array.empty())
        {
            f = input_array.front();
            while (f.arrival_time == t)
            {
                Queue.push_back(f);
                printQ(t, Queue);

                input_array.pop_front();
                if (!input_array.empty())
                    f = input_array.front();
                else
                    f.arrival_time = 999999;
            }
        }
        list<mem_unit> temp;
        temp = removeHoles(units, t);
        units = temp;
        checkp = checkP(units);
        list<Process>::iterator it = Queue.begin();
        while (it != Queue.end())
        {
            a = (*it);

            int b = checkPossible(a, units);

            if (b == 1)
            {
                it = Queue.erase(it);
                cout << "Process " << a.id << " added at time " << t << endl;
                list<mem_unit> temp;
                temp = addProcess(a, units, t);
                units = temp;
            }
            else
            {
                ++it;
            }
        }

        temp = checkifover(units, t);
        units = temp;

        temp = removeHoles(units, t);
        units = temp;
        checkp = checkP(units);

        t++;
    }
}

int main()
{
    list<Process> input_array;
    int type_of_fit; //Type of algorithm to run
    cout << "Press 1 for first fit,2 for best fir , and 3 for worst fit ";
    cin >> type_of_fit;
    while (type_of_fit < 1 || type_of_fit > 3)
    {
        cout << "Enter a valid number between 1-3 ";
        cin >> type_of_fit;
    }
    cout << "Enter the number of processes ";
    int n_processes; //Total Processes
    int mem_size;
    cin >> n_processes;
    cout << "Enter Memory Size ";
    cin >> mem_size;
    int i, j, k; //Helper variables
    cout << "Enter all processes attributes \n";
    // run a for loop to get all the attributes of the input
    for (i = 0; i < n_processes; i++)
    {
        int p_id, p_arrival_time, p_lifetime, p_segments;
        Process p;
        cin >> p_id;                         //Get id
        cin >> p_arrival_time >> p_lifetime; //Get arrival time and lifetime
        cin >> p_segments;
        for (j = 0; j < p_segments; j++)
        {
            int seg_size;
            cin >> seg_size;
            p.segments.push_back(seg_size);
        } //Get number of segments
        p.id = p_id;
        p.arrival_time = p_arrival_time;
        p.lifetime = p_lifetime;
        //loop over the number of segments and take their inputs

        input_array.push_back(p);
    }

    list<Process>::iterator it;
    input_array.sort(PlayerComparator());

    firstfit(input_array, mem_size);
}
