#include<stdio.h>
#include<math.h>
#include<iostream>
#include <fstream>

#define esp 0.001	
int ins,wts;
using namespace std;

					/* Function */
	//	float sigmoid(float x)	
	//	{
	//	  return 1 / (1 + exp(-x));
	//	}
	
	// Fast sigmoid
	float sigmoid(float x)
	{
	  return x / (1 + abs(x));
	}
	
	float sigmoid_derivative(float x)
	{
	  return sigmoid(x) * (1 - sigmoid(x));
	}
	
	
	
	void getData(double *inputs, double weights[][100]){
		
			
			FILE* fp = fopen("inp.txt","r");
			fscanf(fp,"#%i,%i",&ins,&wts);
		
			int z = 0;
			for(int i=1;i<=ins;i++){
				fscanf(fp,"%lf",&inputs[z]);
				z++;
				}
				
			int j = 0;
			int k = 0;
			for(int i=(ins+1);i<=(ins + wts);i++){
				for(int j = 0 ; j < (wts/2); j++)
				{
					for(int k = 0 ; k < 2; k++){
						fscanf(fp,"%lf",&weights[j][k]);
					}
				}
				}
				fclose(fp);
	}
	
	void neuralCalc(double *inputs, double weights[][100],double *output, double *sig){
		double sum = 0;
		for(int i = 0 ; i < 2 ; i++)
		{
			for(int j = 0 ; j < 1 ; j++)
			{
				for(int k = 0 ; k < 2 ; k++)
				{
					sum += (inputs[k]) * weights[i][k];
				}
			output[i] = sum + 1;
			sig[i] = sigmoid(output[i]);
			sum = 0;
			}
		}
	output[2] = (weights[2][0]*sig[0] + weights[2][1]*sig[1] + 1);
	sig[2] = sigmoid(output[2]);
	}
	
	void weightsCalc(double *inputs, double weights[][100],double *output, double *sig,double *d){
		for(int i = 0 ; i < 2 ; i++)
		{
			for(int j = 0 ; j < 1 ; j++)
			{
				for(int k = 0 ; k < 2 ; k++)
				{
					weights[i][k] += d[i]*sigmoid_derivative(output[i])*inputs[i];
				}
			}
		}
		
		for(int j = 0 ; j < 2; j++)
		{
			weights[2][j] += d[2]*sigmoid_derivative(output[2])*sig[j];
		}
	}
	
	float erSigCalc(double *inputs,double *sig,double *d){
		d[2] = inputs[2] - sig[2];
		return d[2];
	}
	
/* ----------------------------------------------- */



int main()
{
	
	
	
	/* Declaration */
	double inputs[100];
	double weights[100][100];
	double output[3];
	double sig[3];
	double d[3];
	int count = 0;
	bool error = false;
	/* Declaration */
	
	getData(inputs,weights);

	neuralCalc(inputs,weights,output,sig);	 /* Neural calculation */	
	erSigCalc(inputs,sig,d); /* Error signal calculation */
	do {
		/* Error signal propagation */
		d[0] = d[2] * weights[2][0];
		d[1] = d[2] * weights[2][1];
		/* Error signal propagation */
		
		weightsCalc(inputs,weights,output,sig,d); /*  Weights Calculation*/
		neuralCalc(inputs,weights,output,sig); /* Neural calculation */ 	
																												
		if(erSigCalc(inputs,sig,d) <= esp)
		{
			for(int i = 0 ; i<(wts/2);i++)
			{
				for(int j = 0; j<2;j++)
				{
					if(weights[i][j] < 0 ) error = true;
				}
			}
			if(!error)
			{
				for(int i = 0 ; i<(wts/2);i++)
				{
					for(int j = 0; j < 2; j++)
					{
						cout<<weights[i][j]<<" ";
					}
				}
			}
			break;
		}
		count++;
	}while(count < 5000);
		if(count >= 5000 || error == true)
		{
			cout<<"Can't find weights";
		}
		
	
	return 0;
	
}

