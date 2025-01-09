# Code for "A Dynamic Programming Algorithm for Finding an Optimal Sequence of Informative Measurements" <br> [doi 10.3390/e25020251](https://www.mdpi.com/1099-4300/25/2/251)

This code reproduces the figures and tables in the journal article "A Dynamic Programming Algorithm for Finding an Optimal Sequence of Informative Measurements". To run this code requires a `C/C++` compiler such as `GCC`. Download a snapshot of the repository's files as a zip file to your local computer, and then unpack the zip file. Reproducing the paper figures is done as follows.

## Running the Code
All figure and table results can be obtained by editing the file `main.cc` on lines 7 to 10. Once this file has been edited, the code can be compiled by typing `make` on the command line (assuming a `C++` compiler is available). To run the code, type `./main` on the command line. Alternatively, an IDE can be used to build and run the code.

## Reproducing the Figure and Table Results

**Figure 3:** In file `main.cc` make the following edits, <br><br>
`int N = 4;` <br>
`int n = 3;` <br>
`int rollout = 1;` <br>
`xprime.set(1,1);`<br> <br>
then compile and run the code as described. 

The figure results are displayed on the terminal. The position of the ship is given by "S", a square that has been searched is denoted by an "X", and a square that has not yet been searched is denoted by an "O". 

Other results displayed on the terminal include the current measurement (number of squares searched at the current stage), the final measurement sequence (given in each figure caption), and the sum of all measurements (number of squares searched over all stages). To be successful at finding the submarine, all squares minus one need to have been searched (it must be in the remaining unsearched square if it has not been found at the final stage).

The search can be chosen to be either a greedy search (`rollout = 0`), or a search using the rollout algorithm (`rollout = 1`) -- which is a particular method of approximate dynamic programming. Each measurement corresponds to a number of squares that have been searched by the ship using a regular sonar pattern. 

**Figure 4:** <br><br> In file `main.cc` make the following edits, <br><br>
`int N = 3;` <br>
`xprime.set(0,1);`<br> <br>
then compile and run the code as described. Note the precise order of the search depends on the order the admissible controls are processed. 

**Figure 5:** <br><br> In file `main.cc` make the following edits, <br><br>
`int N = 4;` <br>
`xprime.set(0,0);`<br> <br>
then compile and run the code as described.

**Figure 6:** In file `main.cc` make the following edits, <br><br>
`int N = 7;` <br>
`int n = 4;` <br>
`xprime.set(1,1);`<br> <br>
then compile and run the code as described. Note that Figures 1 to 6 could instead use `rollout = 0` since greedy search is optimal until `n = 7`.

**Figure 7:** In file `main.cc` make the following edits, <br><br>
`int N = 20;` <br>
`int n = 7;` <br>
`int rollout = 0;` <br>
`xprime.set(1,0);`<br> <br>
then compile and run the code as described. The last three grids correspond to Figure 7. Increasing to `N = 27` shows the ship moving from left to right in an endless cycle without completing the search: greedy search is no longer optimal.

**Figure 8:** In file `main.cc` make the following edits, <br><br>
`int N = 23;` <br>
`int rollout = 1;` <br> <br>
then compile and run the code as described. In the terminal output count back six grids, then five, and then four. These three grids match Figure 8. 

**Table 2:** In file `main.cc` edit `n` and `N` according to the values for "Grid Size" and "Number of Measurements" given in the table. You will need to compile and run the code for each row of the table. For example, for the last row of the table, the following edits 
<br><br>
`int N = 98;` <br>
`int n = 14;` <br>
`int rollout = 1;` <br>
`xprime.set(1,0);`<br> <br>
produce the terminal output: `squares searched = 195 of 195`. While setting `rollout = 0` yields: "squares searched = 164 of 195". Results for these relatively small grids are still somewhat sensitive to the initial condition specified in `xprime.set()`.