#include <iostream>
#include <map>
#include <iomanip>
#include "PolynomialEquation.hpp"
#include "mathsUtils.hpp"

bool	parsePolynomial(std::map<long int, double> &polynomial, std::string const &line);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Wrong number of arguments\n";
		std::cerr << "Example: \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
		return (1);
	}
	std::map<long int, double>	leftPolynomial;
	std::map<long int, double>	rightPolynomial;
	std::string	line(argv[1]);
	if (!parsePolynomial(leftPolynomial, line))
		return (1);
	if (!parsePolynomial(rightPolynomial, line.substr(line.find('=') + 1) + "="))
		return (1);
	PolynomialEquation	MyEquation(leftPolynomial, rightPolynomial);
	std::cout << "Reduced form: ";
	std::cout << MyEquation;
	std::cout << "Polynomial degree: " << MyEquation.getDegree() << std::endl;
	long int	degree = MyEquation.getDegree();
	if (degree == 0)
	{
		if (MyEquation.getHasInfiniteSolutions())
			std::cout << "Any real number is a solution." << std::endl;
		else
			std::cout << "No solution." << std::endl;
	}
	else if (degree == 1)
	{
		std::cout << "The single solution is:" << std::endl;
		std::cout << MyEquation.getSolutions()[0] << std::endl;
		std::cout << "Exact values:" << std::endl;
		MyEquation.showRealSolutionValues();
	}
	else if (degree == 2)
	{
		double	discriminant = MyEquation.evaluateDelta();
		if (discriminant == 0)
		{
			std::cout << "Discriminant is nul, the single solution is:" << std::endl;
			std::cout << MyEquation.getSolutions()[0] << std::endl;
			std::cout << "Exact values:" << std::endl;
			MyEquation.showRealSolutionValues();
		}
		else if (discriminant > 0)
		{
			std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
			std::cout << MyEquation.getSolutions()[0] << std::endl;
			std::cout << MyEquation.getSolutions()[1] << std::endl;
			std::cout << "Exact values:" << std::endl;
			MyEquation.showRealSolutionValues();
		}
		else
		{
			std::vector<std::pair<double, double> > sols = MyEquation.getComplexSolutions();
			std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
			std::cout << sols[0].first;
			if (sols[0].second >= 0)
				std::cout << " + " << sols[0].second << "i" << std::endl;
			else
				std::cout << " - " << -sols[0].second << "i" << std::endl;
			std::cout << sols[0].first;
			if (sols[1].second >= 0)
				std::cout << " + " << sols[1].second << "i" << std::endl;
			else
				std::cout << " - " << -sols[1].second << "i" << std::endl;
			std::cout << "Exact values:" << std::endl;
			MyEquation.showComplexSolutionValues();
		}
	}
	else
		std::cout << "The polynomial degree is stricly greater than 2, I can't solve." << std::endl;
	return (0);
}
