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

void printMem(vector<mem_unit> units, int t)
{
    //list<mem_unit>::iterator i;
    int i, j;
    cout << "---------Memory STATUS---------------- at Time t = " << t << endl;
    for (i = 0; i < units.size(); i++)
    {
        mem_unit temp = units[i];
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

int checkPossible(Process p, vector<mem_unit> m)
{
    //vector<mem_unit> m;
    //list<mem_unit>::iterator i;
    vector<int> seg = p.segments;
    int n = seg.size();
    int status[n] = {};
    int usize = m.size();
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        int s = seg[i];
        int min = 9999999;
        int flg = 0;
        for (j = 0; j < usize; j++)
        {
            if (m[j].is_empty == 1)
            {
                if (m[j].size >= s)
                {
                    if (min > m[j].size)
                    {
                        min = m[j].size;
                        k = j;
                        flg = 1;
                    }
                }
            }
        }
        if (flg == 1)
        {
            vector<mem_unit> q;
            status[i] = 1;
            for (int l = k + 1; l < usize; l++)
                q.push_back(m[l]);
            mem_unit tmp, tmp1;
            tmp1 = m[k];
            tmp.p = p;
            tmp.psegment = i;
            tmp.size = s;
            tmp1.size -= s;
            tmp.is_empty = 0;
            tmp1.is_empty = 1;
            tmp.start_location = tmp1.start_location;
            tmp.end_location = tmp.start_location + s - 1;
            tmp1.start_location = tmp.end_location + 1;
            if (tmp1.size > 0)
            {
                m[k] = tmp;
                m[k + 1] = tmp1;
                for (int l = 0; l < q.size(); l++)
                {
                    m[k + 2 + l] = q[l];
                }
            }
            else
            {
                m[k] = tmp;
            }
            q.clear();
        }
    }
    int flag = 1;
    for (i = 0; i < n; i++)
        if (status[i] == 0)
        {
            flag = 0;
            break;
        }
    return flag;
}

void addProcess(Process p, vector<mem_unit> m, int t)
{
    //list<mem_unit> m(mem_list);
    //vector<mem_unit> m;
    //list<mem_unit>::iterator i;
    vector<int> seg = p.segments;
    int n = seg.size();
    int status[n] = {};
    int usize = m.size();
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        int s = seg[i];
        int min = 9999999;
        int flg = 0;
        for (j = 0; j < usize; j++)
        {
            if (m[j].is_empty == 1)
            {
                if (m[j].size >= s)
                {
                    if (min > m[j].size)
                    {
                        min = m[j].size;
                        k = j;
                        flg = 1;
                    }
                }
            }
        }
        if (flg == 1)
        {
            vector<mem_unit> q;
            status[i] = 1;
            for (int l = k + 1; l < usize; l++)
                q[l - k - 1] = m[l];
            mem_unit tmp, tmp1;
            tmp1 = m[k];
            tmp.p = p;
            tmp.psegment = i;
            tmp.size = s;
            tmp1.size -= s;
            tmp.is_empty = 0;
            tmp1.is_empty = 1;
            tmp.p.entry_time = t;
            tmp.start_location = tmp1.start_location;
            tmp.end_location = tmp.start_location + s - 1;
            tmp1.start_location = tmp.end_location + 1;
            if (tmp1.size > 0)
            {
                m[k] = tmp;
                m[k + 1] = tmp1;
                for (int l = 0; l < q.size(); l++)
                {
                    m[k + 2 + l] = q[l];
                }
            }
            else
            {
                m[k] = tmp;
            }
            q.clear();
        }
    }
    printMem(m, t);

    //return m;
}

vector<mem_unit> checkifover(vector<mem_unit> units, int t)
{
    int i, j, k;
    for (i = 0; i < units.size(); i++)
    {
        Process p;
        p = units[i].p;
        if (units[i].is_empty == 0)
        {
            if (p.entry_time + p.lifetime == t)
            {
                units[i].is_empty = 1;
                for (j = i + 1; j < units.size(); j++)
                {
                    if (units[j].is_empty == 0)
                    {
                        if (units[j].p.id == p.id)
                        {
                            units[j].is_empty = 1;
                        }
                    }
                }
                cout << "Process " << p.id << " is completed and removed at time t = " << t << endl;
                printMem(units, t);
            }
        }
    }

    return units;
}

vector<mem_unit> removeHoles(vector<mem_unit> units, int t)
{
    int i, j, k;
    int sz = units.size();
    vector<mem_unit>::iterator it;
    for (i = 0; i < units.size(); ++i)
    {
        //i--;
        it = units.begin();
        for (j = i + 1; j < units.size(); j++)
        {
            it = units.begin();
            if ((units[j].is_empty == 1) && (units[j - 1].is_empty == 1))
            {
                vector<mem_unit> q;
                units[j - 1].size += units[j].size;
                units[j - 1].end_location = units[j].end_location;
                advance(it, j);
                units.erase(it);
                it = units.begin();
            }
        }
    }
    // for (i = units.begin(); (++i) != units.end(); ++i)
    // {
    //     i--;
    //     if (units.begin() != units.end())
    //     {
    //         j = i;
    //         ++j;
    //         if (((*i).is_empty == 1) && ((*j).is_empty == 1))
    //         {
    //             mem_unit t1, temp = (*i);
    //             t1 = (*j);
    //             (*i).end_location = (*j).end_location;
    //             (*i).size += t1.size;
    //             j = units.erase(j);
    //             i--;
    //             //printMem(units, t);
    //         }
    //     }
    // }
    // for (i = units.begin(); (++i) != units.end(); ++i)
    // {
    //     i--;
    //     if (units.begin() != units.end())
    //     {
    //         j = i;
    //         ++j;
    //         if (((*i).is_empty == 1) && ((*j).is_empty == 1))
    //         {
    //             mem_unit t1, temp = (*i);
    //             t1 = (*j);
    //             (*i).end_location = (*j).end_location;
    //             (*i).size += t1.size;
    //             j = units.erase(j);
    //             i--;
    //             //printMem(units, t);
    //         }
    //     }
    // }
    // for (i = units.begin(); (++i) != units.end(); ++i)
    // {
    //     i--;
    //     if (units.begin() != units.end())
    //     {
    //         j = i;
    //         ++j;
    //         if (((*i).is_empty == 1) && ((*j).is_empty == 1))
    //         {
    //             mem_unit t1, temp = (*i);
    //             t1 = (*j);
    //             (*i).end_location = (*j).end_location;
    //             (*i).size += t1.size;
    //             j = units.erase(j);
    //             i--;
    //             printMem(units, t);
    //         }
    //     }
    // }
    if (sz > units.size())
        printMem(units, t);
    return units;
}
int checkP(vector<mem_unit> units)
{
    vector<mem_unit>::iterator i, j;
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
void firstfit(vector<Process> input_array, int memory_size)
{
    list<Process> Queue;
    int i, j, k; //Helper
    int number_p = input_array.size();
    Memory M;
    vector<mem_unit> units; // SIZE = sum of all mem_units.size
    M.SIZE = memory_size;
    M.fit_algo = 1;
    // Make a initial memory unit/hole with whole size
    mem_unit initial;
    initial.size = memory_size;
    initial.is_empty = 1;
    initial.start_location = 0;
    initial.end_location = memory_size - 1;
    units.push_back(initial);

    int t = 0, checkp = 1, ipi = 0, sz = input_array.size();
    while ((ipi != sz - 1) || (Queue.size() != 0) || (checkp))
    {

        Process a, b, c, f;

        if (!input_array.empty())
        {

            f = input_array[ipi];
            while (f.arrival_time == t)
            {
                Queue.push_back(f);
                printQ(t, Queue);
                if (ipi < sz - 1)
                {
                    ipi++;
                    f = input_array[ipi];
                }
                else
                {
                    break;
                }

                //input_array.erase(input_array.begin());
                //if (!input_array.empty())
                //    f = input_array.front();
                //else
                //    f.arrival_time = 999999;
            }
        }
        vector<mem_unit> temp;
        temp = removeHoles(units, t);
        units = temp;
        checkp = checkP(units);
        list<Process>::iterator it = Queue.begin();
        while (it != Queue.end())
        {
            a = (*it);

            int b;
            b = checkPossible(a, units);

            if (b == 1)
            {
                it = Queue.erase(it);
                cout << "Process " << a.id << " added at time " << t << endl;
                vector<mem_unit> temp;
                addProcess(a, units, t);
                //units = temp;
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
    vector<Process> input_array;
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
    for (i = 0; i < n_processes; i++)
    {
        for (j = i + 1; j < n_processes; j++)
        {
            if (input_array[i].arrival_time > input_array[j].arrival_time)
            {
                swap(input_array[i], input_array[j]);
            }
        }
    }

    //list<Process>::iterator it;
    //input_array.sort(PlayerComparator());
    firstfit(input_array, mem_size);
}