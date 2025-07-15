#include"comfunc.h"
using namespace std;

vector<vector<int>> generateFactorySchedules(const vector<int>& processingSequence, const vector<Job>& jobs, int numFactories) {

    vector<vector<int>> factorySchedules(numFactories);

    

    for (size_t i = 0; i < processingSequence.size(); i++) {
        int jobID = processingSequence[i];

        int factoryID = jobs[jobID-1].assignedFactoryID; 

        factorySchedules[factoryID].push_back(jobID);
    }

    return factorySchedules;
}
