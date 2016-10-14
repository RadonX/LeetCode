#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Job {
public:
    string name;
    int ntask, taskTime, canBegin, priority;
    int cost;
};

class Worker {
public:
    string name;
    int timestamp, preJobId;
    Worker(): timestamp(0), preJobId(-1) {}
};


bool compareCost(const class Job *a , const class Job *b) {
    return (a->priority * a->taskTime + b->priority * (a->taskTime + b->taskTime)
            < b->priority * b->taskTime + a->priority * (a->taskTime + b->taskTime) ); // a->cost < b->cost
}
struct CompareTime { // min heap, with smallest begin time
    bool operator() (const class Job *a , const class Job *b) const {
        return (a->canBegin > b->canBegin);
    }
};
struct CompareCost { // min heap, with min cost
    bool operator() (const class Job *a , const class Job *b) const {
        return (a->cost > b->cost);
    }
};
struct CompareTimestamp { // min heap, with smallest timestamp
    bool operator() (const class Worker *a , const class Worker *b) const {
        return (a->timestamp >= b->timestamp);
    }
};

vector<Job*> jobs;
priority_queue<Job*, vector<Job*>, CompareCost> costHeap;
priority_queue<Worker*, vector<Worker*>, CompareTimestamp> workerHeap;

void sortJobs() {
    sort(jobs.begin(), jobs.end(), compareCost);
    int cost = 0;
    for (auto job: jobs) {
        job->cost = ++cost;
    }
}

inline void scheduleAJob() {
    // get the worker
    Worker *worker = workerHeap.top(); workerHeap.pop();
    // get the job
    Job *job = costHeap.top();

    if (worker->preJobId != job->cost) {
        worker->preJobId = job->cost; // unique
        worker->timestamp = max(worker->timestamp, job->canBegin);
        cout << worker->timestamp << ' ' << worker->name << ' ' << job->name << endl;
    }
    worker->timestamp += job->taskTime;
    workerHeap.push(worker);
    job->ntask -= 1;
    if (job->ntask == 0) costHeap.pop();
}

void schedule() {
    priority_queue<Job*, vector<Job*>, CompareTime> timeHeap(jobs.begin(), jobs.end());
    int timestamp;
    while (true) {
        // get the timestamp of earliest available worker
        timestamp = workerHeap.top()->timestamp;
        while (!timeHeap.empty() && timestamp >= timeHeap.top()->canBegin) {
            costHeap.push(timeHeap.top()); timeHeap.pop();
        }
        if (costHeap.empty()) {
            // no job can be started instantly
            if (!timeHeap.empty()) {
                costHeap.push(timeHeap.top()); timeHeap.pop();
            } else break; // all jobs done
        }

        // all jobs in costHeap are earliest available or <= timestamp jobs
        while (timestamp == workerHeap.top()->timestamp)
            scheduleAJob();
    }
}

int main() {
    Job *job;
    Worker *worker;
    string category;
    while (cin) {
        category = "-"; // some cin problem
        cin >> category;
        if (category[0] == 'j') {
            job = new Job();
            cin >> job->name >> job->ntask >> job->taskTime >> job->canBegin >> job->priority;
            jobs.push_back(job);
        } else if (category[0] == 'w') {
            worker = new Worker();
            cin >> worker->name;
            workerHeap.push(worker);
        }
    }

    if (workerHeap.size() == 0) return 0;
    sortJobs();
    schedule();

    return 0;
}
