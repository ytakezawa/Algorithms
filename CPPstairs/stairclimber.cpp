/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Yoshika Takezawa
 * Date        : 10/3/18
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      :I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways;
	vector<vector<int>> result;
	if (num_stairs <= 0){				//returns <<>>
		ways.push_back(vector<int>());
	}else{
		for (int i = 1; i<=3; i++){		// iterates from 1 to 3 steps at a time
			if (num_stairs >= i){
				result = get_ways(num_stairs-i);

				// the following's pseudocode is: for r in result do: r.append(i)
				// english: for each individual way, append the iterating i
				for (unsigned int r= 0; r<result.size(); r++){
					result[r].insert(result[r].begin(),i);
				}
				ways.insert(ways.end(), result.begin(), result.end()); //https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector
			}
		}
	}
	return ways;
}


void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int highest = ways.size();
	int spaces = 1;
	while (highest >9){ 		// gets number of spaces, from the sieve problem
		highest = highest/10;
	    spaces++;
	}

	for (unsigned int i =0; i< ways.size(); i++){ // printing rows
		cout << setw(spaces) << i+1 << ". [";
		for(unsigned int j = 0; j<ways.at(i).size(); j++) { // printing individual steps
			cout << ways.at(i).at(j);
			if (j!=ways.at(i).size()-1){
				cout << ", ";
			}
		}
		cout << "]\n"; // better than endl
	}
}

int main(int argc, char * argv[]) {
	//case 1,2 no inputs, too many inputs

	//cin.tie(NULL); bros used it??
	//ios_base::sync_with_stdio(false); speed up algo

	if (argc != 2){
		cerr << "Usage: " << argv[0] << " <number of stairs>";
		return 1;
	}

	//case 3,4 not positive integers
	int m;
	istringstream iss;
	iss.str(argv[1]);
	if ((!(iss >> m)) || m<=0){
		cerr << "Error: Number of stairs must be a positive integer.";
		return 1;
	}
	iss.clear();

	//case 5: valid
	if (get_ways(m).size() ==1 ){
		cout << "1 way to climb 1 stair."<< endl;
	}else{
		cout << get_ways(m).size() << " ways to climb " << m << " stairs." << endl;
	}

	display_ways(get_ways(m));
}
