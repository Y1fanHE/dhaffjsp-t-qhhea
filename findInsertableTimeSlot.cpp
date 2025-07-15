#include"comfunc.h"
using namespace std;

FuzzyTime findInsertableTimeSlot(const vector<ScheduledTask>& machineSchedule,
    FuzzyTime processing,
    FuzzyTime previousOperationEndTime) {
    if (machineSchedule.empty()) {
        return previousOperationEndTime; 
    }

    FuzzyTime firstStart = machineSchedule[0].start;
    FuzzyTime gapBeforeFirst = subtractFuzzyTime(firstStart, previousOperationEndTime);
    if (compareFuzzyTime(gapBeforeFirst, processing) >= 0) {
        return previousOperationEndTime;
    }

    for (size_t i = 0; i < machineSchedule.size() - 1; ++i) {
        FuzzyTime prevEnd = maxFuzzyTime(machineSchedule[i].end, previousOperationEndTime);
        FuzzyTime nextStart = machineSchedule[i + 1].start;

        FuzzyTime gap = subtractFuzzyTime(nextStart, prevEnd);
        if (compareFuzzyTime(gap, processing) >= 0) {
            return prevEnd;
        }
    }

    return maxFuzzyTime(machineSchedule.back().end, previousOperationEndTime);
}
