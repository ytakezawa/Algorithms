/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Yoshika Takezawa
 * Date        : 9/12/18
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
        sieve();
        count_num_primes();
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
        // TODO: write code to display the primes in the format specified in the
        // requirements document.
    	const int max_prime_width = num_digits(max_prime_);
    	const int primes_per_row = 80/(max_prime_width +1);
    	int count = 0; // number of primes on current row
    	int spaces; // number of spaces to be displayed

    	if (num_primes() <= primes_per_row){ // single line output <80 charas
    		for (int i = 2; i <= limit_; i++){
    			if (is_prime_[i] == true){
    				if (count ==0){
    					cout << i;
    				}else{
    					cout <<" "<< i;
    				}
    				count ++;
    			}
    		}
    	}else{ // multi-lined output
    		for (int i = 2; i<= limit_; i++){
    		    if (is_prime_[i] == true){
    		    	if (count == primes_per_row){ //enters a new row
    		    		count =0;
    		    		cout << endl;
    				}
    		    	spaces = (max_prime_width - num_digits(i)) ;
    		   		for (int j = 0; j<spaces; j++){ // prints spaces
    		    		cout << " ";
    		    	}
    		    	if (count == 0){
    		    		cout << i;
    		    	}else{
    		    		cout <<" "<< i; // prints the prime number
    		    	}
    		    	count ++;
    		   	}
    		}
    	}


    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    /*
     *iterates through is_prime_ and adds one to numprimes for each true item
     *also assigns maxprime to the last index it reaches.
     *finds max prime, EXECUTE THIS FIRST BEFORE display_primes()
     */
    int count_num_primes()  {
        // TODO: write code to count the number of primes found
    	num_primes_ =0;
    	for (int i= 2; i<= limit_; i++){
    		if (is_prime_[i] == true){
    			num_primes_ ++;
    			max_prime_ = i;
    		}
    	}
    	return num_primes_;
    }


    /*
     * finds the number of digits by dividing the num by 10 until it is < 1 and > 0.
     * the number of times it divides is the number of digits.
     */
    int num_digits(int num) const {
        // TODO: write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
    	int counter = 0;
    	//the input doesn't allow anything less than 2, so we do not have to worry about those cases.
    	while (num >=1){
    		num = num/10;
    		counter++;
    	}
    	return counter;
    }

    /*
     * the indeces are the value.
     * boolean array is initially all true
     * iterates from 2 to sqrt(limit)
     * if there is a true value, changes multiples from i^2 to limit to false
     */
    void sieve() {
        // TODO: write sieve algorithm
    	for (int x =0; x<=limit_; x++){
    		is_prime_[x] = true;
    	}
    	for (int i = 2; i<= sqrt(limit_); i++){
    		if (is_prime_[i] == true){
    			for (int j= pow(i,2); j<= limit_; j+=i){
    				is_prime_[j] =false;
    			}
    		}
    	}
    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve a(limit);
    cout <<endl << "Number of primes found: " << a.num_primes()<< endl;
    cout << "Primes up to " << limit << ":" << endl ;
    a.display_primes();

    return 0;
}
