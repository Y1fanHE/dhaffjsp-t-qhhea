#include"comfunc.h"
using namespace std;

vector<vector<double>> calculateAverageProcessingTime(const vector<Job>& jobs, int numFactories, int numMachines) {

    vector<vector<double>> averageProcessingTimes(jobs.size(), vector<double>(numFactories, 0.0));


    for (size_t jobIndex = 0; jobIndex < jobs.size(); ++jobIndex) {
        const Job& job = jobs[jobIndex];

        for (int factoryID = 0; factoryID < numFactories; ++factoryID) {
            double totalProcessingTime = 0.0; 

            for (size_t opIndex = 0; opIndex < job.operations.size(); ++opIndex) {
                const vector<FuzzyTime>& machineTimes = job.operations[opIndex].factoryProcessingTimes[factoryID];

                FuzzyTime sumFuzzyTime = { 0, 0, 0 };
                for (const FuzzyTime& time : machineTimes) {
                    sumFuzzyTime = addFuzzyTime(sumFuzzyTime, time);
                }

                double operationExpectedTime = (sumFuzzyTime.optimistic + 2 * sumFuzzyTime.most_likely + sumFuzzyTime.pessimistic) / 4.0;
                double operationAverageTime = operationExpectedTime / numMachines;

                totalProcessingTime += operationAverageTime; 
            }

            averageProcessingTimes[jobIndex][factoryID] = totalProcessingTime / job.operations.size();
        }
    }

    return averageProcessingTimes;
}