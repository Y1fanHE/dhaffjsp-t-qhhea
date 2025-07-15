#include"comfunc.h"
using namespace std;

bool compareProductByArrivalTime(const Product& a, const Product& b, const vector<FuzzyTime>& productArrivalTimes) {
    return compareFuzzyTime(productArrivalTimes[a.productID-1], productArrivalTimes[b.productID-1]) < 0;
}