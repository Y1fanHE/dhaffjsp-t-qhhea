#include"comfunc.h"
using namespace std;

vector<int> assignFactories(const vector<vector<double>>& probabilities, int numFactories, mt19937& gen) {
    size_t numJobs = probabilities.size();
    vector<int> assignments(numJobs, -1); 

    
    uniform_real_distribution<> probDist(0.0, 1.0); 
    uniform_real_distribution<> rouletteDist(0.0, 1.0); 
    uniform_int_distribution<> randomFactoryDist(0, numFactories - 1); 

    for (size_t jobIndex = 0; jobIndex < numJobs; ++jobIndex) {
        double randomChoice = probDist(gen); 

        if (randomChoice < 0.8) {
           
            double randValue = rouletteDist(gen); 
            double cumulativeProbability = 0.0;

            for (int factoryID = 0; factoryID < numFactories; ++factoryID) {
                cumulativeProbability += probabilities[jobIndex][factoryID];
                if (randValue < cumulativeProbability) {
                    assignments[jobIndex] = factoryID; 
                    break;
                }
            }
        }
        else {
            assignments[jobIndex] = randomFactoryDist(gen); 
        }
    }

    return assignments;
}