#include <iostream>
#include <map>
#include <iomanip>
#include "PolynomialEquation.hpp"
#include "mathsUtils.hpp"

bool	parsePolynomial(std::map<long int, double> &polynomial, std::string const &line);

static void	treatEquation(PolynomialEquation &MyEquation);
static void	printDegree0(PolynomialEquation const &MyEquation);
static void	printDegree1(PolynomialEquation const &MyEquation);
static void	printDegree2(PolynomialEquation &MyEquation);

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
	treatEquation(MyEquation);
	return (0);
}

void	treatEquation(PolynomialEquation &MyEquation)
{
	std::cout << "Reduced form: ";
	std::cout << MyEquation;
	std::cout << "Polynomial degree: " << MyEquation.getDegree() << std::endl;
	switch (MyEquation.getDegree())
	{
		case 0:
			printDegree0(MyEquation);
			break;

		case 1:
			printDegree1(MyEquation);
			break;

		case 2:
			printDegree2(MyEquation);
			break;
		
		default:
			std::cout << "The polynomial degree is stricly greater than 2, I can't solve." << std::endl;
	}
}
static void	printDegree0(PolynomialEquation const &MyEquation)
{
	if (MyEquation.getHasInfiniteSolutions())
		std::cout << "Any real number is a solution." << std::endl;
	else
		std::cout << "No solution." << std::endl;
}

static void	printDegree1(PolynomialEquation const &MyEquation)
{
	std::cout << "The single solution is:" << std::endl;
	std::cout << MyEquation.getSolutions()[0] << std::endl;
	std::cout << "Exact values:" << std::endl;
	MyEquation.showRealSolutionValues();
}

static void	printDegree2(PolynomialEquation &MyEquation)
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
