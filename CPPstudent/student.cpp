/*
 * student.cpp
 * 	I pledge my honor that I have abided by the Stevens Honor System.
 *	ytakezaw
 *  Created on: Sep 7, 2018
 *      Author: Yoshika Takezawa
 */

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student {

//private variables
private:
	string first_;
	string last_;
	float gpa_;
	int id_;
//public methods
public :
	//initializer list
	Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} {}

	string full_name() const {
		return first_ + " " + last_;
	}

	int id() const{
		return id_;
	}

	float gpa() const{
		return gpa_;
	}

	void print_info() const{
		cout << full_name() << ", GPA: "
				<< fixed << setprecision(2)<< gpa()
				<< ", ID: " << id();
	}

};


	/*
	 * iterates through vector of students and if the gpa is less than 1.0, their name is added to the
	 * vector failing_students... returns failing_students vector
	 * USED mypoint.cpp's points_above_two section in the main function AS A REFERNCE/BASELINE.
	 */
vector<Student> find_failing_students(const vector<Student> &students){
	vector<Student> failing_students;
	for (const auto &student : students) {
	        if (student.gpa() < 1.0) {
	            failing_students.push_back(student);
	        }
	    }
	return failing_students;

}

/*
 * GOes through given vector from beginning to end and uses print_info() to print out
 * each student's information.
 * USED mypoint.cpp's display_points function AS A REFERENCE/BASELINE
 */
void print_students(const vector<Student> &students){
	for (auto it = students.cbegin(); it != students.cend(); ++it) {
		        it->print_info();
		        cout << endl;
		        }
}


/*
 *Allows the user to enter information for multiple student, then
 *find those students whose GPA is below 1.0 and prints them to the screen.
 */
int main(){
	//copy pasta from Canvas
	string first_name, last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;

	do {
		cout << "Enter student's first name: " ;
		cin >> first_name;
		cout << "Enter student's last name: ";
		cin >> last_name;
		gpa = -1;
		while (gpa < 0 || gpa >4){
			cout << "Enter student's GPA (0.0-4.0): ";
			cin >> gpa;
		}
		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout << "Add another student to database (Y/N)? ";
		cin >> repeat;
	}while (repeat == 'Y' || repeat == 'y');

	cout << endl << "All students:" << endl;
	print_students(students);

	cout << endl << "Failing students:";
	//TODO,, end of copy pasta from canvas
	//Print a space and the word 'None' on the same line if no students are
	//failing.
	//Otherwise, print each failing student on a separate line.

	/*
	 *gets a vector of failing_students. If the vector is empty,
	 *prints NONE
	 *if not, uses print_students() method to print failing_students vector
	 */
	if (find_failing_students(students).empty()){
		cout << " None"<< endl;
	}else {
		cout<< endl;
		print_students(find_failing_students(students));
	}

	return 0;
}

