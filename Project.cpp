#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct Task
{
    char id;
    int duration;
    vector<char> dependencies;
};

// Function to calculate the earliest start time for each task
void calculateEarliestStartFinishTimes(vector<Task> &tasks, map<char, int> &earliestStartTimes, map<char, int> &earliestFinishTimes, map<char, bool> &inqueue, map<char, bool> &dependentOn)
{
    queue<Task> waiting;
    for (auto &task : tasks)
    {
        int earliestStartTime = 0;
        bool setVals = true;
        for (auto &dependency : task.dependencies)
        {
            dependentOn[dependency] = true;
            if (earliestStartTimes[dependency] == earliestFinishTimes[dependency])
            {
                waiting.push(task);
                setVals = false;
                break;
            }
            earliestStartTime = max(earliestStartTime, earliestFinishTimes[dependency]);
        }
        if (setVals)
        {
            earliestStartTimes[task.id] = earliestStartTime;
            earliestFinishTimes[task.id] = earliestStartTime + task.duration;
        }
    }

    while (!waiting.empty())
    {
        Task task = waiting.front();
        waiting.pop();
        int earliestStartTime = 0;
        bool setVals = true;
        for (auto &dependency : task.dependencies)
        {
            if (earliestStartTimes[dependency] == earliestFinishTimes[dependency])
            {
                if (!inqueue[task.id])
                    waiting.push(task);
                inqueue[task.id] = 1;
                setVals = false;
                break;
            }
            earliestStartTime = max(earliestStartTime, earliestFinishTimes[dependency]);
        }
        if (setVals)
        {
            earliestStartTimes[task.id] = earliestStartTime;
            earliestFinishTimes[task.id] = earliestStartTime + task.duration;
        }
    }
}

// Function to calculate the latest finish time for each task
void calculateLatestStartFinishTimes(vector<Task> &tasks, map<char, int> &earliestFinishTimes, map<char, int> &latestStartTimes, map<char, int> &latestFinishTimes, int &TotalTime, map<char, Task> &charToTask, map<char, bool> &dependentOn, char &maxFinishTask)
{
    int maxFinishTime = 0;
    for (auto &task : tasks)
    {
        if (earliestFinishTimes[task.id] > maxFinishTime)
        {
            maxFinishTime = earliestFinishTimes[task.id];
            maxFinishTask = task.id;
        }
    }
    for (auto &task : dependentOn)
    {
        if (!task.second)
        {
            latestFinishTimes[task.first] = maxFinishTime;
            latestStartTimes[task.first] = maxFinishTime - charToTask[task.first].duration;
        }
    }

    TotalTime = maxFinishTime;

    queue<char> reverse({maxFinishTask});

    while (!reverse.empty())
    {
        for (auto &dependency : charToTask[reverse.front()].dependencies)
        {
            reverse.push(dependency);
            if (latestStartTimes[reverse.front()] < latestFinishTimes[dependency] || latestFinishTimes[dependency] == 0)
            {
                latestFinishTimes[dependency] = latestStartTimes[reverse.front()];
                latestStartTimes[dependency] = latestFinishTimes[dependency] - charToTask[dependency].duration;
            }
        }
        reverse.pop();
    }
}

// Function to calculate the critical path
void calculateCriticalPath(char &maxFinishTask, map<char, int> &earliestStartTimes, map<char, int> &latestStartTimes, map<char, Task> &charToTask)
{
    map<char, bool> addedToQueue;
    vector<string> paths({{maxFinishTask}});
    queue<char> reverse({maxFinishTask});

    while (!reverse.empty())
    {
        string tmp = "";
        for (auto task : charToTask[reverse.front()].dependencies)
        {
            if (earliestStartTimes[task] == latestStartTimes[task])
            {
                if (!addedToQueue[task])
                {
                    addedToQueue[task] = true;
                    tmp.push_back(task);
                    reverse.push(task);
                }
            }
        }
        reverse.pop();
        if (tmp != "")
            paths.push_back(tmp);
    }

    cout << "Critical Path(s) : \n\n";

    int counter = 1;

    while (true)
    {
        cout << '[' << counter++ << "] ";
        bool Finished = true;
        for (int i = paths.size() - 1; i >= 0; i--)
        {
            cout << paths[i][0] << " ";
            if (paths[i].size() > 1)
            {
                paths[i].erase(paths[i].begin());
                Finished = false;
            }
        }
        cout << '\n';

        if (Finished)
            break;
    }
}

int main()
{
    // Define tasks and their dependencies
    vector<Task> tasks = {
        // Test 1
         {/*'A', 6, {}},
         {'B', 4, {'A'}},
         {'C', 4, {'A'}},
         {'D', 7, {'B', 'C'}},
         {'E', 6, {'C'}},
         {'F', 2, {'D', 'E'}},*/

        // Test 2
         {'H', 2, {'E', 'G'}},
         {'D', 3, {'B'}},
         {'E', 3, {'D', 'F'}},
         {'A', 7, {}},
         {'F', 2, {'B'}},
         {'B', 3, {}},
         {'G', 3, {'C'}},
         {'C', 6, {'A'}},

        // Test 3
        // {'A', 2, {}},
        // {'B', 2, {}},
        // {'C', 4, {}},
        // {'D', 8, {}},
        // {'E', 3, {'A', 'F'}},
        // {'F', 4, {'B'}},
        // {'G', 3, {'C', 'D', 'E'}},
        // {'H', 2, {'D', 'G'}},
        // {'I', 7, {'E'}},
        // {'J', 6, {'G'}},
    };

    // Initialize maps to store earliest start times and latest finish times
    map<char, int> earliestStartTimes;
    map<char, int> earliestFinishTimes;
    map<char, int> latestStartTimes;
    map<char, int> latestFinishTimes;
    map<char, Task> charToTask;
    map<char, bool> inqueue;
    map<char, bool> dependentOn;

    char maxFinishTask;

    int TotalTime = 0;

    for (auto &task : tasks)
    {
        charToTask[task.id] = task;
    }

    for (auto &task : tasks)
    {
        dependentOn[task.id] = 0;
    }

    // handle tasks with no dependencies
    for (auto &task : tasks)
    {
        if (task.dependencies.empty())
        {
            earliestStartTimes[task.id] = 0;
            earliestFinishTimes[task.id] = task.duration;
        }
    }

    // Calculate earliest start finish times
    calculateEarliestStartFinishTimes(tasks, earliestStartTimes, earliestFinishTimes, inqueue, dependentOn);

    // Calculate latest start finish times
    calculateLatestStartFinishTimes(tasks, earliestFinishTimes, latestStartTimes, latestFinishTimes, TotalTime, charToTask, dependentOn, maxFinishTask);

    calculateCriticalPath(maxFinishTask, earliestStartTimes, latestStartTimes, charToTask);

    cout << "\nTotal Time: " << TotalTime << endl;

    return 0;
}