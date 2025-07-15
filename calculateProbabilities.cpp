#include"comfunc.h"
using namespace std;

vector<vector<double>> calculateProbabilities(const vector<vector<double>>& averageProcessingTimes) {
    size_t numJobs = averageProcessingTimes.size();
    size_t numFactories = averageProcessingTimes[0].size();

    vector<vector<double>> probabilities(numJobs, vector<double>(numFactories, 0.0));

    for (size_t jobIndex = 0; jobIndex < numJobs; ++jobIndex) {
        double inverseSum = 0.0;

        for (size_t factoryID = 0; factoryID < numFactories; ++factoryID) {
            if (averageProcessingTimes[jobIndex][factoryID] > 0) {
                inverseSum += 1.0 / averageProcessingTimes[jobIndex][factoryID];
            }
        }

        for (size_t factoryID = 0; factoryID < numFactories; ++factoryID) {
            if (averageProcessingTimes[jobIndex][factoryID] > 0) {
                probabilities[jobIndex][factoryID] = (1.0 / averageProcessingTimes[jobIndex][factoryID]) / inverseSum;
            }
        }
    }

    return probabilities;
}