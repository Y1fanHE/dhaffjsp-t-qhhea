#include"comfunc.h"
using namespace std;

FuzzyTime calculateFactoriesMaxCompletionTime(const vector<Factory>& factories) {
    FuzzyTime overallMaxCompletionTime = { 0, 0, 0 };
    int criticalFactoryID = -1; 

    for (size_t factoryID = 0; factoryID < factories.size(); ++factoryID) {
        FuzzyTime factoryMaxCompletion = calculateMaxCompletionTime(factories[factoryID].machineEndTimes);

        if (compareFuzzyTime(factoryMaxCompletion, overallMaxCompletionTime) > 0) {
            overallMaxCompletionTime = factoryMaxCompletion;
            criticalFactoryID = static_cast<int>(factoryID); 
        }
    }

    return overallMaxCompletionTime;
}