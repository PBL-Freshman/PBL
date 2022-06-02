#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include <ctime>
#include <cstring>

bool comp(const int a, const int b){
   return a > b;
}

using namespace std;

int main() {
	
	ofstream myfileout;
   	myfileout.open ("training-out.txt");
	double inputs[200];
	double inputs1[200];
	double inputs_[200];
    ifstream ifile("training.txt", std::ios::in);
    vector<double> scores;

    //check to see that the file was opened correctly:
    if (!ifile.is_open()) {
        cerr << "There was a problem opening the input file!\n";
        exit(1);//exit or do additional error checking
    }

    double num = 0.0;
    //keep storing values from the text file so long as data exists:
    
    while (ifile >> num) {
        scores.push_back(num);
    }
    int size = scores.size();
    
    std::copy(scores.begin(), scores.end(), inputs);
    
    for(int j = 0 ; j < 105 ; j++){
		inputs1[j] = inputs[j]/10000;
	}

    for(int j = 0 ; j < 105 ; j+=5){
    	for(int i = j; i< j+5; i++){
    			sort(inputs1+j, inputs1 +j+5,comp);
    			inputs_[i] = (inputs[i]*0.8)/(inputs1[j]*10000 - inputs1[j+4]*10000);
    			myfileout <<inputs_[i]<<" ";
		}
	}

    return 0;
}
