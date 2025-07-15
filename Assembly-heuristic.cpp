#include"comfunc.h"
using namespace std;

void Assembly-heuristic(
    vector<Factory>& factories,
    Individual& individual,
    const vector<Job>& jobs,
    const vector<Product>& products,
    int numMachines,
    int numJobs,
    int numFactories) {

    vector<FuzzyTime> completionTimes(numJobs, { 0, 0, 0 });
    FuzzyTime processingmakespan = factoryScheduling(factories, individual.factorySchedule, jobs, completionTimes, numMachines);

    vector<pair<FuzzyTime, int>> jobCompletionTimes;
    for (int i = 0; i < numJobs; ++i) {
        jobCompletionTimes.emplace_back(completionTimes[i], i);
    }
    sort(jobCompletionTimes.begin(), jobCompletionTimes.end(), [](const auto& a, const auto& b) {
        return compareFuzzyTime(a.first, b.first) < 0;
        });

    vector<pair<FuzzyTime, int>> productCompletionTimes;
    for (int p = 0; p < products.size(); ++p) {
        FuzzyTime latest = { 0, 0, 0 };
        for (int jobID : products[p].componentJobs) {
            latest = maxFuzzyTime(latest, completionTimes[jobID - 1]);
        }
        productCompletionTimes.emplace_back(latest, p);
    }
    sort(productCompletionTimes.begin(), productCompletionTimes.end(), [](const auto& a, const auto& b) {
        return compareFuzzyTime(a.first, b.first) < 0;
        });

    vector<pair<FuzzyTime, int>> prioritizedJobs;
    for (const auto& [_, pidx] : productCompletionTimes) {
        const Product& prod = products[pidx];
        vector<pair<FuzzyTime, int>> jobGroup;
        for (int jid : prod.componentJobs) {
            jobGroup.emplace_back(completionTimes[jid - 1], jid - 1);
        }
        sort(jobGroup.begin(), jobGroup.end(), [](const auto& a, const auto& b) {
            return compareFuzzyTime(a.first, b.first) < 0;
            });
        for (auto& entry : jobGroup) {
            prioritizedJobs.push_back(entry);
        }
    }

    int capacity = numJobs / numFactories;
    Truck truck(1, capacity, truckTransportTime);
    vector<FuzzyTime> jobArrivalTimes(numJobs, { 0, 0, 0 });
    vector<bool> transported(numJobs, false);
    FuzzyTime truckEndTime = { 0, 0, 0 };

    int index = 0, batchCount = 0;
    while (index < prioritizedJobs.size()) {
        vector<int> batch;
        FuzzyTime latestComp = { 0, 0, 0 };

        while (batch.size() < capacity && index < prioritizedJobs.size()) {
            int jid = prioritizedJobs[index].second;
            if (!transported[jid]) {
                batch.push_back(jid);
                transported[jid] = true;
                latestComp = maxFuzzyTime(latestComp, completionTimes[jid]);
            }
            index++;
        }

        FuzzyTime departTime = (batchCount == 0) ? latestComp : maxFuzzyTime(truckEndTime, latestComp);
        FuzzyTime arriveTime = addFuzzyTime(departTime, truck.transportTime);

        truck.clearQueue();
        truckEndTime = addFuzzyTime(arriveTime, truck.transportTime);  // ¿¨³µ·µ»Ø
        batchCount++;
    }

    vector<FuzzyTime> productArrivalTimes = calculateProductArrivalTimes(products, jobArrivalTimes);

    AssemblyFactory assemblyFactory(0);  

    vector<pair<FuzzyTime, int>> sortedProductArrivals;
    for (int i = 0; i < products.size(); ++i) {
        sortedProductArrivals.emplace_back(productArrivalTimes[i], products[i].productID);
    }
    sort(sortedProductArrivals.begin(), sortedProductArrivals.end(), [](const auto& a, const auto& b) {
        return compareFuzzyTime(a.first, b.first) < 0;
        });


    FuzzyTime makespan = assemblyProcess(products, sortedProductArrivals, assemblyFactory);

    if (compareFuzzyTime(makespan, individual.makespan) < 0)
        individual.makespan = makespan;



   
}