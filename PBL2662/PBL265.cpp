#include<stdio.h>
#include<math.h>
#include<iostream>
#include <fstream>
#include<algorithm>
#include <ctime>
#include <cstdlib>

#define esp 0.001	
int ins = 5,wts = 20;

int counts = 0;

   			
using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

float sigmoid(float x)
	{
	  return x / (1 + fabs(x));
	}
	
	float sigmoid_derivative(float x)
	{
	  return sigmoid(x) * (1 - sigmoid(x));
	}
	
//	float sigmoid_derivative(float x)
//	{
//	  return exp(x)/pow(1+exp(x),2);
//	}

	void neuralCalc(double *inputs, double weights[][100],double *output, double *sig){
		double sum = 0;
		for(int i = 0 ; i < (ins-1) ; i++)
		{
			for(int j = 0 ; j < 1 ; j++)
			{
				for(int k = 0 ; k < (wts/ins) ; k++)
				{
					sum += (inputs[k]) * weights[k][i];
				}
			output[i] = sum + 1;
			sig[i] = sigmoid(output[i]);
			sum = 0;
			}
		}
	output[ins-1] = (weights[ins-1][0]*sig[0] + weights[ins-1][1]*sig[1] + weights[ins-1][2]*sig[2] + weights[ins-1][4]*sig[3]+ 1);
	sig[ins-1] = sigmoid(output[ins-1]);
	}
	
	void weightsCalc(double *inputs, double weights[][100],double *output, double *sig,double *d){
		for(int i = 0 ; i < (ins-1) ; i++)
		{
			for(int j = 0 ; j < 1 ; j++)
			{
				for(int k = 0 ; k < (wts/ins); k++)
				{
					weights[k][i] += d[i]*sigmoid_derivative(output[i])*inputs[i];
				}
			}
		}
		
		for(int j = 0 ; j < (ins-1); j++)
		{
			weights[wts/ins][j] += d[ins-1]*sigmoid_derivative(output[ins-1])*sig[j];
		}
	}
	
	float erSigCalc(double *inputs,double *sig,double *d){
		d[ins-1] = inputs[ins-1] - sig[ins-1];
		return d[ins-1];
	}
	
	void erSigPPGT(double weights[][100],double *d){
		for(int i = 0; i < (wts/ins); i++){
			d[i] = d[ins - 1] * weights[wts/ins][i];
		}
	}
	
	void forwardPro(double *inputs, double weights[][100],double *output, double *sig,double *d){
		neuralCalc(inputs,weights,output,sig);	 /* Neural calculation */	
		erSigCalc(inputs,sig,d); /* Error signal calculation */
	}
	
	void backwardPro(double *inputs, double weights[][100],double *output, double *sig,double *d){
		erSigPPGT(weights,d);	/* Error signal propagation */
		weightsCalc(inputs,weights,output,sig,d);	/*  Weights Calculation*/
		neuralCalc(inputs,weights,output,sig);  /* Neural calculation */
		erSigCalc(inputs,sig,d); /* Error signal calculation */
	}

int main()
{
	srand(time(NULL)); 
	/* Declaration */
	double inputs[100];
	double $inputs[100];
	double $$inputs[100];
	double weights[100][100];
	double $weights[100][100];
	double output[100];
	double sig[100];
	double d[100];
	int count = 0;
	int q = 0;
	double sum = 0;
	/* Declaration */
	FILE* fp = fopen("training-out.txt","r");
	for(int i = 0 ; i<=(wts/ins);i++){
		for(int j = 0; j <(wts/ins); j++)
		{
			weights[i][j] = fRand(0.1,0.9);			
		}
	}
	while(!feof(fp)){
			cout<<"\n";
			for(int i = 0; i<105; i++)
			{
				fscanf(fp,"%lf",&$inputs[i]);
			}
			
			
			for(int u = 0; u < 105; u+=5)
			{
				sum = 0;
				q = 0;
				for(int i = u; i<u+4;i++)
     		 	{
					cout<<"Target["<<u/5<<"] = "<<$inputs[i]<<" "<<"\n";
	  			}
	  				cout<<"Target["<<u/5<<"] output = "<<$inputs[u+4]<<" "<<"\n";
	  			cout<<"\n";
	  			
	  			for(int i = 0 ; i<=(wts/ins);i++){
					for(int j = 0; j <(wts/ins); j++)
					{
						$weights[i][j] = weights[i][j];
						cout<<"Target["<<u/5<<"] weight = "<<$weights[i][j]<<" "<<"\n";			
					}
				}
				cout<<"\n";
				int j = 0;
				for(int i = u; i<u+4;i++)
     		 	{
					$$inputs[j] = $inputs[i];
					j++;
	  			}
	  			j = 0;
	  			
//	  			for(int i = 0; i<4;i++)
//     		 	{
//					cout<<$$inputs[i]<<" ? ";
//	  			}
//				cout<<"\n";
// 			 	for(int i = 0 ; i<=(wts/ins);i++){
//					for(int j = 0; j <(wts/ins); j++)
//					{
//						cout<<"Target["<<u/5<<"] weight = "<<$weights[i][j]<<" ? "<<"\n";			
//					}
//				}
//				neuralCalc($$inputs,$weights,output,sig);	 /* Neural calculation */	
//				erSigCalc($$inputs,sig,d); /* Error signal calculation */
					
				do{
					forwardPro($$inputs,$weights,output,sig,d);
					
					sum += erSigCalc(inputs,sig,d);
					q++;
					
					if(fabs(erSigCalc($$inputs,sig,d)) <= esp){						
							for(int i = 0 ; i<=(wts/ins);i++)
							{
								for(int j = 0; j <(wts/ins); j++)
								{
									weights[i][j] = $weights[i][j];
									//printf("New Weight[%i][%i] = %g \n",i,j,$weights[i][j]);
									printf("%g ",$weights[i][j]);
								}
							}
					cout<<"------------------------------------------------ \n";
					break;
				}else {
//					erSigPPGT($weights,d);	/* Error signal propagation */
//					weightsCalc($$inputs,$weights,output,sig,d);	/*  Weights Calculation*/
//					neuralCalc($$inputs,$weights,output,sig);  /* Neural calculation */
//					erSigCalc($$inputs,sig,d); /* Error signal calculation */
					backwardPro($$inputs,$weights,output,sig,d);
					cout<<"\n^^^"<<(sum/q)<<"\n";
				}
				count++;
			}while(count < 50000);
			if(count >= 50000)
			{
				cout<<"Can't find weights";
			}	
				cout<<"\n^^^"<<(sum/q)<<"\n";
		}
	
}
}
