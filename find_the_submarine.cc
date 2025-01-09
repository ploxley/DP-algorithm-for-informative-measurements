#include "find_the_submarine.h"
#include <algorithm>
#include <stdexcept>

std::ostream& operator<<(std::ostream& output, const Grid_coordinate& x)
{
	output << "(" << x(0) << "," << x(1) << ")";

	return output;
}

Grid_coordinate::Grid_coordinate(int a, int b) 
{ 
	x.first = a; x.second = b;
}

void Grid_coordinate::set(int a, int b)
{
	x.first = a, x.second = b;
}

int& Grid_coordinate::operator[] (int i)
{	
	if (i == 0)
		return x.first;
	else
		return x.second;
}

const int& Grid_coordinate::operator() (int i) const
{	
	if (i == 0)
		return x.first;
	else
		return x.second;
}

Grid_coordinate Grid_coordinate::operator+(const Grid_coordinate& y) const
{
	Grid_coordinate z;

	z[0] = x.first + y(0);
	z[1] = x.second + y(1);

	return z;
} 

bool Grid_coordinate::operator==(const Grid_coordinate& y) const
{
	return (x.first == y(0) && x.second == y(1));
}

Multi_array::Multi_array(int a, int b) 
{
    N1 = a, N2 = b; 
    vec = std::vector<char>(N1*N2, 'O'); // initialized to zero
}

void Multi_array::clear()
{
	vec.clear();
	vec = std::vector<char>(N1*N2, 'O');
}

char& Multi_array::operator()(int n1, int n2)
{ 
    return vec.at(n1 + N1*n2); // column-major indexing
}

int sonar_pattern (Multi_array& A, const Grid_coordinate& x, int n)
{
	// Form the sonar pattern on grid given position x
	// Takes into account edges of grid at 0 and n
	// Only new squares are searched
	// Coordinates for x start at top-left

	// Count number of assignments made
	int counter = 0;	

	// First check x is on the grid
	if (x(0) < 0 || x(0) > n - 1 || x(1) < 0 || x(1) > n - 1)
		throw std::invalid_argument("position must be on the grid");
	
	if (A(x(0),x(1)) == 'O') {
		A(x(0), x(1)) = 'X';
		++counter;
	}
	if (x(0) - 1 >= 0 && A(x(0) - 1,x(1)) == 'O') {
		A(x(0) - 1, x(1)) = 'X';
		++counter; 
	}
	if (x(0) + 1 < n && A(x(0) + 1,x(1)) == 'O') {
		A(x(0) + 1, x(1)) = 'X';
		++counter; 
	}
	if (x(1) - 1 >= 0 && A(x(0),x(1) - 1) == 'O') {
		A(x(0), x(1) - 1) = 'X';
		++counter;
	}
	if (x(1) + 1 < n && A(x(0),x(1) + 1) == 'O') {
		A(x(0), x(1) + 1) = 'X';
		++counter;
	}

	return counter;
}

std::vector<Grid_coordinate> control_set(const Grid_coordinate& x, int n)
{
	// Returns a list of admissible controls (ones that are on the grid)
	std::vector<Grid_coordinate> admissible_controls;

	// First check x is on the grid
	if (x(0) < 0 || x(0) > n - 1 || x(1) < 0 || x(1) > n - 1)
		throw std::invalid_argument("position must be on the grid");

	// Now find valid controls from diagonal and cartesian moves:
	// Check cartesian moves x 4
	if (x(0) - 2 >= 0) {
		Grid_coordinate control(- 2, 0);
		admissible_controls.push_back(control);
	}
	if (x(0) + 2 < n) {
		Grid_coordinate control(2, 0);
		admissible_controls.push_back(control);
	}
	if (x(1) - 2 >= 0) {
		Grid_coordinate control(0, - 2);
		admissible_controls.push_back(control);
	}
	if (x(1) + 2 < n) {
		Grid_coordinate control(0, 2);
		admissible_controls.push_back(control);
	}

	// Check diagonal moves x 4
	if (x(0) - 1 >= 0 && x(1) - 1 >= 0) {
		Grid_coordinate control(- 1, - 1);
		admissible_controls.push_back(control);
	}
	if (x(0) + 1 < n && x(1) - 1 >= 0) {
		Grid_coordinate control(1, - 1);
		admissible_controls.push_back(control);
	}
	if (x(0) - 1 >= 0 && x(1) + 1 < n) {
		Grid_coordinate control(- 1, 1);
		admissible_controls.push_back(control);
	}
	if (x(0) + 1 < n && x(1) + 1 < n) {
		Grid_coordinate control(1, 1);
		admissible_controls.push_back(control);
	}

	return admissible_controls;
}

void print_array (Multi_array& A, const Grid_coordinate& x, int n)
{
	A(x(0), x(1)) = 'S';	
	for (int j = 0; j != n; ++j) {
		for (int i = 0; i != n; ++i) {
			std::cout << A(i,j) << " ";
		}
		std::cout << std::endl;
	}
	A(x(0), x(1)) = 'X';
}

void print_search_pattern(const std::vector<Grid_coordinate>& stored_controls, 
const Grid_coordinate& initial_condition, int n, int N, int rollout)
{
	Multi_array A(n,n);
	int u, sum_u = 0;
	std::vector<int> keep_u;
	std::vector<int>::const_iterator keep_u_it;
	std::vector<Grid_coordinate>::const_iterator it;
	Grid_coordinate xprime;
	
	if (rollout == 1)
		std::cout << "Printing OPTIMAL search pattern..." << std::endl;
	else
		std::cout << "Printing GREEDY search pattern..." << std::endl;
	xprime = initial_condition;
	u = sonar_pattern(A, xprime, n);
	keep_u.push_back(u);
	sum_u += u;
	print_array(A, xprime, n);
	std::cout << "current measurement = " << u << std::endl;

	for (it = stored_controls.begin(); it != stored_controls.end(); ++it) {
		std::cout << "take control = " << *it << std::endl;
		xprime = xprime + *it;
		u = sonar_pattern(A, xprime, n);
		keep_u.push_back(u);
		sum_u += u;
		print_array(A, xprime, n);
		std::cout << "current measurement = " << u << std::endl;
	}
	std::cout << "measurement sequence: "; 
	for (keep_u_it = keep_u.begin(); keep_u_it != keep_u.end(); ++keep_u_it) {
		std::cout << *keep_u_it << " ";
	}
	std::cout << std::endl;
	std::cout << "number of measurements = " << N << std::endl;
	std::cout << "squares searched = " << sum_u << " of " << (n*n)-1 << std::endl;
}

bool control_value_comparison(const std::pair<Grid_coordinate, int>& i, const std::pair<Grid_coordinate, int>& j)
{
	return i.second < j.second;
}

int evaluate_base_policy(Multi_array& A, Grid_coordinate& xprime, int n, int N_m_k, int u_value)
{
	// Base policy is one-step lookahead with greedy measurement value u

	int u, sum_u;
	Multi_array current_A;
	Grid_coordinate uprime, current_xprime;
	std::vector<Grid_coordinate> admissible_controls;
	std::vector<Grid_coordinate>::const_iterator it; 
	std::vector<std::pair<Grid_coordinate, int> > stored_control;
	std::vector<std::pair<Grid_coordinate, int> >::const_iterator result;
	std::pair<Grid_coordinate, int> control_value;

	sum_u = u_value;

	// Evaluate base policy as loop over N - k remaining measurements
	for (int k = 0; k != N_m_k; ++k) {
		current_xprime = xprime; 
		current_A = A;

		// Consider all admissible controls from this state
		admissible_controls = control_set(xprime, n);

		// Update state and measurement value for each admissible control
		for (it = admissible_controls.begin(); it != admissible_controls.end(); ++it) {
			xprime = xprime + *it;
			u = sonar_pattern(A, xprime, n);
			control_value.first = *it;
			control_value.second = u;
			stored_control.push_back(control_value);  
			xprime = current_xprime;		// initialize xprime and A for next loop
			A = current_A;			
		}

		// Choose maximum u
		result = std::max_element(stored_control.begin(), stored_control.end(), control_value_comparison);
		u = result->second;
		uprime = result->first;
		stored_control.clear();

		// Choose control and move to next state
		xprime = xprime + uprime;
		u = sonar_pattern(A, xprime, n);
		sum_u += u;
	}	
	return sum_u;
}

void iterate_DP(const Grid_coordinate& initial_condition, int n, int N, int rollout)
{
	Grid_coordinate xprime, current_xprime, uprime;
	Multi_array A(n,n), current_A;
	int u, u_total, u_value;
	std::vector<Grid_coordinate> admissible_controls, stored_controls;
	std::vector<Grid_coordinate>::const_iterator it;
	std::vector<std::pair<Grid_coordinate, int> > stored_control;
	std::vector<std::pair<Grid_coordinate, int> >::const_iterator result;
	std::pair<Grid_coordinate, int> control_value;

	xprime = initial_condition;

	// Iterate DP as loop over N
	for (int k = 1; k != N; ++k) { 
		// Find measurement value given by u (the number of searched squares)
		u = sonar_pattern(A, xprime, n);
		current_xprime = xprime; 
		current_A = A;

		// Consider all admissible controls from this state
		admissible_controls = control_set(xprime, n);

		// Update state and measurement value for each admissible control
		for (it = admissible_controls.begin(); it != admissible_controls.end(); ++it) {
			xprime = xprime + *it;
			u_value = sonar_pattern(A, xprime, n);
			if (rollout == 1) {
				u_total = evaluate_base_policy(A, xprime, n, N-k, u_value);
			}
			else
				u_total = u_value;	
			control_value.first = *it;
			control_value.second = u_total;
			stored_control.push_back(control_value);
			xprime = current_xprime;	// initialize xprime and A for next loop
			A = current_A;
		}

		// Choose maximum u
		result = std::max_element(stored_control.begin(), stored_control.end(), control_value_comparison);
		u_total = result->second;
		uprime = result->first;
		stored_control.clear();

		// Choose control and move to next state
		xprime = xprime + uprime;
		stored_controls.push_back(uprime);
	}
	
	print_search_pattern(stored_controls, initial_condition, n, N, rollout);
}
