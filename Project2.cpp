//----------------------------------------------------------------
// CS215-402 Project 2
//----------------------------------------------------------------
// Author: Gavin Crain
// Date: 3/15/2020
// Description: Tool for teachers to keep track of students 
//----------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int maxStudents = 5;
const int maxScores = 5;
const string validOptions = "ADNVEPSX";

struct score {
	int possible;
	int made;
};

struct students {
	int studentID;
	string firstName, lastName;
	int numScores;
	score sc[maxScores];
};

void init(students s[maxStudents], int& num) {
	for (int i = 0; i < num; i++) {

		s[i].studentID = 0;
		s[i].firstName = "";
		s[i].lastName = "";
		for (int j = 0; j < s[i].numScores; j++) {
			s[i].sc[j].made = 0;
			s[i].sc[j].possible = 0;
		}
		s[i].numScores = 0;
	}
	num = 0;
}

void load(students s[maxStudents], int& num) {
	ifstream fin;
	fin.open("grades.txt");
	if (fin.fail()) {
		// assume a new class is being started 
		num = 0;
	}
	else {
		// fill structure with student info 
		fin >> num;
		for (int i = 0; i < num; i++) {
			fin >> s[i].studentID;
			fin >> s[i].firstName;
			fin >> s[i].lastName;
			fin >> s[i].numScores;
			for (int j = 0; j < s[i].numScores; j++) {
				fin >> s[i].sc[j].made >> s[i].sc[j].possible;
			}
		}

	}
}

void write(students s[maxStudents], int num) {
	ofstream fout;
	fout.open("gradesout.txt");
	if (fout.fail()) {
		cout << "Unable to open output file.\n";
	}
	else {
		fout << num << endl;
		for (int i = 0; i < num; i++) {
			fout << s[i].studentID << " ";
			fout << s[i].firstName << " ";
			fout << s[i].lastName << " ";
			fout << s[i].numScores << " ";
			for (int j = 0; j < s[i].numScores; j++) {
				fout << s[i].sc[j].made << " " << s[i].sc[j].possible << " ";
			}
			fout << endl;
		}
	}
}

void displayLogo() {
	cout << endl;
	cout << "+" << "--------------------------------------------------" << "+" << endl;
	cout << "|" << "                 " << "THE SUPER GRADER" << "                 " << "|" << endl;
	cout << "|" << "                  " << "by Gavin Crain" << "                  " << "|" << endl;
	cout << "+" << "--------------------------------------------------" << "+" << endl;
	cout << left << setfill(' ') << setw(25) << "A - Add Student" << "D - Drop Student" << endl;
	cout << left << setw(25) << "V - View Student" << "P - Print class" << endl;
	cout << left << setw(25) << "S - Sort by Avg" << "N - Sort by name" << endl;
	cout << left << setw(25) << "E - Enter new scores" << "X - Exit" << endl;
}

char getOption() {
	string option;
	char opt;
	int b = 5;
	while (b > 1) {
		cout << "Enter option: ";
		if (cin.peek() == '\n') cin.ignore();
		getline(cin, option);
		opt = toupper(option[0]);
		int found = validOptions.find(opt);
		if (found == -1) {
			cout << "Invalid option. Choose one of ADNVEPSX" << endl;

		}
		else if (found == 0) {
			opt = 'A';
			b = 0;
		}
		else if (found == 1) {
			opt = 'D';
			b = 0;
		}
		else if (found == 2) {
			opt = 'N';
			b = 0;
		}
		else if (found == 3) {
			opt = 'V';
			b = 0;
		}
		else if (found == 4) {
			opt = 'E';
			b = 0;
		}
		else if (found == 5) {
			opt = 'P';
			b = 0;
		}
		else if (found == 6) {
			opt = 'S';
			b = 0;
		}
		else if (found == 7) {
			opt = 'X';
			b = 0;
		}
	}
	return opt;
}

void addStudent(students s[maxStudents], int& num) {
	if (num == 5) {
		cout << "No more students may be added" << endl;
	}
	else {
		cout << "Enter student ID number:   ";
		cin >> s[num].studentID;
		cout << "Enter first and last name: ";
		cin >> s[num].firstName;
		cin >> s[num].lastName;
		int b = 0;
		while (b < 1) {
			cout << "Enter number of scores:    ";
			cin >> s[num].numScores;
			if (s[num].numScores <= 5 && s[num].numScores > 0) {
				b = 5;
			}
			else {
				cout << "Invalid number of scores!" << endl; 
			}
		}
		for (int i = 0; i < s[num].numScores; i++) {
			cout << "Enter score " << i + 1 << " (made poss): ";
			cin >> s[num].sc[i].made;
			cin >> s[num].sc[i].possible;
		}
		cout << "New student added." << endl;
		num = num + 1;
	}
	system("pause");
}

int search(students s[], int id, int num) {
	int found = -1;
	for (int i = 0; i < num; i++) {
		if (s[i].studentID == id) {
			found = i;
		}
	}
	return found;
}

int findStudent(students s[], int num) {
	int i;
	int id;
	cout << "Enter student id number: ";
	cin >> id;
	i = search(s, id, num);

	if (i == -1) {
		cout << "Student id " << id << " not found!" << endl;
	}
	return i;
}

students removeStudent(int i, students s[], int& num) {
	students f;
	num = num - 1;
	f = s[i];
	
	//moves students into the new empty spot
	for (int j = i; j < num; j++) {
		s[j] = s[j + 1];
	}
	return f;
}

void dropStudent(students s[], int& num) {
	int f;
	f = findStudent(s, num);
	students stu;
	if (f >= 0) {
		stu = removeStudent(f, s, num);
		cout << stu.firstName << " " << stu.lastName << " dropped. " << endl;
	}
	system("pause");
}

double getAvg(score sc[]) {
	double avgscore = 0;
	double made = 0;
	double possible = 0;
	int b = 0;
	while (sc[b].made >= 0) {
		made = made + sc[b].made;
		possible = possible + sc[b].possible;
		b = b + 1;
	}

	avgscore = (made / possible) * 100.0;
	return avgscore;
}

char getGrade(double avgscore) {
	char grade;
	if (avgscore >= 90) {
		grade = 'A';
	}
	else if (avgscore >= 80) {
		grade = 'B';
	}
	else if (avgscore >= 70) {
		grade = 'C';
	}
	else if (avgscore >= 60) {
		grade = 'D';
	}
	else {
		grade = 'E';
	}
	return grade;
}

void viewStudent(students s[], int num) {
	int f = findStudent(s, num);
	if (f > -1) {
		double avg = getAvg(s[f].sc);
		char grade = getGrade(avg);
		cout << left << setw(6) << "ID:" << s[f].studentID << "  Name:  " << s[f].lastName + ", " + s[f].firstName << endl;
		cout << left << setw(6) << "Avg:" << setprecision(3) << avg << "  Grade: " << grade << endl;
		cout << "Number of scores:  " << s[f].numScores << endl;
		cout << left << setw(19) << "Scores:";
		for (int i = 0; i < s[f].numScores; i++) {
			cout << s[f].sc[i].made << "/" << s[f].sc[i].possible << " ";
		}
		cout << endl;
	}
	system("pause");
}

void swap(students s[], int i, int j) {
	students temp = s[i];
	s[i] = s[j];
	s[j] = temp;
}

void sortByName(students s[], int num) {
	string sort[maxStudents];
	for (int i = 0; i < num; i++) {
		string first = s[i].firstName;
		string last = s[i].lastName;
		sort[i] = last + first;
	}
	for (int i = 0; i < num; i++) {
		for (int j = i + 1; j < num; j++) {
			if (sort[i] < sort[j]) {
				swap(s, i, j);
			}
		}
	}
	cout << "Class sorted by name." << endl;
	system("pause");
}

void sortByAvg(students s[], int num) {
	double avg[maxScores];
	score sc[maxScores];
	for (int i = 0; i < num; i++) {
		avg[i] = getAvg(s[i].sc);
	}
	for (int i = 0; i < num; i++) {
		for (int j = i + 1; j < num; j++) {
			if (avg[i] < avg[j]) {
				swap(s, i, j);
				double avgTemp = avg[i];
				avg[i] = avg[j];
				avg[j] = avgTemp;
			}
		}
	}
	cout << "Class sorted by Average" << endl;
	system("pause");
}

void enterScore(students s[], int num) {
	sortByName(s,num);
	int newPoss;
	cout << "Enter points possible for this assignment: ";
	cin >> newPoss;
	cout << "Enter points made for each student: " << endl;
	for (int i = 0; i < num; i++) {
		cout << s[i].studentID << " " << left << setw(25) << s[i].lastName + ", " + s[i].firstName;
		if (s[i].numScores == 5) {
			cout << "Max scores exceeded!" << endl;
		}
		else {
			cin >> s[i].sc[s[i].numScores].made;
			s[i].sc[s[i].numScores].possible = newPoss;
			s[i].numScores = s[i].numScores + 1;
		}
	}
	system("pause");
}

void printReport(students s[], int num) {
	double avg[maxStudents];
	char gr[maxStudents];
	for (int i = 0; i < num; i++) {
		avg[i] = getAvg(s[i].sc);
	}

	for (int i = 0; i < num; i++) {
		gr[i] = getGrade(avg[i]);
	}

	cout << left << setw(6) << " ID" << setw(21) << "Name" << setw(6) << "Avg" << setw(4) << "Grd" << setw(40) << "Scores" << endl;
	cout << setfill('-') << setw(5) << " " << setw(21) << " " << setw(6) << " " << setw(4) << " " << setw(41) << " " << endl;
	cout << setfill(' ');
	for (int i = 0; i < num; i++) {
		
		cout << " " << s[i].studentID << " ";
		cout << left << setw(20) << s[i].lastName + ", " + s[i].firstName << " ";
		cout << setprecision(3) << avg[i] << "  ";
		cout << " " << gr[i] << "  ";
		for (int j = 0; j < s[i].numScores; j++) {
			cout << s[i].sc[j].made << "/" << setw(3) << right << s[i].sc[j].possible << "  ";
		}
	cout << endl;
	}
	system("pause");
}

int main() {
	score sc[maxScores];
	students s[maxStudents];
	int numStudents = 0;
	int b = 0;
	init(s, numStudents);
	load(s, numStudents);
	while (b < 1) {
		displayLogo();
		char k = getOption();
		if (k == 'A') {
			addStudent(s, numStudents);
		}
		if (k == 'V') {
			viewStudent(s, numStudents);
		}
		if (k == 'S') {
			sortByAvg(s, numStudents);
		}
		if (k == 'E') {
			enterScore(s, numStudents);
		}
		if (k == 'D') {
			dropStudent(s, numStudents);
		}
		if (k == 'P') {
			printReport(s, numStudents);
		}
		if (k == 'N') {
			sortByName(s, numStudents);
		}
		if (k == 'X') {
			write(s, numStudents);
			cout << "Thanks for using THE SUPER GRADER" << endl;
			system("pause");
			return 0;
		}

	}
}