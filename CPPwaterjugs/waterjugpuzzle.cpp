/*
 * waterjugpuzzle.cpp
 * 	I pledge my honor that I have abided by the Stevens Honor System.
 *	ytakezaw
 *  Created on: Oct 18, 2018
 *      Author: Yoshika Takezawa
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

// Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	vector<string> directions;

	State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }

	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};


/*
 * checks if all the arguments are valid inputs
 * returns false if not, returns true if otherwise
 */
bool isValid(int argc, char *argv[]){
	int x;
	istringstream iss;
	for (int i=1;i<argc; i++){
		iss.str(argv[i]);
		iss >> x;
		if (iss.fail() || (x<0) || ((x==0) && (i==3)) || ((x==0) && (i == 7))){
			//is not an integer or less than 0 or capc/goalc is 0
			cerr << "Error: Invalid ";
			if(i < 4){
				cerr << "capacity '" << argv[i] << "' for jug " ;
			}else{
				cerr << "goal '" << argv[i] << "' for jug ";
			}

			//which jug is incorrect?
			if ((i== 1)||(i==4)){
				cerr << "A.";
			}else if ((i==2)||(i==5)){
				cerr << "B.";
			}else if((i==3)||(i==6)){
				cerr << "C.";
			}
			return false;
		}
		iss.clear();
	}
	return true;
}

/*
 * singular or plural word for gallon
 */
string sp(int gal){
	if (gal ==1){
		return to_string(gal) +" gallon ";
	}
	return to_string(gal) + " gallons ";
}

/*
 * where the branching happens
 */
vector<State> create_intersection(State f, State cap){
	vector<State> output;
	int a = f.a,b = f.b,c=f.c,d;

	//Pour from C to A
	if (cap.a >=a + c){
		d=c;
	}else{
		d=(cap.a)-a;
	}
	State y(a+d, b, c-d);
	y.directions = f.directions;
	y.directions.push_back("Pour " + sp(d) + "from C to A. " + y.to_string());
	output.push_back(y);


	//Pour from B to A
	if(cap.a >= a + b){
		d=b;
	}else{
		d=(cap.a)-a;
	}
	State w(a+d, b-d, c);
	w.directions = f.directions;
	w.directions.push_back("Pour " + sp(d) + "from B to A. " + w.to_string());
	output.push_back(w);


	//Pour from C to B
	if(cap.b >= c+b){
		d=c;
	}else{
		d= (cap.b)-b;
	}
	State u(a, b+d, c-d);
	u.directions = f.directions;
	u.directions.push_back("Pour " + sp(d) + "from C to B. " + u.to_string());
	output.push_back(u);


	//Pour from A to B
	if(cap.b >= a+b){
		d=a;
	}else{
		d= (cap.b)-b;
	}
	State s(a-d,b+d,c);
	s.directions = f.directions;
	s.directions.push_back("Pour " + sp(d) + "from A to B. " + s.to_string());
	output.push_back(s);


	//Pour from B to C
	if(cap.c >= b+c){
		d=b;
	}else{
		d= (cap.c)-c;
	}
	State q(a,b-d, c+d);
	q.directions = f.directions;
	q.directions.push_back("Pour " + sp(d) + "from B to C. " + q.to_string());
	output.push_back(q);


	//Pour from A to C
	if(cap.c >= a+c){
		d=a;
	}else{
		d= (cap.c) -c;
	}
	State o(a-d, b, c+d);
	o.directions = f.directions;
	o.directions.push_back("Pour " + sp(d) + "from A to C. " + o.to_string());
	output.push_back(o);


	return output;
}


/*
 * gets the shortest path from initial state to goal state using breadth first search.
 * Since breadth first search looks at the nodes on the same level, the one that matches with the
 * goal the quickest is returned
 */
void get_directions( State cap,  State goal){

	bool **visited = new bool*[((cap.a)+1)]; // sets up boolean matrix to all false
	for (int i = 0; i<=(cap.a); i++){
		visited[i] = new bool [(cap.b)+1];
		for (int j= 0; j <=(cap.b); j++){
			visited[i][j] =false;
		}
	}
	visited[0][0] = true;

	State init(0,0,cap.c);
	queue<State> q;
	init.directions.push_back("Initial state. " + init.to_string());

	q.push(init);
	while (!q.empty()) {
		State front = q.front();
		if ((front.a == goal.a) && (front.b == goal.b) && (front.c == goal.c)) { // found goal
			q.pop();

			for (unsigned int i=0; i<front.directions.size(); i++){
				cout << front.directions[i] << endl;
			}

			for (int i= 0; i <=(cap.a); i++){
				delete[] visited[i];
			}
			delete[] visited;
			return;
		}

		//creating vector of states
		vector<State> paths= create_intersection(front, cap);
		for (unsigned int i=0; i<paths.size(); i++) {
			if (!visited[paths[i].a][paths[i].b]) { // not visited before
				visited[paths[i].a][paths[i].b] = true;
				q.push(paths[i]);
			}
		}

		q.pop();
	}

	//did not return-- is empty
	cout << "No solution.";
}


int main(int argc, char *argv[]) {

	if (argc != 7){ // if incorrect number of arguments are presented
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
		return 1;
	}
	if (!isValid(argc, argv)){
		return 1;
	}

	int cap_a = stoi(argv[1]);
	int cap_b = stoi(argv[2]);
	int cap_c = stoi(argv[3]);
	int goal_a = stoi(argv[4]);
	int goal_b = stoi(argv[5]);
	int goal_c = stoi(argv[6]);

	if(goal_a>cap_a){ // goal>cap AAAA
		cerr << "Error: Goal cannot exceed capacity of jug A.";
		return 1;
	}
	else if(goal_b>cap_b){ // goal>cap BBBB
		cerr << "Error: Goal cannot exceed capacity of jug B.";
		return 1;
	}
	else if(goal_c>cap_c){ // goal>cap CCCC
		cerr << "Error: Goal cannot exceed capacity of jug C.";
		return 1;
	}
	//checking if total goal != cap c
	if((goal_a + goal_b + goal_c) != cap_c){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
		return 1;
	}

	//valid input now
	State capacity(cap_a, cap_b, cap_c);
	State goal(goal_a, goal_b, goal_c);
	get_directions(capacity, goal);
	return 0;
}
