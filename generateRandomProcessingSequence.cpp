#include"comfunc.h"
using namespace std;


vector<int> generateRandomProcessingSequence(const vector<Job>& jobs, mt19937& gen) {
    vector<int> processingSequence;


    for (const auto& job : jobs) {
        for (int i = 0; i < job.operations.size(); ++i) {
 
            processingSequence.push_back(job.jobID);
        }
    }


    shuffle(processingSequence.begin(), processingSequence.end(), gen);

    return processingSequence;
}