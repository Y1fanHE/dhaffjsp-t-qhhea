#include"comfunc.h"
using namespace std;

FuzzyTime factoryScheduling(vector<Factory>& factories,
    const vector<vector<int>>& factorySchedules,
    const vector<Job>& jobs,
    vector<FuzzyTime>& completionTimes,
    int numMachines) {
    FuzzyTime overallMaxCompletionTime = { 0, 0, 0 };
    for (size_t factoryID = 0; factoryID < factories.size(); ++factoryID) {

    vector<vector<ScheduledTask>> machineSchedules(numMachines);

        vector<int> jobSequence = factorySchedules[factoryID];
        vector<int> machineSequence = InitialSchedule(jobSequence, jobs, factories[factoryID].machineEndTimes, factoryID, completionTimes,machineSchedules);

    overallMaxCompletionTime = calculateFactoriesMaxCompletionTime(factories);
    return overallMaxCompletionTime;
}