#include <iostream>
#include <iomanip>
#include <vector>
#include "PolynomialEquation.hpp"

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
int main(void)
{
	std::vector<double> prout;
	prout.push_back(4.43);
	prout.push_back(434.543);
	prout.push_back(-424);
	prout.push_back(-1);
	prout.push_back(0);
	prout.push_back(32.1);
	prout.push_back(0);
	std::vector<double> caca;
	caca.push_back(5);
	caca.push_back(7);
	caca.push_back(1);
	caca.push_back(-3);
	caca.push_back(6.1);
	PolynomialEquation here(prout, caca);
	printVect(here.getReducedPolynomial());
}
