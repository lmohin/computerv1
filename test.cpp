#include <iostream>
#include <iomanip>
#include <vector>
#include "PolynomialEquation.hpp"
#include <cmath>
void	printDigit(int const &digit)
{
	switch (digit)
	{
		case 0:
			std::cout << "⁰";
			break;
		case 1:
			std::cout << "¹";
			break;
		case 2:
			std::cout << "²";
			break;
		case 3:
			std::cout << "³";
			break;
		case 4:
			std::cout << "⁴";
			break;
		case 5:
			std::cout << "⁵";
			break;
		case 6:
			std::cout << "⁶";
			break;
		case 7:
			std::cout << "⁷";
			break;
		case 8:
			std::cout << "⁸";
			break;
		case 9:
			std::cout << "⁹";
			break;
	}
}

void	printExponent(int const &value)
{
	if (value < 10)
		printDigit(value);	
	else
	{
		printExponent(value / 10);
		printDigit(value % 10);
	}
}

double	ft_abs(double const &value)
{
	if (value < 0)
		return (-1 * value);
	else
		return (value);
}

double	ft_sqrt(double const &number)//newton-raphson, se renseigner
{
	    if (number < 0) {
        std::cout << "Error: Cannot compute the square root of a negative number!" << std::endl;
        return -1;  // Return an error value
    }

    if (number == 0) return 0;  // Special case for 0
    
    double guess = number / 2.0;  // Start with an initial guess
    double epsilon = 1e-12;        // The precision level

    while (true) {
        double next_guess = 0.5 * (guess + number / guess);  // Newton's method formula
        if (std::abs(next_guess - guess) < epsilon) {
            break;  // Stop when the difference is within the acceptable range
        }
        guess = next_guess;  // Update the guess
    }

    return guess;
}

void	printVect(std::vector<double> const &value)
{
	int i = 0;
	for (std::vector<double>::const_iterator it = value.begin(); it != value.end(); it++)
	{
		if (*it >= 0 && i != 0)
			std::cout << "+ ";
		else if (*it < 0)
			std::cout << "- ";
		std::cout << ft_abs(*it) << " * X";
		printExponent(i);
		std::cout << " ";
		i++;
	}
	std::cout << "= 0" << std::endl;
}
/*
void	printPartialVect(std::vector<double> const &value)
{
}
*/

//a + bx + cx**2

int main(void)
{
	std::vector<double> prout;
	prout.push_back(4.4424324);
	prout.push_back(1);
	std::vector<double> caca;
	caca.push_back(0);
	PolynomialEquation here(prout, caca);
	printVect(here.getReducedPolynomial());
	here.solveInR();
	std::cout << here.getSolutions()[0] << std::endl << here.getSolutions()[1] << std::endl;
	here.showRealSolutionValues();
	std::cout << sqrt(0.00000000000000000004) << std::endl;
	std::cout << ft_sqrt(0.00000000000000000004) << std::endl;
}
