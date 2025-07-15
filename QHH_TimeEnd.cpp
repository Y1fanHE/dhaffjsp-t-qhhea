#include"comfunc.h"
using namespace std;
using namespace chrono;



FuzzyTime QHH_TimeEnd(vector<Individual>& population, vector<Factory>& factories,
    vector<Job>& jobs, vector<Product>& products,
    int numFactories, int numMachines, mt19937& gen,
    FuzzyTime initialBestMakespan, int numJobs) {

    int numStates = 12;
    int numActions = 6;
    vector<vector<double>> QTable(numStates, vector<double>(numActions, 0.0));
    double gamma = 0.9;
    double alpha = 0.8;
    double epsilon = 0.7;

    FuzzyTime bestMakespan = initialBestMakespan;
    FuzzyTime globalBestMakespan = initialBestMakespan;

    auto startTime = chrono::steady_clock::now();
    double timeLimitSeconds = 0.5 * numMachines * numJobs;

    ofstream logFile(globalLogPath);



    double initialScalar = fuzzyTimeToScalar(initialBestMakespan);

    for (auto& ind : population) {
        ind.state = 3;
    }

    int iter = 0;

    while (true) {
        auto now = chrono::steady_clock::now();
        double elapsed = chrono::duration<double>(now - startTime).count();
        if (elapsed > timeLimitSeconds) break;

        sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
            return compareFuzzyTime(a.makespan, b.makespan) < 0;
            });
        int eliteSize = max(1, (int)(0.01 * population.size()));
        vector<Individual> eliteIndividuals(population.begin(), population.begin() + eliteSize);


        double progressRatio = min(1.0, elapsed / timeLimitSeconds); 
        epsilon = epsilon * progressRatio;
        alpha = alpha * progressRatio;
    
        for (int i = eliteSize; i < population.size(); ++i) {
            Individual& ind = population[i];

            int selectedLLH;
            uniform_real_distribution<double> dist(0.0, 1.0);
            if (dist(gen) < epsilon) {
                uniform_int_distribution<int> randLLH(0, numActions - 1);
                selectedLLH = randLLH(gen);
            }
            else {
                selectedLLH = distance(QTable[ind.state].begin(),
                    max_element(QTable[ind.state].begin(), QTable[ind.state].end()));
            }

            FuzzyTime prevMakespan = ind.makespan;
            int prevState = ind.state;

            NewApplyLLH(selectedLLH, ind, factories, jobs, products, numFactories, numMachines, gen, numJobs);  // 需支持单个个体调用

            FuzzyTime currentMakespan = ind.makespan;


            if (compareFuzzyTime(currentMakespan, globalBestMakespan) < 0) {
                globalBestMakespan = currentMakespan;

            }

            int newState = getStateNo(prevMakespan, currentMakespan);
            ind.state = newState;

            double prevScalar = fuzzyTimeToScalar(prevMakespan);
            double currentScalar = fuzzyTimeToScalar(currentMakespan);
            double improvementRatio = (prevScalar - currentScalar) / prevScalar;
            double reward = improvementRatio ;

            double maxQNext = *max_element(QTable[newState].begin(), QTable[newState].end());
            QTable[prevState][selectedLLH] += alpha * (reward + gamma * maxQNext - QTable[prevState][selectedLLH]);
        }

     
        for (int i = 0; i < eliteSize; ++i) {
            population[i] = eliteIndividuals[i];
        }

        FuzzyTime currentBest = { 999, 999, 999 };
        for (const auto& ind : population) {
            if (compareFuzzyTime(ind.makespan, currentBest) < 0) {
                currentBest = ind.makespan;
            }
        }

        for (const auto& ind : population) {
            if (compareFuzzyTime(ind.makespan, globalBestMakespan) < 0) {
                globalBestMakespan = ind.makespan;
            }
        }


        iter++;
    }

    return globalBestMakespan;
}
