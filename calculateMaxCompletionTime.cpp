#include"comfunc.h"
using namespace std;

FuzzyTime calculateMaxCompletionTime(const vector<vector<FuzzyTime>>& machineEndTimes) {
    FuzzyTime maxCompletion = { 0, 0, 0 };
    for (const auto& machineTimes : machineEndTimes) {
        if (!machineTimes.empty()) {
            FuzzyTime lastCompletionTime = machineTimes.back();
            maxCompletion = maxFuzzyTime(maxCompletion, lastCompletionTime);
        }
    }
    return maxCompletion;
}