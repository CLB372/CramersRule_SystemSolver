# CramersRule_SystemSolver
Solves a system of N equations with N variables from file input using Cramer's Rule and a recursive function that solves determinants of any size.

The file CramersRule_SystemSolver.exe is the executable file for this program. The user's input text file should be in the same directory as this file.

The file CramersRule_SystemSolver.cpp is the relevant C++ code.

This program solves an N x N linear system of equations using Cramer's Rule and a recursive
function called det_nxn that solves the relevant determinants. It displays the solutions
to the user.

Input must be in matrix form. For example, for the following 3 x 3 system of equations
containing 3 variables x, y, and z:

			ax + by + cz = d
			fx + gy + hz = i
      		jx + ky + mz = n
      
The input must look like the following (without any white space to the left of each row:

			a,b,c,d
			f,g,h,i
			j,k,m,n
      
Within each row the numbers must be separated by commas as shown above. Both integral and decimal
values are allowed.

Cramer's Rule for the above input dictates that the following ratios of determinants are solutions
to these equations:

		| d b c |			| a d c |			| a b d |
		| i g h |			| f i h |			| f g i |
		| n k m |			| j n m |			| j k n |
	x =	---------		    y = ---------                   z = ---------
		| a b c |			| a b c |			| a b c |
		| f g h |			| f g h |			| f g h |
		| j k m |			| j k m |			| j k m |

The det_nxn function then solves the determinants in the numerators and denominators to arrive
at solutions to the equations.

The solutions are displayed to the user.

The input can have any number of rows and columns, so long as the number of rows = the number of columns - 1.
If the input is not N x (Nx1) numbers, the program will skip to an error message and terminate.
