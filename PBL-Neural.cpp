#include<stdio.h>
#include<math.h>
#include<iostream>

#define esp 0.001;

using namespace std;

					/* Function */
	float sigmoid(float x)
	{
	  return 1 / (1 + exp(-x));
	}
	
	float sigmoid_derivative(float x)
	{
	  return sigmoid(x) * (1 - sigmoid(x));
	}
/* ----------------------------------------------- */

void Inp(double *inputs)
{
	for(int i = 0; i < 3 ; i++)
		{
			cin>>inputs[i];
		}
}

void InpW(double weights[][100], int m, int n)
{
   for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++)
      {
         scanf("%lf", &weights[i][j]);
      }
}

int main()
{
	/* Declaration */
	double inputs[3];
	Inp(inputs);
	double weights[100][100];
	InpW(weights,3,2);
	double biases[3] = {1,1,1};
	double h[3] = {1,1,1};
	double output[3];
	double sum = 0;
	double sig[3];
	double d[3];
	int count = 0;
	/* Declaration */
	
	
//	output [0] = (weights[0][0]*inputs[0] + weights[0][1]*inputs[1]) + biases [0];
//	double s0 = sigmoid(output [0]);
//	output [1] = (weights[1][0]*inputs[0] + weights[1][1]*inputs[1]) + biases [1];
//	double s1 = sigmoid(output [1]);


	/* Neural calculation */
	for(int i = 0 ; i < 2 ; i++)
	{
		for(int j = 0 ; j < 1 ; j++)
		{
			for(int k = 0 ; k < 2 ; k++)
			{
				sum += (inputs[k]) * weights[i][k];
			}
			output[i] = sum + biases[i];
			sig[i] = sigmoid(output[i]);
			sum = 0;
		}
	}
	output[2] = (weights[2][0]*sig[0] + weights[2][1]*sig[1] + biases[2]);
	sig[2] = sigmoid(output[2]);
	/* Neural calculation */
	
	
	
//	cout<<sig[2]<<endl;
//	for(int i = 0; i < 2 ; i++)
//	{
//		cout<<output[i]<<endl;
//		cout<<sig[i]<<endl;
//	}
	
	d[2] = inputs[2] - sig[2];	/* Error signal calculation */
	
	do {
		/* Error signal propagation */
		d[0] = d[2] * weights[2][0];
		d[1] = d[2] * weights[2][1];
		/* Error signal propagation */
		
		
		
//		weights[0][0] = weights[0][0] + h[0]*d1*sigmoid_derivative(output[0])*inputs[0];
//		weights[0][1] = weights[0][1] + h[0]*d1*sigmoid_derivative(output[0])*inputs[0];
//		weights[1][0] = weights[1][0] + h[0]*d2*sigmoid_derivative(output[1])*inputs[1];
//		weights[1][1] = weights[1][1] + h[0]*d2*sigmoid_derivative(output[1])*inputs[1];
//		weights[2][0] = weights[2][0] + h[0]*d3*sigmoid_derivative(output[2])*sig[0];
//		weights[2][1] = weights[2][1] + h[0]*d3*sigmoid_derivative(output[2])*sig[1];

		/* Calculate Weights */
		
		for(int i = 0 ; i < 2 ; i++)
		{
			for(int j = 0 ; j < 1 ; j++)
			{
				for(int k = 0 ; k < 2 ; k++)
				{
					weights[i][k] = weights[i][k] + h[0]*d[i]*sigmoid_derivative(output[i])*inputs[i];
				}
			}
		}
		
		for(int j = 0 ; j < 2; j++)
		{
			weights[2][j] = weights[2][j] + h[0]*d[2]*sigmoid_derivative(output[2])*sig[j];
		}
		
		/*  Weights Calculation*/
		
		/* Neural calculation */
		for(int i = 0 ; i < 2 ; i++)
		{
			for(int j = 0 ; j < 1 ; j++)
			{
				for(int k = 0 ; k < 2 ; k++)
				{
					sum += (inputs[k]) * weights[i][k];
				}
				output[i] = sum + biases[i];
				sig[i] = sigmoid(output [i]);
				sum = 0;
			}
		}
		output[2] = (weights[2][0]*sig[0] + weights[2][1]*sig[1] + biases[2]);
		sig[2] = sigmoid(output[2]);
		/* Neural calculation */
		
		d[2] = inputs[2] - sig[2]; /* Error signal calculation */
		//cout<<d[2]<< " ";
		if(d[2] == 0)
		{
			//cout<<" *** "<<weights[0][0]<<" "<<weights[0][1]<<" "<<weights[1][0]<<" "<<weights[1][1]<<" "<<weights[2][0]<<" "<<weights[2][1]<<" ";
			//cout<<"--- "<<count<<" --- ";	
				
			cout<<weights[0][0]<<" "<<weights[0][1]<<" "<<weights[1][0]<<" "<<weights[1][1]<<" "<<weights[2][0]<<" "<<weights[2][1]<<" ";
			
			break;
		}
		count++;
	}while(count < 500);
		
		if(count >= 500)
		{
			cout<<weights[0][0]<<" "<<weights[0][1]<<" "<<weights[1][0]<<" "<<weights[1][1]<<" "<<weights[2][0]<<" "<<weights[2][1]<<" ";	
		}

	return 0;
}

