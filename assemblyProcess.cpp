#include"comfunc.h"
using namespace std;

FuzzyTime assemblyProcess(const vector<Product>& products,
    const vector<pair<FuzzyTime, int>>& sortedProductArrivals,
    AssemblyFactory& assemblyFactory) {
    vector<FuzzyTime> productEndTimes(products.size());

    for (const auto& [arrivalTime, pid] : sortedProductArrivals) {
        int index = pid - 1;
        const Product& product = products[index];

        FuzzyTime startTime = maxFuzzyTime(arrivalTime, assemblyFactory.assemblyLineEndTime);
        FuzzyTime endTime = addFuzzyTime(startTime, product.assemblyTimes);

        productEndTimes[index] = endTime;
        assemblyFactory.assemblyLineEndTime = endTime;
        
    FuzzyTime makespan = { 0, 0, 0 };
    for (const auto& t : productEndTimes) {
        makespan = maxFuzzyTime(makespan, t);
    }

    return makespan;
}
