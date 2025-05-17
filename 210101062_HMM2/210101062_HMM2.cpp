// 210101062_HMM2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

#define M 32	//Number of observation symbols per state
#define N 5		//Number of states
const int MAX_T = 160;		//Maximum number of observations

//Model parameters A, B and Pi
long double A[N+1][N+1] = {0};
long double B[N+1][M+1] = {0};
long double Pi[N+1] = {0};

int T=1;			//Number of observations
long double delta[MAX_T+1][N+1];	//P(qT= Si, O | lambda)
int psi[MAX_T+1][N+1];
int q_star[MAX_T+1];	//Optimal state sequence
int O[MAX_T+1];			//Observation sequence
long double p_star = 0;

//Function to find the single best state sequence for the given observation sequence
void viterbiAlgorithm(){
    for(int i=1; i<=N; i++){			//Initialization
        delta[1][i] = Pi[i] * B[i][O[1]];
        psi[1][i] = 0;
    }

	for(int j=1; j<=N; j++){			//Induction
		for(int t=2; t<=T; t++){
            long double maxVal = 0, temp = 0;
            int index = 0;
            for(int i=1; i<=N; i++){
                temp = (delta[t-1][i] * A[i][j]);
                if(temp > maxVal){
					maxVal = temp;
					index = i;
				}
            }
            delta[t][j] = maxVal * B[j][O[t]];
			psi[t][j] = index;
        }
    }

    long double max = 0;
    for(int i=1; i<=N; i++){			//Termination
        if(delta[T][i] > max) {
			max = delta[T][i];
			q_star[T] = i;
		}
        p_star = max;
    }

    for(int t=T-1; t>0; t--){			//Path (state sequence) backtracking
        q_star[t] = psi[t+1][q_star[t+1]];
    }
}

int main(){
	FILE *f1 = NULL;    // Read the data from the input file.
	double x;
    int err = fopen_s(&f1, "Files/Initial_Model.txt", "r");
    if(err != NULL)     //error handling for file opening
    {
        printf("\nCannot open the file\n");
        system("pause");
        exit(1);
    }

	int count = 0; 
	int i=1, j=1;
	while( !feof(f1) )
	{
		if( fscanf_s( f1, "%lf", &x) == 1)
		{
			if(count<25){
				A[i][j] = x;
				j++;
				if(j==N+1){
					i++,j=1;
					if(i==N+1) i=1,j=1;
				}
				count++;
			}
			else if(count<185){
				B[i][j] = x;
				j++;
				if(j==M+1){
					i++,j=1;
					if(i==N+1) i=1,j=1;
				}
				count++;
			}
			else{
				Pi[i]=x;
				i++;
			}
		}
		else{
			char lines[500];
			fgets(lines, 500, f1);
		}
	}
	fclose(f1);

	FILE* f2= fopen("Files/HMM_OBSERVATION_SEQUENCE_1.txt","r");
    while( !feof(f2) )
	{
		if( fscanf_s( f2, "%lf", &x) == 1){
			O[T++]=x;
		}
	}
	fclose(f2);
	T--;

	viterbiAlgorithm();
	for(int i=1; i<=N; i++){
		for(int j=1; j<=T; j++){
			//cout<<delta[j][i]<<"    ";
		}
		//cout<<"\n\n";
	}

	for(int j=1; j<=T; j++){
		cout<<q_star[j]<<"    ";
	}
	return 0;
}

