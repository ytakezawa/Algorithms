/*
 * gcd.cpp
 *	I pledge my honor that I have abided by the Stevens Honor System.
 *	ytakezaw
 *  Created on: Aug 31, 2018
 *      Author: Yoshi
 */


#include <iostream>
#include <sstream>

using namespace std;

int gcd_iterative(int m, int n){
	m = abs(m); // can do this before cout in main
	n= abs(n);
	int r;
	while (n!=0){
		r = m%n;
		m=n;
		n=r;
	}
	return m;
}

int gcd_recursive(int m, int n){
	m = abs(m);
	n= abs(n);
	if (n == 0){
		return m;
	}
	return gcd_recursive(n, m%n);
}

int main(int argc, char *argv[]){
	int m, n;
	if (argc != 3){
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	istringstream iss;
	iss.str(argv[1]);
	if(!(iss >> m)){
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if(!(iss >> n)){
			cerr << "Error: The second argument is not a valid integer." << endl;
			return 1;
	}
	cout << "Iterative: gcd(" << m <<", " << n << ") = " << gcd_iterative(m,n) << endl;
	cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m,n) << endl;

}
