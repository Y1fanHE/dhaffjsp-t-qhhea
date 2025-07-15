#include"comfunc.h"
using namespace std;

void NewApplyLLH(int LLH, Individual& individual, vector<Factory>& factories,
    vector<Job>& jobs, vector<Product>& products, int numFactories, int numMachines,
    mt19937& gen, int numJobs) {

    FuzzyTime bestTime = individual.makespan;

        Individual trialInd = individual; 

        switch (LLH) {
        case 0: LLH1(trialInd, factories, jobs, products, numMachines, gen, numJobs, numFactories); break;
        case 1: LLH2(trialInd, factories, jobs, products, numFactories, numJobs, numMachines); break;
        case 2: LLH3(trialInd, factories, products, numFactories, numMachines, gen, numJobs); break;
        }

       Assembly-heuristic(factories, trialInd, jobs, products, numMachines, numJobs, numFactories);

        if (compareFuzzyTime(trialInd.makespan, bestTime) < 0) {
            bestTime = trialInd.makespan;
            individual = trialInd;
        }
}


