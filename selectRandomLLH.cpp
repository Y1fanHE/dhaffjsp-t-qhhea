#include"comfunc.h"
using namespace std;

int selectRandomLLH(mt19937& gen) {
    uniform_int_distribution<int> dist(0, 5); // 6¸öLLH (0-5)
    return dist(gen);
}
