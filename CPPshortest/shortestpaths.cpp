/*
 * shortestpaths.cpp
 * 	I pledge my honor that I have abided by the Stevens Honor System.
 *	ytakezaw
 *  Created on: Dec 2, 2018
 *      Author: Yoshika Takezawa
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <iomanip>
#include <cstring>
//#include <ctgmath>
//#include <cmath>

//const long inf = std::numeric_limits<long>::infinity();
int vert_number;
const int INFINITY = -1;
/*
 * returns the number of digits
 */
int len(long val){
	int digits = 1;
	// snippet from stairclimber problem
	//for numbering
	while (val > 9) {
		val = val / 10;
		++digits;
	}
	return digits;
}

bool isNumber(std::string s)
{
    for (unsigned int i = 0; i < s.length(); i++){
		if (isdigit(s[i]) == false)
			return false;
    }
    return true;
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const std::string &label,
		const bool use_letters = false) {
	std::cout << label << std::endl;
	long max_val = 0;
	for (int i = 0; i < vert_number; i++) {
		for (int j = 0; j < vert_number; j++) {
			long cell = matrix[i][j];
			if (cell > INFINITY && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = len(std::max(static_cast<long>(vert_number), max_val));
	std::cout << ' ';
	for (int j = 0; j < vert_number; j++) {
		std::cout << std::setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	std::cout << std::endl;
	for (int i = 0; i < vert_number; i++) {
		std::cout << static_cast<char>(i + 'A');
		for (int j = 0; j < vert_number; j++) {
			std::cout << " " << std::setw(max_cell_width);
			if (matrix[i][j] == INFINITY) {
				std::cout << "-";
			} else if (use_letters) {
				std::cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				std::cout << matrix[i][j];
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print_path (long ** const intermediate, int i, int j){

	long cur_i = intermediate[i][j];

	if (i == j){
		return;
	}
	if (cur_i == INFINITY){//found a connection
		std::cout << " -> " << static_cast<char>(j + 'A');
		return;
	}
	print_path(intermediate, i, cur_i);
	print_path(intermediate, cur_i, j);
	return;
}


void floyd_algo(long** const matrix){
	long** path_len = new long *[(vert_number)];
	for (int i = 0; i < vert_number; i++) {
		path_len[i] = new long[vert_number];
		for (int j =0; j< vert_number; j++){
			path_len[i][j] = matrix[i][j];
		}
	}

	long ** intermediate = new long*[(vert_number)];
	for (int i = 0; i < vert_number; i++) {
		intermediate[i] = new long[vert_number];
		std::memset(intermediate[i], INFINITY, sizeof(long) * vert_number);
	}

	for(int k = 0; k<vert_number; k++){
		for (int i = 0; i < vert_number; i++) {
			for (int j = 0; j < vert_number; j++) {
				if ((k == i) || (k == j) || (i == j)
						|| (path_len[i][k] == INFINITY)
						|| (path_len[k][j] == INFINITY)) {
					continue;
				}
				long next = path_len[i][k] + path_len[k][j];
				if ((path_len[i][j] == INFINITY) || (path_len[i][j] > next)){
					path_len[i][j] = next;
					intermediate[i][j] = k;
				}else{
					continue;
				}
			}
		}
	}

	display_table(path_len, "Path lengths:");
	display_table(intermediate, "Intermediate vertices:", true);

	for (int i =0; i<vert_number; i++){
		for (int j =0; j<vert_number; j++){
			std::cout << static_cast<char>(i + 'A') << " -> "
					<< static_cast<char>(j + 'A')
					<< ", distance: ";
			if (path_len[i][j] == INFINITY){
				std::cout << "infinity, path: none" << std:: endl;
				continue;
			}else{
				std::cout << path_len[i][j] <<", path: " << static_cast<char>(i + 'A');
			}

			if (i == j){
				std::cout << std::endl;
				continue;
			}

			print_path(intermediate, i, j);
			std::cout << std::endl;
		}
	}

	//delete all matrices made
	for (int d = 0; d<vert_number; d++){
		delete [] path_len[d];
		delete []intermediate[d];
	}
	delete [] path_len;
	delete [] intermediate;
	path_len = NULL;
	intermediate = NULL;
}

int main(int argc, const char *argv[]) {
	// Make sure the right number of command line arguments exist.
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
		return 1;
	}

	// Create an ifstream object.
	std::ifstream input_file(argv[1]);
	// If it does not exist, print an error message.
	if (!input_file) {
		std::cerr << "Error: Cannot open file '" << argv[1] << "'." << std::endl;
		return 1;
	}

	// Add read errors to the list of exceptions the ifstream will handle.
	input_file.exceptions(std::ifstream::badbit);
	std::string line;
	try {
		unsigned int line_number = 1;
		// Use getline to read in a line.
		// See http://www.cplusplus.com/reference/string/string/getline/
		getline(input_file, line);
		std:: stringstream first(line);
		if (!(first >> vert_number) || (vert_number < 1)
				|| (vert_number > 26)) {
			std::cerr << "Error: Invalid number of vertices '" << line
					<< "' on line 1.";
			return 1;
		} else {
			first >> vert_number;
			line_number ++;
		}
		long ** matrix = new long*[(vert_number)];

		for (int i=0;i<vert_number;i++)
		{
		    matrix[i]=new long [vert_number];
		    std::memset(matrix[i], INFINITY, sizeof(long)*vert_number);
		}

		while (getline(input_file, line)) {
			std::stringstream stream(line);
			std::string token;
			std::vector<std::string> inputs;
			while (getline(stream, token, ' ')) {//checking number of arguments
				if (token != "") {
					inputs.push_back(token);
				}
			}
			if (inputs.size() != 3) {
				std::cerr << "Error: Invalid edge data '" << line
						<< "' on line " << line_number << ".";
				return 1;
			}

			//validating inputs
			char to;
			char from;
			long weight;

			if ((inputs[0].length() != 1) || (inputs[0].at(0) < 'A')
					|| (inputs[0].at(0) > 'A' + vert_number - 1)) {
				std::cerr << "Error: Starting vertex '" << inputs[0]
						<< "' on line " << line_number
						<< " is not among valid values A-"
						<< static_cast<char>(64 + vert_number) << ".";
				return 1;
			}
			to = inputs[0].at(0);

			if ((inputs[1].length() != 1) || (inputs[1].at(0) < 'A')
					|| (inputs[1].at(0) > 'A' + vert_number - 1)) {
				std::cerr << "Error: Ending vertex '" << inputs[1]
						<< "' on line " << line_number
						<< " is not among valid values A-"
						<< static_cast<char>(64 + vert_number) << ".";
				return 1;
			}
			from = inputs[1].at(0);

			//https://stackoverflow.com/questions/8888748/how-to-check-if-given-c-string-or-char-contains-only-digits
			if (!isNumber(inputs[2]) || stol(inputs[2]) < 1 ) {
				std::cerr << "Error: Invalid edge weight '" << inputs[2] << "' on line " << line_number << ".";
				return 1;
			}

			weight = stol(inputs[2]);
			if (weight == 0 && inputs[2][0] != '0'){

			}
			matrix[to - 'A'][from - 'A'] = weight;

			inputs.clear();
			++line_number;
		}
		for (int i = 0; i < vert_number; i++) {		// self loops = 0
			for (int j = 0; j < vert_number; j++) {
				if (i == j) {
					matrix[i][j] = 0;
				}
			}
		}
		display_table(matrix, "Distance matrix:", false);
		floyd_algo(matrix);

		for (int d = 0; d<vert_number; d++){
			delete[] matrix[d];
		}
		delete[] matrix;
		matrix = NULL;
		// Don't forget to close the file.
		input_file.close();
	} catch (const std::ifstream::failure &f) {
		std::cerr << "Error: Cannot open file '" << argv[1] << "'.";
		return 1;
	}


	return 0;
}
