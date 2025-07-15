#include "comfunc.h"
using namespace std;

vector<int> InitialSchedule(const vector<int>& jobSequence, const vector<Job>& jobs,
    vector<vector<FuzzyTime>>& machineEndTimes, int assignedFactoryID,
    vector<FuzzyTime>& completionTimes,
    vector<vector<ScheduledTask>>& machineSchedules) {
    for (auto& machine : machineEndTimes) {
        machine.clear();
    }

    int numMachines = machineEndTimes.size();
    vector<int> machineSequence;
    vector<size_t> operationCount(jobs.size(), 0);
    vector<int> lastOperationIndex(jobs.size(), -1);

    for (size_t jobIndex = 0; jobIndex < jobSequence.size(); ++jobIndex) {
        int jobID = jobSequence[jobIndex] - 1;
        const Job& currentJob = jobs[jobID];
        int operation = operationCount[jobID]++;

        int bestMachine = -1;
        FuzzyTime earliestCompletion = { 999, 999, 999 };
        FuzzyTime bestStartTime = { 0, 0, 0 };
        FuzzyTime previousOperationEndTime = { 0, 0, 0 };

        if (operation > 0) {
            for (int m = 0; m < numMachines; ++m) {
                for (const auto& task : machineSchedules[m]) {
                    if (task.jobID == jobID) {
                        if (compareFuzzyTime(task.end, previousOperationEndTime) > 0) {
                            previousOperationEndTime = task.end;
                        }
                    }
                }
            }
        }

        for (int machine = 0; machine < numMachines; ++machine) {
            FuzzyTime processing = currentJob.operations[operation].factoryProcessingTimes[assignedFactoryID][machine];

            FuzzyTime startTime = findInsertableTimeSlot(machineSchedules[machine], processing, previousOperationEndTime);

            FuzzyTime completionTime = addFuzzyTime(startTime, processing);


            if (compareFuzzyTime(completionTime, earliestCompletion) < 0) {
                earliestCompletion = completionTime;
                bestMachine = machine;
                bestStartTime = startTime;
            }
        }

        if (bestMachine != -1) {
            machineEndTimes[bestMachine].push_back(earliestCompletion);
            machineSequence.push_back(bestMachine + 1);
            lastOperationIndex[jobID] = jobIndex;

            completionTimes[jobID] = earliestCompletion;

            ScheduledTask newTask = { jobID, bestStartTime, earliestCompletion };

            auto& schedule = machineSchedules[bestMachine];

            auto insertPos = schedule.begin();
            while (insertPos != schedule.end() && compareFuzzyTime(insertPos->start, bestStartTime) < 0) {
                ++insertPos;
            }
            schedule.insert(insertPos, newTask);

    }

    return machineSequence;
}
