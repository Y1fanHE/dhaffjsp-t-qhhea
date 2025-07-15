#include"comfunc.h"
using namespace std;

int getStateNo(const FuzzyTime& prevBestMakespan, const FuzzyTime& currentBestMakespan) {
    double prevScalar = fuzzyTimeToScalar(prevBestMakespan);
    double currentScalar = fuzzyTimeToScalar(currentBestMakespan);

    double improvementRatio = (prevScalar - currentScalar) / prevScalar;

   
    if (improvementRatio <= -0) return 0;   
    if (improvementRatio <= 0.01) return 1;   
    if (improvementRatio <= 0.02) return 2;   
    if (improvementRatio <= 0.03) return 3;  
    if (improvementRatio <= 0.04) return 4;   
    if (improvementRatio <= 0.05) return 5;   
    if (improvementRatio <= 0.06) return 6;  
    if (improvementRatio <= 0.07) return 7;  
    if (improvementRatio <= 0.08) return 8;   
    if (improvementRatio <= 0.09) return 9;
    if (improvementRatio <= 0.10) return 10;
    return 11;                                 
}
