#include"comfunc.h"
using namespace std;

vector<FuzzyTime> calculateProductArrivalTimes(const vector<Product>& products, const vector<FuzzyTime>& jobArrivalTimes) {
    vector<FuzzyTime> productArrivalTimes(products.size());

    for (size_t i = 0; i < products.size(); ++i) {
        FuzzyTime maxArrivalTime = { 0, 0, 0 };

        for (int jobID : products[i].componentJobs) {
   
            if (jobID - 1 >= 0 && jobID - 1 < jobArrivalTimes.size()) {
                maxArrivalTime = maxFuzzyTime(maxArrivalTime, jobArrivalTimes[jobID - 1]);  
            }
            else {
                cout << "¾¯¸æ: jobID " << jobID << " Ô½½ç!" << endl;
            }
        }

        productArrivalTimes[i] = maxArrivalTime;
    }

    return productArrivalTimes;
}
