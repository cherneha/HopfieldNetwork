#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

void showNums(vector <double> numRead);
double countWij(int i, int j, vector <vector <double>> &v);
double newValueInNum(vector <vector <double>> &weights, vector <double> &num, int p);

int main() {

    vector <vector <double>> patterns(4);

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
            if(i == j){
                weights[i][j] = 0;
            }
        }
    }

    vector <double> num;

    ofs.close();
    ofs.open("/home/stasey/Документы/representValues/4.txt", ofstream::in);
    while (ofs >> a){
        num.push_back(a);
    }

    showNums(num);



    bool changed = false;
    while(!changed){
        cout << "iter" << endl;
        changed = true;
        for(int i = num.size(); i >= 0; i--){
            double newVal = newValueInNum(weights, num, i);
            if(newVal != num[i]){
                changed = false;
                num[i] = newVal;
            }
        }
    }

    showNums(num);

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

// updating node value

double newValueInNum(vector <vector <double>> &weights, vector <double> &num, int p){
    double newValue = 0;
    for(int i = 0; i < num.size(); i++){
        if(i != p){
            newValue = newValue + weights[i][p]*num[i];
        }
    }
    if(newValue >= 0){
        return 1;
    }
    else{
        return 0;
    }
}