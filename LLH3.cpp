#include"comfunc.h"
using namespace std;

void LLH3(Individual& individual, vector<Factory>& factories, 
    vector<Product>& products, int numFactories, int numMachines, mt19937& gen, int numJobs) {
    int factoryID = individual.criticalFactoryID;

    if (factoryID == -1 || individual.factorySchedule[factoryID].empty()) {
        return;
    }

    vector<Job>& jobs = individual.personalJobs;

    vector<int>& schedule = individual.factorySchedule[factoryID];


    uniform_int_distribution<int> dist(0, schedule.size() - 1);
    int jobIndex = dist(gen);
    int jobID = schedule[jobIndex];

    uniform_int_distribution<int> newFactoryDist(0, numFactories - 2);
    int randIndex = newFactoryDist(gen);
    int newFactoryID = (randIndex < factoryID) ? randIndex : randIndex + 1; 

    jobs[jobID-1].assignedFactoryID = newFactoryID;

    individual.factorySchedule = generateFactorySchedules(individual.jobSequence, jobs, numFactories);

    vector<FuzzyTime> completionTimes(jobs.size(), { 0, 0, 0 });


    FuzzyTime newMakespan = calculateMakespan(factories, individual.factorySchedule, jobs, completionTimes, products, numMachines, numJobs, numFactories);

    int newCriticalFactoryID = -1;
    calculateCriticalFactory(factories, newCriticalFactoryID);

    if (newCriticalFactoryID == -1 || individual.factorySchedule[newCriticalFactoryID].empty()) return;

    individual.makespan = newMakespan;
    individual.criticalFactoryID = newCriticalFactoryID;
}
