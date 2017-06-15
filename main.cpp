#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

void showNums(vector <double> numRead);
double countWij(int i, int j, vector <vector <double>> &v);

int main() {

    vector <vector <double>> patterns(10);

    ifstream ofs("/home/stasey/Документы/representValues/number.txt", ofstream::in);

    double a;
    int count = 0;

    // reading all patterns

    while(ofs >> a){
        if(a > 8){
            count++;
        }
        else {
            patterns[count].push_back(a);
        }
    }

    vector <vector <double>> weights (patterns[0].size(), vector <double> (patterns[0].size()));

    // counting weights

    for(int i = 0; i < weights.size(); i++){
        for(int j = 0; j < weights[i].size(); j++){
            weights[i][j] = countWij(i, j, patterns);
        }
    }

    return 0;
}

// function to display numbers

void showNums(vector <double> numRead){
    int k = floor(sqrt(numRead.size()));

    for(auto i = 0; i < numRead.size(); i++){
        if((i % k) == 0){
            cout << endl;
        }
        cout << (int)numRead[i];

    }
}

// function to count weight[i][j]

double countWij(int i, int j, vector <vector <double>> &v){
    double sum = 0;
    for(int s = 0; s < v.size(); s++){
        sum = sum + (2*v[s][i] - 1)*(2*v[s][j] - 1);
    }
    return sum;
}