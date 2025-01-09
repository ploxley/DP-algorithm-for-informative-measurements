#include "find_the_submarine.h"

int main()
{
	Grid_coordinate xprime, initial_condition;
	
	int N = 4;						// number of measurements
	int n = 3;						// grid size is n x n
	int rollout = 1;				// rollout = 1, greedy = 0;
	xprime.set(1,1);				// initial condition
	initial_condition = xprime;
	
	iterate_DP(initial_condition, n, N, rollout);

	return 0;
}
