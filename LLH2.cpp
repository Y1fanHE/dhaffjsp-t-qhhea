#include"comfunc.h"
using namespace std;

void LLH2(Individual& individual, vector<Factory>& factories, vector<Job>& jobs,
    vector<Product>& products, int numMachines, mt19937& gen, int numJobs, int numFactories) {
    int factoryID = individual.criticalFactoryID;

    if (factoryID == -1 || individual.factorySchedule[factoryID].size() < 2) {
        return;
    }

    vector<int>& schedule = individual.factorySchedule[factoryID];
    int size = schedule.size();

    int mid = size / 2;

    uniform_int_distribution<int> choice(0, 1);
    bool reverseFirstHalf = choice(gen);

    if (reverseFirstHalf) {
        reverse(schedule.begin(), schedule.begin() + mid);
    }
    else {
        reverse(schedule.begin() + mid, schedule.end());
    }

    vector<FuzzyTime> completionTimes(jobs.size(), { 0, 0, 0 });
    individual.factorySchedule[factoryID] = schedule;

    FuzzyTime newMakespan = calculateMakespan(factories, individual.factorySchedule, jobs, completionTimes, products, numMachines, numJobs, numFactories);

    int newCriticalFactoryID = -1;
    calculateCriticalFactory(factories, newCriticalFactoryID);

    individual.makespan = newMakespan;
    individual.criticalFactoryID = newCriticalFactoryID;

  

    int insertIndex = 0;
    for (int& job : individual.jobSequence) {
        if (individual.personalJobs[job - 1].assignedFactoryID == factoryID) {
            job = -1;  
        }
    }
    for (int& job : individual.jobSequence) {
        if (job == -1) {
            job = individual.factorySchedule[factoryID][insertIndex++];
        }
    }

}
