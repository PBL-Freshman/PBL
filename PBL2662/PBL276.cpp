#include<stdio.h>
#include<math.h>
#include<iostream>
#include <fstream>

#define esp 0.001	
int ins,wts;
FILE* fp = fopen("training-out.txt","r");
int counts = 0;

using namespace std;

float sigmoid(float x)
	{
	  return x / (1 + abs(x));
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
	/* Declaration */
	double inputs[100];
	double weights[100][100];
	double output[100];
	double sig[100];
	double d[100];
	int count = 0;
	bool error = false;
	/* Declaration */
	
	while(!feof(fp)){
		counts++;
			cout<<"\n";
			fscanf(fp,"#%i,%i",&ins,&wts);
			int z = 0;
		for(int i=1;i<=ins;i++){
			fscanf(fp,"%lf",&inputs[z]);
			z++;
		}
		int j = 0;
		int k = 0;
		for(int i=(ins+1);i<=(ins + wts);i++){
			for(int j = 0 ; j <ins; j++)
				{
					for(int k = 0 ; k < (wts/ins); k++){
						fscanf(fp,"%lf",&weights[j][k]);
					}
				}
		}
				for(int i=0;i<ins-1;i++){
			cout<<"Target["<<counts<<"] = "<<inputs[i]<<" "<<"\n";
			}
			cout<<"Target["<<counts<<"] = "<<inputs[ins-1]<<" "<<"\n";
			cout<<"\n";
			
			for(int i=0;i<ins;i++){
			for(int j = 0 ; j < (wts/ins); j++)
				{
					printf("Target[%i] Weight[%i][%i] = %g \n",counts,i,j,weights[i][j]);
				}
	}
			cout<<"\n";
			
//			neuralCalc(inputs,weights,output,sig);	 /* Neural calculation */	
//			erSigCalc(inputs,sig,d); /* Error signal calculation */
			forwardPro(inputs,weights,output,sig,d);
		do{
			if(fabs(erSigCalc(inputs,sig,d)) <= esp){
						
						for(int i = 0 ; i<=(wts/ins);i++)
						{
							for(int j = 0; j <(wts/ins); j++)
							{
								printf("New Weight[%i][%i] = %g \n",i,j,weights[i][j]);
							}
						}
					
					cout<<"------------------------------------------------";
					break;
			}else {
//				erSigPPGT(weights,d);
//				weightsCalc(inputs,weights,output,sig,d);
//				neuralCalc(inputs,weights,output,sig);
//				erSigCalc(inputs,sig,d);
				backwardPro(inputs,weights,output,sig,d);
			}
			count++;
		}while(count < 50000);
		if(count >= 50000 || error == true)
		{
			cout<<"Can't find weights";
		}		
		
	
	
			
			
//			do {
//					erSigPPGT(weights,d); /* Error signal propagation */
//					weightsCalc(inputs,weights,output,sig,d); /*  Weights Calculation*/
//					neuralCalc(inputs,weights,output,sig); /* Neural calculation */ 	
//																												
//					if(erSigCalc(inputs,sig,d) <= esp)
//						{
//						for(int i = 0 ; i<=(wts/ins);i++)
//						{
//							for(int j = 0; j<(wts/ins);j++)
//							{
//								if(weights[i][j] < 0 ) error = true;
//							}
//						}
//					if(!error)
//					{
//						for(int i = 0 ; i<=(wts/ins);i++)
//						{
//							for(int j = 0; j <(wts/ins); j++)
//							{
//								printf("New Weight[%i][%i] = %g \n",i,j,weights[i][j]);
//							}
//						}
//					}
//					cout<<"------------------------------------------------";
//					break;
//		}

}
}
