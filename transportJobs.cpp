#include"comfunc.h"
using namespace std;

vector<FuzzyTime> transportJobs(const vector<pair<FuzzyTime, int>>& jobCompletionTimes,
    int numJobs,
    Truck& truck1) {
    vector<FuzzyTime> jobArrivalTimes(numJobs); 
    vector<int> transportedJobs; 

    FuzzyTime truckEndTime = { 0, 0, 0 };

    int numBatches = (numJobs + truck1.capacity - 1) / truck1.capacity;

    for (int i = 0; i < numBatches; ++i) {
    
        FuzzyTime transportStartTime;
        int startIdx = i * truck1.capacity;
        int endIdx = min((i + 1) * truck1.capacity, (int)jobCompletionTimes.size()) - 1;

        if (i == 0) {
            transportStartTime = jobCompletionTimes[endIdx].first;
        }
        else {
            transportStartTime = maxFuzzyTime(truckEndTime, jobCompletionTimes[endIdx].first);
        }

        truckEndTime = addFuzzyTime(transportStartTime, truck1.transportTime);

        for (int j = startIdx; j <= endIdx && j < jobCompletionTimes.size(); ++j) {
            int jobID = jobCompletionTimes[j].second;
            jobArrivalTimes[jobID] = addFuzzyTime(transportStartTime, truck1.transportTime);
            transportedJobs.push_back(jobID);
            truck1.addToTransportQueue(jobID);

        truck1.clearQueue(); 
        truckEndTime = addFuzzyTime(truckEndTime, truck1.transportTime);
    }
    return jobArrivalTimes;
}
