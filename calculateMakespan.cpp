#include"comfunc.h"
using namespace std;

FuzzyTime calculateMakespan(vector<Factory>& factories,
    const vector<vector<int>>& factorySchedules,
    const vector<Job>& jobs,
    vector<FuzzyTime>& completionTimes,
     vector<Product>& products,
    int numMachines,
    int numJobs,
    int numFactories) {

    FuzzyTime overallMaxCompletionTime = factoryScheduling(factories, factorySchedules, jobs, completionTimes,numMachines);

    vector<pair<FuzzyTime, int>> jobCompletionTimes;
    for (int i = 0; i < jobs.size(); ++i) {
        jobCompletionTimes.push_back({ completionTimes[i], i });
    }

    sort(jobCompletionTimes.begin(), jobCompletionTimes.end(), [](const pair<FuzzyTime, int>& a, const pair<FuzzyTime, int>& b) {
        return compareFuzzyTime(a.first, b.first) < 0;
        });



    int volume = numJobs / numFactories;

    Truck truck1(1, volume, truckTransportTime);  
    vector<FuzzyTime> jobArrivalTimes = transportJobs(jobCompletionTimes, jobs.size(), truck1);

    vector<FuzzyTime> productArrivalTimes = calculateProductArrivalTimes(products, jobArrivalTimes);

    AssemblyFactory assemblyFactory(0);  
    

    vector<pair<FuzzyTime, int>> sortedProductArrivals;
    for (int i = 0; i < products.size(); ++i) {
        sortedProductArrivals.emplace_back(productArrivalTimes[i], products[i].productID);
    }

    FuzzyTime makespan = assemblyProcess(products, sortedProductArrivals, assemblyFactory);

    return makespan;
}