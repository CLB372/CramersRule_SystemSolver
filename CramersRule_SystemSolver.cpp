// This program solves an N x N linear system of equations using Cramer's Rule and a recursive
// function called det_nxn that solves the relevant determinants.
//
// Input must be in matrix form. For example, for the following 3 x 3 system of equations
// containing 3 variables x, y, and z:
//
//			ax + by + cz = d
//			fx + gy + hz = i
//			jx + ky + mz = n
//
// The input must look like the following (without any white space to the left of each row or'/' characters:
//
//			a,b,c,d
//			f,g,h,i
//			j,k,m,n
//
// Within each row the numbers must be separated by commas as shown above. Both integral and decimal
// values are allowed.
//
// Cramer's Rule for the above input dictates that the following ratios of determinants are solutions
// to these equations:
//
//		| d b c |			| a d c |			| a b d |
//		| i g h |			| f i h |			| f g i |
//		| n k m |			| j n m |			| j k n |
//	x =	---------		y = ---------       z = ---------
//		| a b c |			| a b c |			| a b c |
//		| f g h |			| f g h |			| f g h |
//		| j k m |			| j k m |			| j k m |
//
// The det_nxn function then solves the determinants in the numerators and denominators to arrive
// at solutions to the equations.
//
// The solutions are displayed to the user.
//
// The input can have any number of rows and columns, so long as the number of rows = the number of columns - 1.
// If the input is not N x (Nx1) numbers, the program will skip to an error message and terminate.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// function prototypes
vector<vector<double>> getFileInput(string filename);
double det_1x1(double x);
double det_2x2(vector<vector<double>> matrix);
double det_nxn(vector<vector<double>> matrix);
vector<double> solveSystem_CramersRule(vector<vector<double>> x);

int main()
{

	vector<vector<double>> inputMatrix;
	string filename;
	vector <double> solutions;

	// get the file name that contains the input
	cout << "\n\n  Enter the file name containing the N x (N+1) matrix representing an N x N system\n"
		 << "  of equations (please include the .txt extension):\n"
		 << "                                                       ";
	cin >> filename;
	inputMatrix = getFileInput(filename);
	cout << "\n\n  ";

	// display the matrix of numbers to the user for confirmation purposes
	for (int i = 0; i < inputMatrix.size(); i++)
	{
		for (int j = 0; j < inputMatrix[i].size(); j++)
		{
			cout << inputMatrix[i][j] << " ";
		}
		cout << "\n  ";
	}

	if (inputMatrix.size() == 0)
	{
		cout << "     ERROR: There were zero rows of numbers in your text file.\n\n";
	}
	else
	{
		if (inputMatrix[0].size() != inputMatrix.size() + 1)
		{
			cout << "     ERROR: The provided matrix of numbers is not an N x (N+1) matrix.\n\n";
		}
		else
		{
			// display the result to the user
			cout << "\n\n     RESULT: \n";
			solutions = solveSystem_CramersRule(inputMatrix);
			for (int i = 0; i < solutions.size(); i++)
			{
				cout << "              var" << i + 1 << " = " << solutions[i] << "\n\n";
			}
		}
	}
	cin.ignore(); cin.ignore();

	return 0;
}


vector<vector<double>> getFileInput(string filename)
// This function reads the file 'filename' (a *.txt file) and returns a matrix of the file's input values.
// The input must be in the format described in the comments at the top of this program.
{
	vector<vector<double>> inputMatrix;
	ifstream myFile;
	string stringInput;
	myFile.open(filename);

	// for every row of text in the file myFile...
	while (getline(myFile, stringInput))
	{
		stringstream linestream(stringInput);
		string individualNumber;

		// increase the number of rows in inputMatrix by 1
		inputMatrix.resize(inputMatrix.size() + 1);

		// for every individual number captured in the current row of the text file...
		while (getline(linestream, individualNumber, ','))
		{
			// increase the number of columns in inputMatrix by 1
			inputMatrix[inputMatrix.size() - 1].resize(inputMatrix[inputMatrix.size() - 1].size() + 1);

			// convert individualNumber from a string to a double, and input
			// the double value into the currentinputMatrix element
			stringstream cast(individualNumber);
			cast >> inputMatrix[inputMatrix.size() - 1][inputMatrix[inputMatrix.size() - 1].size() - 1];
		}
	}

	return inputMatrix;
}


double det_1x1(double x)
// the determinant of a single number is equal to the number itself
{
	return x;
}


double det_2x2(vector<vector<double>> matrix)
/*
	The determinant of a 2x2 matrix, with the following structure:

			a   b

			c   d

	equals (a x d) - (b x c)
*/
{
	return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
}


double det_nxn(vector<vector<double>> matrix)
// this function returns the determinant of any N x N matrix
{
	vector<vector<double>> submatrix;
	double result = 0;

	// there shouldn't be any 0-element matrix passed to this function,
	// but in case that happens, return 0 for the result
	if (matrix.size() == 0) { return 0; }

	// if the matrix 1x1, just return the number itself
	else if (matrix.size() == 1) { return matrix[0][0]; }

	// if the matrix is 2x2, return the value returned by det_2x2
	else if (matrix.size() == 2) { return det_2x2(matrix); }

	// otherwise, n > 2, and we will employ recursion to express
	// the value of the N x N determinant in terms of (N-1) x (N-1)
	// determinants, then express those determinants in terms of
	// (N-2) x (N-2) determinants, and so on, until the entire expression
	// is in terms of 2x2 determinants that can be calculated using det_2x2.
	// (This is called 'cofactor expansion' or 'expansion of minors' in
	// linear algebra texts.)
	else
	{
		// create an (n-1) x (n-1) matrix to hold the (n-1) x (n-1) determinants
		submatrix.resize(matrix.size() - 1);
		for (int i = 0; i < submatrix.size(); i++) { submatrix[i].resize(submatrix.size()); }

		// i goes through row 0 of the input matrix, from left to right
		for (int i = 0; i < matrix.size(); i++)
		{
			// j goes through rows 1 through n (downward of the input matrix)
			for (int j = 1; j < matrix.size(); j++)
			{
				// k goes through columns 0 through n, within row j of the input matrix
				for (int k = 0; k < matrix.size(); k++)
				{
					if (k < i)
					{
						submatrix[j - 1][k] = matrix[j][k];
					}
					else if (k > i)
					{
						submatrix[j - 1][k - 1] = matrix[j][k];
					}
					// (if j = i, then do nothing -- skip that column)
				}
			}

			result = result + (matrix[0][i] * det_nxn(submatrix) * pow(-1.0, i));
		}

		return result;
	}
}


vector<double> solveSystem_CramersRule(vector<vector<double>> x)
// solves an N x N system of equations using an N x (Nx1) input matrix 'x'
// that contains the matrix form of the system
{
	vector<vector<double>> denominatorMatrix;
	vector<vector<double>> numeratorMatrix;
	vector<double> rightHandVector;
	vector<double> solutions;

	// get the denominator matrix
	for (int i = 0; i < x.size(); i++)
	{
		denominatorMatrix.resize(i + 1);
		for (int j = 0; j < x[i].size() - 1; j++)
		{
			denominatorMatrix[i].resize(j + 1);
			denominatorMatrix[i][j] = x[i][j];
		}
	}

	// put the right-hand column of x into rightHandVector
	for (int i = 0; i < x.size(); i++)
	{
		rightHandVector.resize(i + 1);
		rightHandVector[i] = x[i][x.size()];
	}

	// for every unknown in the system...
	if (x.size() != 0)
	{
		for (int a = 0; a < x.size(); a++)
		{
			// get the relevant numerator matrix...
			numeratorMatrix.resize(0);
			for (int i = 0; i < x.size(); i++)
			{
				numeratorMatrix.resize(i+1);
				for (int j = 0; j < x[i].size(); j++)
				{
					numeratorMatrix[i].resize(numeratorMatrix[i].size() + 1);
					if (j != a)
					{
						numeratorMatrix[i][j] = x[i][j];
					}
					else
					{
						numeratorMatrix[i][j] = rightHandVector[i];
					}
				}
			}

			solutions.resize(solutions.size() + 1);
			solutions[a] = det_nxn(numeratorMatrix) / det_nxn(denominatorMatrix);

		}
	}
	
	return solutions;
}