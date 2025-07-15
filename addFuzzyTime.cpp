#include"comfunc.h"
using namespace std;

FuzzyTime addFuzzyTime(const FuzzyTime& t1, const FuzzyTime& t2) {
    return { t1.optimistic + t2.optimistic, t1.most_likely + t2.most_likely, t1.pessimistic + t2.pessimistic };
}