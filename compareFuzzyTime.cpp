#include"comfunc.h"
using namespace std;

int compareFuzzyTime(const FuzzyTime& t1, const FuzzyTime& t2) {
    double c1_t1 = (t1.optimistic + 2 * t1.most_likely + t1.pessimistic) / 4.0;
    double c1_t2 = (t2.optimistic + 2 * t2.most_likely + t2.pessimistic) / 4.0;


    if (c1_t1 > c1_t2) {
        return 1;
    }
    else if (c1_t1 < c1_t2) {
        return -1;
    }
    
}