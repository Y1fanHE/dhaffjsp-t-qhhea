#include<iostream>
#include<stdlib.h>
#include<string>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits> 
#include <regex>
#include <utility> 
#include <random>
#include <iomanip> 
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric> 



using namespace std;

struct FuzzyTime {
    int optimistic;  
    int most_likely;
    int pessimistic; 
 
    void print(std::ostream& os = std::cout) const {
        os << "(" << optimistic << ", " << most_likely << ", " << pessimistic << ")";
    }

};

struct Operation {
    vector<vector<FuzzyTime>> factoryProcessingTimes; 
};

struct Job {
    int jobID;                  
    int assignedFactoryID = -1;     
    vector<Operation> operations;     
};

struct Factory {
    int factoryID;                             
    vector<vector<FuzzyTime>> machineEndTimes;  
};

struct Product {
    int productID;
    vector<int> componentJobs; 
    FuzzyTime assemblyTimes; 
};



struct Truck {
    int truckID;             
    int capacity;           
    vector<int> transportQueue;  
    FuzzyTime transportTime;    

    Truck(int id, int cap, FuzzyTime time)
        : truckID(id), capacity(cap), transportTime(time) {}

    void addToTransportQueue(int jobID) {
        if (transportQueue.size() < capacity) {
            transportQueue.push_back(jobID);
        
    }

    void clearQueue() {
        transportQueue.clear();
    }
};


class Individual {
public:
    int id; 
    vector<int> jobSequence;  
    vector<vector<int>> factorySchedule;  
    FuzzyTime makespan;  
    int criticalFactoryID;                
    vector<Job> personalJobs; 
    int state = 3;
    Individual(int id, const vector<int>& jobSequence, const vector<vector<int>>& factorySchedule,
        const FuzzyTime& makespan, int criticalFactoryID, const vector<Job>& globalJobs)
        : id(id), jobSequence(jobSequence), factorySchedule(factorySchedule),
        makespan(makespan), criticalFactoryID(criticalFactoryID), personalJobs(globalJobs) {
    }
};

