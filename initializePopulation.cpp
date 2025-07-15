#include"comfunc.h"
using namespace std;

vector<Individual> initializePopulation(int populationSize,int numFactories, int numMachines, int numJobs,  vector<Job>& jobs,  vector<Factory>& factories,
     vector<Product>& products, mt19937& gen) {

    vector<Individual> population;

    for (int i = 0; i < populationSize; ++i) {

        vector<int> processingSequence = generateRandomProcessingSequence(jobs, gen);

        vector<FuzzyTime> completionTimes(numJobs);
        for (auto& time : completionTimes) {
            time.optimistic = 0;
            time.most_likely = 0;
            time.pessimistic = 0;
        }

        vector<vector<double>> averageProcessingTimes = calculateAverageProcessingTime(jobs, numFactories, numMachines);

        vector<vector<double>> probabilities = calculateProbabilities(averageProcessingTimes);

        vector<int> assignments = assignFactories(probabilities, numFactories, gen);

        for (size_t j = 0; j < jobs.size(); ++j) {
            jobs[j].assignedFactoryID = assignments[j];
        }
     
        vector<vector<int>> factorySchedules = generateFactorySchedules(processingSequence, jobs, numFactories);

       
        FuzzyTime makespan = calculateMakespan(factories, factorySchedules, jobs, completionTimes, products,numMachines,numJobs,numFactories);

        int criticalFactoryID = -1;
        calculateCriticalFactory(factories, criticalFactoryID); 

   
        Individual individual(i + 1, processingSequence, factorySchedules, makespan, criticalFactoryID, jobs);


        population.push_back(individual);

    }
    return population;
}