#include <iostream>
#include <vector>

class Grid_coordinate {
friend std::ostream& operator<<(std::ostream&, const Grid_coordinate&);
public:
	Grid_coordinate() { }
	Grid_coordinate(int, int); 
	void set(int, int);
	int& operator[] (int);
	const int& operator() (int) const;
	Grid_coordinate operator+(const Grid_coordinate&) const;
	bool operator==(const Grid_coordinate&) const;
private:
	std::pair<int, int> x;
};

class Multi_array {
public:
    Multi_array() {  }
    Multi_array(int, int);
    void clear();
    char& operator()(int, int); 
private:
    int N1, N2;
    std::vector<char> vec;
};

int sonar_pattern (Multi_array&, const Grid_coordinate&, int);
std::vector<Grid_coordinate> control_set(const Grid_coordinate&, int);
bool control_value_comparison(const std::pair<Grid_coordinate, int>& i, const std::pair<Grid_coordinate, int>& j);
int evaluate_base_policy(Multi_array&, Grid_coordinate&, int, int, int);
void iterate_DP(const Grid_coordinate&, int, int, int);
void print_array (Multi_array&, const Grid_coordinate&, int);
void print_search_pattern(const std::vector<Grid_coordinate>&, const Grid_coordinate&, int, int, int);

