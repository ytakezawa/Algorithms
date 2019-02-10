/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Yoshika Takezawa
 * Date        : 9/23/18
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

/*
 * iterates through a string, returns false if there is even one character that is not a
 * lower case letter. Returns true if
 */
bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	for (unsigned int i = 0; i< s.length(); i++){
		if (!islower(s[i])){
			return false;
		}
	}
	return true;
}

/*
 * takes advantage of the letter's binary,
 * mem = where we store the letters
 * next= shift 1<< by 97 minus letter
 * mem & next -- if we get a number >0, there is a duplicate.
 * else mem | next and
 */
bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int mem = 0;
	unsigned int next;
	for (unsigned int i =0; i<s.length(); i++){
		next = 1 << (97-s[i]);
		if((mem & next)>0) {
			return false;
		}else{
			mem = mem|next;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

	// case 1: no input args and case 2: too many inputs
	if (argc != 2){
		cerr << "Usage: " << argv[0] << " <string>";
		return 1;
	}

	//case 3 and 4: bad input's  ie: not lower case
	if(!(is_all_lowercase(argv[1]))){
		cerr << "Error: String must contain only lowercase letters.";
		return 1;
	}

	//case 5: unique letters all around
	if((is_all_lowercase(argv[1])) && (all_unique_letters(argv[1]))){
		cout << "All letters are unique.";
		return 0;
	}

	//case 6: duplicates
	if((is_all_lowercase(argv[1])) && !(all_unique_letters(argv[1]))){
		cout << "Duplicate letters found.";
		return 0;
	}
}
