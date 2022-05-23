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
//		return 1 / (1 + exp(-x));
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
		for(int i=0;i<ins-1;i++){
			cout<<"input["<<i<<"] = "<<inputs[i]<<" ";
			cout<<"\n";
		}
		cout<<"output = "<<inputs[ins-1];
		cout<<"\n \n";
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
		
		for(int i=0;i<ins;i++){
			for(int j = 0 ; j < 2; j++)
				{
					printf("Weight[%i][%i] = %g \n",i,j,weights[i][j]);
				}
		}
		cout<<"\n";
		fclose(fp);
	}
	
	void neuralCalc(double *inputs, double weights[][100],double *output, double *sig){
		double sum = 0;
		for(int i = 0 ; i < (ins-1) ; i++)
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
	output[ins-1] = (weights[ins-1][0]*sig[0] + weights[ins-1][1]*sig[1] + 1);
	sig[ins-1] = sigmoid(output[ins-1]);
	}
	
	void weightsCalc(double *inputs, double weights[][100],double *output, double *sig,double *d){
		for(int i = 0 ; i < (ins-1) ; i++)
		{
			for(int j = 0 ; j < 1 ; j++)
			{
				for(int k = 0 ; k < 2 ; k++)
				{
					weights[i][k] += d[i]*sigmoid_derivative(output[i])*inputs[i];
				}
			}
		}
		
		for(int j = 0 ; j < (ins-1); j++)
		{
			weights[ins-1][j] += d[ins-1]*sigmoid_derivative(output[ins-1])*sig[j];
		}
	}
	
	float erSigCalc(double *inputs,double *sig,double *d){
		d[ins-1] = inputs[ins-1] - sig[ins-1];
		return d[ins-1];
	}
	
	void erSigPPGT(double weights[][100],double *d){
		for(int i = 0; i < (ins - 1); i++){
			d[i] = d[ins - 1] * weights[ins - 1][i];
		}
	}
	
/* ----------------------------------------------- */



int main()
{
	/* Declaration */
	double inputs[100];
	double weights[100][100];
	double output[100];
	double sig[100];
	double d[100];
	int count = 0;
	bool error = false;
	/* Declaration */
	
	getData(inputs,weights);

	neuralCalc(inputs,weights,output,sig);	 /* Neural calculation */	
	erSigCalc(inputs,sig,d); /* Error signal calculation */
	
	do {
		erSigPPGT(weights,d); /* Error signal propagation */
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
						printf("New Weight[%i][%i] = %g \n",i,j,weights[i][j]);
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

