#include"comfunc.h"
using namespace std;

void LLH1(Individual& individual, vector<Factory>& factories, vector<Job>& jobs,
    vector<Product>& products, int numMachines, mt19937& gen, int numJobs, int numFactories) {
    int factoryID = individual.criticalFactoryID;

    if (factoryID == -1 || individual.factorySchedule[factoryID].size() < 2) {
        return;
    }

    vector<int>& schedule = individual.factorySchedule[factoryID];
  
    vector<int> validIndices;
    for (int i = 0; i < schedule.size() - 1; ++i) {
        int jobID1 = schedule[i] - 1;
        int jobID2 = schedule[i + 1] - 1;
        if (jobID1 != jobID2) {
            validIndices.push_back(i);
        }
    }

    if (validIndices.empty()) {

        return;
    }

    uniform_int_distribution<int> dist(0, validIndices.size() - 1);
    int index = validIndices[dist(gen)];

    swap(schedule[index], schedule[index + 1]);

    individual.factorySchedule[factoryID] = schedule;

    vector<FuzzyTime> completionTimes(jobs.size(), { 0, 0, 0 }); 
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
