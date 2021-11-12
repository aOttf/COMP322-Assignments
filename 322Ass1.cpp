//============================================================================
// Name        : 322Ass1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : 322 Assignment1
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
using namespace std;

const int rows = 5;
const int cols = 5;

void checkPassword();
void convertPhonetic();
void fillMatrix(int matrix[rows][cols]);
void printMatrix(int matrix[rows][cols]);
void multiplyMatrices(int matrix_left[rows][cols], int matrix_right[rows][cols],
		int matrix_result[rows][cols]);

int main() {
	checkPassword();
	convertPhonetic();

	//initialize matrices with all entries zero
	int matrix[rows][cols] = { 0 };
	int matrix2[rows][cols] = { 0 };
	int matrix_result[rows][cols] = { 0 };

	fillMatrix(matrix);
	fillMatrix(matrix2);
	printMatrix(matrix);
	printMatrix(matrix2);
	multiplyMatrices(matrix, matrix2, matrix_result);
	printMatrix(matrix_result);
	return 0;
}

void checkPassword() {
	string password;

	cout << "Please Enter your password:" << endl;
	cin >> password;

	int len = password.length();

	//copy password
	char cp[len + 1];
	password.copy(cp, len, 0);
	cp[len + 1] = '\0';

	//check length
	if (len < 8) {
		cout << "The password should be at least 8 characters." << endl;
		return;
	}

	//check occurrance
	for (int i = 0; i < len; i++) {
		int count = 0;

		//cp[i] hasn't been counted
		if (cp[i]) {
			count++;
			for (int j = i + 1; j < len; j++) {
				if (cp[j] == cp[i]) {
					count++;

					//cp[j] has been counted
					cp[j] = '\0';
				}
			}

			//character occurs at lease 3 times
			if (count > 2) {
				cout
						<< "each character does not occur more than 2 times in the word"
						<< endl;
				return;
			}
		}
	}

	//check number
	int i = 0;
	for (; i < len; i++) {
		//has found a digit, no need to check
		if (isdigit(password[i])) {
			break;
		}
	}

	//no digit found after traversing the password
	if (i >= len) {
		cout << "The password should contain at least one number." << endl;
		return;
	}

	//check symbol
	i = 0;
	bool issymbol = false;
	for (; i < len; i++) {
		switch (password[i]) {
		case '*':
			issymbol = true;
			break;
		case '$':
			issymbol = true;
			break;
		case '#':
			issymbol = true;
			break;
		}

		//has found a special symbol; no need to check
		if (issymbol)
			break;
	}

	//no special symbols found after traversing the password
	if (i >= len) {
		cout << "The password should contain at least one special symbol."
				<< endl;
		return;
	}

	//set password successfully
	cout << "The password has been set." << endl;
	return;

}

void convertPhonetic() {
	string input;
	cout << "Please Enter a word:";
	cin >> input;

	//a lot of switch cases...
	unsigned int i = 0;
	for (; i < input.length(); i++) {
		switch (input[i]) {
		case 'a':
		case 'A':
			cout << "Alfa ";
			break;

		case 'b':
		case 'B':
			cout << "Bravo ";
			break;

		case 'c':
		case 'C':
			cout << "Charlie ";
			break;

		case 'd':
		case 'D':
			cout << "Delta ";
			break;
		case 'e':
		case 'E':
			cout << "Echo ";
			break;
		case 'f':
		case 'F':
			cout << "Foxtrot ";
			break;
		case 'g':
		case 'G':
			cout << "Golf ";
			break;
		case 'h':
		case 'H':
			cout << "Hotel ";
			break;
		case 'i':
		case 'I':
			cout << "India ";
			break;
		case 'j':
		case 'J':
			cout << "Juliett ";
			break;
		case 'k':
		case 'K':
			cout << "Kilo ";
			break;
		case 'l':
		case 'L':
			cout << "Lima ";
			break;
		case 'm':
		case 'M':
			cout << "Mike ";
			break;
		case 'n':
		case 'N':
			cout << "November ";
			break;
		case 'o':
		case 'O':
			cout << "Oscar ";
			break;
		case 'p':
		case 'P':
			cout << "Papa ";
			break;
		case 'q':
		case 'Q':
			cout << "Quebec ";
			break;
		case 'r':
		case 'R':
			cout << "Romeo ";
			break;
		case 's':
		case 'S':
			cout << "Sierra ";
			break;
		case 't':
		case 'T':
			cout << "Tango ";
			break;
		case 'u':
		case 'U':
			cout << "Uniform ";
			break;
		case 'v':
		case 'V':
			cout << "Victor ";
			break;
		case 'w':
		case 'W':
			cout << "Whiskey ";
			break;
		case 'x':
		case 'X':
			cout << "X-ray ";
			break;
		case 'y':
		case 'Y':
			cout << "Yankee ";
			break;
		case 'z':
		case 'Z':
			cout << "Zulu ";
			break;

		case '1':
			cout << "One ";
			break;

		case '2':
			cout << "Two ";
			break;
		case '3':
			cout << "Three ";
			break;
		case '4':
			cout << "Four ";
			break;
		case '5':
			cout << "Five ";
			break;
		case '6':
			cout << "Six ";
			break;
		case '7':
			cout << "Seven ";
			break;
		case '8':
			cout << "Eight ";
			break;
		case '9':
			cout << "Nine ";
			break;
		case '0':
			cout << "Zero ";
			break;
		}
	}
	//newline printed
	cout << endl;
}

void fillMatrix(int matrix[rows][cols]) {
	srand(time(0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//range from 0 to 25
			matrix[i][j] = rand() % (25 + 1);
		}
	}
	Sleep(1000);
}

void printMatrix(int matrix[rows][cols]) {
	for (int i = 0; i < rows; i++) {
		int j = 0;
		for (; j < cols - 1; j++) {
			cout << matrix[i][j] << " |";
		}
		cout << matrix[i][j] << endl;
		cout << "------------------------------" << endl;

	}
}

void multiplyMatrices(int matrix_left[rows][cols], int matrix_right[rows][cols],
		int matrix_result[rows][cols]) {
	//pointers to entries
	static int i = 0, j = 0, k = 0;

	//traversed all the entries
	if (i >= rows) {
		i = 0;
		return;
	}

	//one row of result has been computed
	if (j >= cols) {
		j = 0;
		i++;
		return multiplyMatrices(matrix_left, matrix_right, matrix_result);
	}

	//one cell of result has been computed
	if (k >= cols) {
		k = 0;
		j++;
		return multiplyMatrices(matrix_left, matrix_right, matrix_result);
	}

	//multiplying two entries and add to the current cell of result matrix
	matrix_result[i][j] += matrix_left[i][k] * matrix_right[k][j];
	k++;
	return multiplyMatrices(matrix_left, matrix_right, matrix_result);
}

