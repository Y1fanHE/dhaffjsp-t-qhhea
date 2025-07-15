#include"comfunc.h"
using namespace std;

//计算关键工厂
void calculateCriticalFactory(const vector<Factory>& factories, int criticalFactoryID) {
    FuzzyTime maxCompletionTime = { 0, 0, 0 };
    

    for (size_t factoryID = 0; factoryID < factories.size(); ++factoryID) {
        FuzzyTime factoryCompletionTime = calculateMaxCompletionTime(factories[factoryID].machineEndTimes);
        if (compareFuzzyTime(factoryCompletionTime, maxCompletionTime) > 0) {
            maxCompletionTime = factoryCompletionTime;
            criticalFactoryID = factoryID;
        }
    }
}
