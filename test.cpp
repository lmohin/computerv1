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


// approximating square root function using Newton method
double	ft_sqrt(double const &number)
{
	if (number < 0)
        	return -1;
	if (number == 0)
		return 0;
    	
	double value = number / 2.0;
	double epsilon = 1e-10;
	double nextValue = 0.5 * (value + number / nextValue);
	
	while (ft_abs(nextValue - value) > epsilon)
	{
		value = nextValue;
		nextValue = 0.5 * (value + number / nextValue);
	}
	return nextValue;
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
	prout.push_back(-12);
	prout.push_back(29);
	prout.push_back(2);
	std::vector<double> caca;
	caca.push_back(32);
	PolynomialEquation here(prout, caca);
	printVect(here.getReducedPolynomial());
	here.solveInR();
	std::cout << here.getSolutions()[0] << std::endl << here.getSolutions()[1] << std::endl;
	here.showRealSolutionValues();
//	std::cout << sqrt(45) << std::endl;
//	std::cout << ft_sqrt(2) << std::endl;
}
