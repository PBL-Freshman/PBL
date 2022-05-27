#include<stdio.h>
#include<math.h>
#include<iostream>
#include <fstream>
#include<algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

bool comp(const int a, const int b){
   return a > b;
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main()
{
	srand(time(NULL)); 
	int j = 0;
	int inputs[100];
	int inputs1[100];
	double inputs_[100];
	double weights[100];
	ofstream myfileout;
	FILE* myfilein = fopen("training.txt","r");
   	myfileout.open ("training-out.txt");
    while (!feof(myfilein) && j <= 100 )
    {
    
      for(int i = j; i<j+5;i++)
      {
      	fscanf(myfilein,"%i",&inputs[i]);
	  }
	  
	  for(int i = j; i<j+5;i++)
      {
      	inputs1[i] = inputs[i];
	  }
	  
	  sort(inputs1, inputs1 + 5,comp);
	  
	  for(int i = j; i<j+5;i++)
      {
      	inputs_[i] = (inputs[i]*0.8)/(inputs1[4] - inputs1[0]);
	  }
	  
	  	
	  	
	  	for(int i = j; i<j+5;i++)
      	{
      		if(inputs_[i] >= 0)
      		{
      			myfileout <<inputs_[i]<<" ";
			}
			else {
				myfileout <<-inputs_[i]<<" ";
			}
	  	}
	  	
	   	j+=1;
    }
    
    return 0;
}

