#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include<iostream>
#include <fstream>
#include<algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <time.h>

#define NUMPAT 20
#define NUMIN  4
#define NUMHID 4
#define NUMOUT 1 

#define rando() ((double)rand()/((double)RAND_MAX+1))

using namespace std;

 float getrd(float min,float max)
{
  if (min == max)
  return min;
  float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
  return min + scale * ( max - min );      /* [min, max] */
}
 
main() {
	
	//Khai báo variables
/* -----------------------------------------------------------------------*/
    int    i, j, k, p, np, op, ranpat[NUMPAT+1], epoch;
    int    NumPattern = NUMPAT, NumInput = NUMIN, NumHidden = NUMHID, NumOutput = NUMOUT;
    double inputs[200];
	double $inputs[200];
	double _inputs[NUMPAT+1][NUMIN+1];
	double Input[NUMPAT+1][NUMIN+1];
	double target[NUMPAT+1][NUMOUT+1];
	double Target[NUMPAT+1][NUMOUT+1];
	double SumH[NUMPAT+1][NUMHID+1], WeightIH[NUMIN+1][NUMHID+1], Hidden[NUMPAT+1][NUMHID+1];
    double SumO[NUMPAT+1][NUMOUT+1], WeightHO[NUMHID+1][NUMOUT+1], Output[NUMPAT+1][NUMOUT+1];
    double DeltaO[NUMOUT+1], SumDOW[NUMHID+1], DeltaH[NUMHID+1];
    double DeltaWeightIH[NUMIN+1][NUMHID+1], DeltaWeightHO[NUMHID+1][NUMOUT+1];
    double Error, eta = 0.1, alpha = 0.9;
/* -----------------------------------------------------------------------*/	
	
	//IMPORT DATA
/* -----------------------------------------------------------------------*/
	ifstream ifile("training-out.txt", std::ios::in);
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
    
    for(int i = 0; i< size; i++){
    	cout<<inputs[i]<<" ";
	}
    
    for(int i = 0; i<= size; i++){
    	$inputs[i + 1] = inputs[i];
	}

	for(int i = 0; i <= NUMPAT; i++){
			_inputs[i][0] = 0;
			target[i][0] = 0;
			Input[i][0] = 0;
			Target[i][0] = 0;
	}
	
	for(int i = 0; i <= NUMPAT; i++){
		for(int j = 1 ; j < NUMIN+1;j++){
			_inputs[i][j] = $inputs[j+(5*i)];
		}
	}
	
	for(int j = 0 ; j < NUMIN+1;j++){
		Input[0][j] = 0;
	}
	
	for(int i = 0; i <= NUMPAT; i++){
		for(int j = 1 ; j < NUMIN+1;j++){
			Input[i+1][j] = _inputs[i][j];
		}
	}
	
	for(int i = 0; i <= NUMPAT; i++){
		for(int j = 1 ; j < NUMOUT+1;j++){
			target[i][j] = $inputs[5*(i+1)];
		}
	}
	
	for(int i = 0; i <= NUMPAT; i++){
		for(int j = 1 ; j < NUMOUT+1;j++){
			Target[i+1][j] = target[i][j];
		}
	}
/* ----------------------------------------------------------------------------------------------*/
    

    srand((int)time(0));

    for( j = 1 ; j <= NumHidden ; j++ ) {    /* initialize WeightIH and DeltaWeightIH */
        for( i = 1 ; i <= NumInput ; i++ ) {

            DeltaWeightIH[i][j] = 0.0 ;
            WeightIH[i][j] = getrd(0.1, 0.9);
            printf("WeightIH[%i][%i] = %lf\n", i, j, WeightIH[i][j]);
        }
    }
    
    printf("\n *///////////\n");
    for( k = 1 ; k <= NumOutput ; k ++ ) {    /* initialize WeightHO and DeltaWeightHO */
        for( j = 1 ; j <= NumHidden ; j++ ) {
            DeltaWeightHO[j][k] = 0.0 ;
             WeightHO[j][k] = getrd(0.1, 0.9);
             printf("WeightHO[%i][%i] = %lf\n", j, k, WeightHO[j][k]);
        }
    }

    for( epoch = 0 ; epoch < 200000 ; epoch++) {    /* iterate weight updates */

        Error = 0.0 ;
		   
			for(p = 1; p<=NumPattern;p++){  /* repeat for all the training patterns */
		  
            for( j = 1 ; j <= NumHidden ; j++ ) {    /* compute hidden unit activations */
                SumH[p][j] = WeightIH[0][j] ;
                for( i = 1 ; i <= NumInput ; i++ ) {
                    SumH[p][j] += Input[p][i] * WeightIH[i][j] ;
                }
                Hidden[p][j] = 1.0/(1.0 + exp(-SumH[p][j])) ;
            }
            for( k = 1 ; k <= NumOutput ; k++ ) {    /* compute output unit activations and errors */
                SumO[p][k] = WeightHO[0][k] ;
                for( j = 1 ; j <= NumHidden ; j++ ) {
                    SumO[p][k] += Hidden[p][j] * WeightHO[j][k] ;
                }
                Output[p][k] = 1.0/(1.0 + exp(-SumO[p][k])) ;   /* Sigmoidal Outputs */
                Error += 0.5 * (Target[p][k] - Output[p][k]) * (Target[p][k] - Output[p][k]) ;   /* SSE */
                DeltaO[k] = (Target[p][k] - Output[p][k]) * Output[p][k] * (1.0 - Output[p][k]) ;   /* Sigmoidal Outputs, SSE */

            }
            for( j = 1 ; j <= NumHidden ; j++ ) {    /* 'back-propagate' errors to hidden layer */
                SumDOW[j] = 0.0 ;
                for( k = 1 ; k <= NumOutput ; k++ ) {
                    SumDOW[j] += WeightHO[j][k] * DeltaO[k] ;
                }
                DeltaH[j] = SumDOW[j] * Hidden[p][j] * (1.0 - Hidden[p][j]) ;
            }
            for( j = 1 ; j <= NumHidden ; j++ ) {     /* update weights WeightIH */
                DeltaWeightIH[0][j] = eta * DeltaH[j] + alpha * DeltaWeightIH[0][j] ;
                WeightIH[0][j] += DeltaWeightIH[0][j] ;
                for( i = 1 ; i <= NumInput ; i++ ) {
                    DeltaWeightIH[i][j] = eta * Input[p][i] * DeltaH[j] + alpha * DeltaWeightIH[i][j];
                    WeightIH[i][j] += DeltaWeightIH[i][j] ;
                }
            }
            for( k = 1 ; k <= NumOutput ; k ++ ) {    /* update weights WeightHO */
                DeltaWeightHO[0][k] = eta * DeltaO[k] + alpha * DeltaWeightHO[0][k] ;
                WeightHO[0][k] += DeltaWeightHO[0][k] ;
                for( j = 1 ; j <= NumHidden ; j++ ) {
                    DeltaWeightHO[j][k] = eta * Hidden[p][j] * DeltaO[k] + alpha * DeltaWeightHO[j][k] ;
                    WeightHO[j][k] += DeltaWeightHO[j][k] ;
                }
            }
        }
        if( epoch%100 == 0 ) fprintf(stdout, "\nEpoch %-5d :   Error = %f", epoch, Error) ;
        if( Error < 0.0001 ) break ;  /* stop learning when 'near enough' */
    }

    fprintf(stdout, "\n\nNETWORK DATA - EPOCH %d\n\nPat\t", epoch) ;   /* print network outputs */
    for( i = 1 ; i <= NumInput ; i++ ) {
        fprintf(stdout, "Input%-4d\t", i) ;
    }
    for( k = 1 ; k <= NumOutput ; k++ ) {
        fprintf(stdout, "Target%-4d\tOutput%-4d\t", k, k) ;
    }
    for( p = 1 ; p <= NumPattern ; p++ ) {
    fprintf(stdout, "\n%d\t", p) ;
        for( i = 1 ; i <= NumInput ; i++ ) {
            fprintf(stdout, "%f\t", Input[p][i]) ;
        }
        for( k = 1 ; k <= NumOutput ; k++ ) {
            fprintf(stdout, "%f\t%f\t", Target[p][k], Output[p][k]) ;
        }
    }
    fprintf(stdout, "\n\nGoodbye!\n\n") ;


    for( j = 1 ; j <= NumHidden ; j++ ) {    /* compute hidden unit activations */
        SumH[NumPattern+1][j] = WeightIH[0][j] ;
        for( i = 1 ; i <= NumInput ; i++ ) {
            SumH[NumPattern+1][j] += Input[NumPattern+1][i] * WeightIH[i][j] ;
        }
        Hidden[NumPattern+1][j] = 1.0/(1.0 + exp(-SumH[NumPattern+1][j])) ;
    }

    for( k = 1 ; k <= NumOutput ; k++ ) {    /* compute output unit activations and errors */
        SumO[NumPattern+1][k] = WeightHO[0][k] ;
        for( j = 1 ; j <= NumHidden ; j++ ) {
            SumO[NumPattern+1][k] += Hidden[NumPattern+1][j] * WeightHO[j][k] ;
        }
        Output[NumPattern+1][k] = 1.0/(1.0 + exp(-SumO[NumPattern+1][k])) ;   /* Sigmoidal Outputs */
        fprintf(stdout, "\nInputs %f %f %f %f= %f\n", Input[NumPattern+1][1], Input[NumPattern+1][2],Input[NumPattern+1][3],Input[NumPattern+1][4], Output[NumPattern+1][k]);
	}
	
	for( k = 1 ; k <= NumOutput ; k ++ ) {    /* initialize WeightHO and DeltaWeightHO */
        for( j = 1 ; j <= NumHidden ; j++ ) {
             printf(" \n WeightHO[%i][%i] = %lf\n", j, k, WeightHO[j][k]);
        }
    }

    return 1 ;
}

/*******************************************************************************/
