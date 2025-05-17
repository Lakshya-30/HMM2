-------------------------------------- CS566 ASSIGNMENT 6------------------------------------------------
NAME: Lakshya Onkara
ROLL NO.: 210101062

AIM: Solution to HMM problem-2
EXECUTION: Build and run the code on Visual Studio 2010. Use F5 key to run the code.

INPUT: Initial_Model.txt, HMM_OBSERVATION_SEQUENCE_1.txt
OUTPUT: Optimal state sequence given the observation sequence and the model lambda.

CONSTANTS:
1. M: The number of observation symbols per state (32)
2. N: The number of states (5)
3. MAX_T: Maximum number of observations (160)

VARIABLES:
1. A[N+1][N+1]: Array to store the state transition probability distribution.
2. B[N+1][M+1]: Array to store the observation symbol probability distribution.
3. Pi[N+1]: Array to store the initial state distribution.
4. T: Variable to store number of observations
5. delta[MAX_T+1][N+1]: Array to store the best score along a single path, at time t, which accounts for the first t observations and ends in state i.
6. psi[MAX_T+1][N+1]: Array to keep track of the argument that maximized delta[t+1][j] for each t and j.
7. q_star[MAX_T+1]: Array to store the optimal state sequence.
8. O[MAX_T+1]: Array to store the observation sequence.
9. p_star: long double to store the solution of problem-2.


FUNCTIONS:
1. viterbiAlgorithm():
	Function to find the single best state sequence for the given observation sequence.
	

PROCEDURE:
1. Read the input files and populate the A, B, Pi and O arrays.
2. Call the viterbiAlgorithm function.