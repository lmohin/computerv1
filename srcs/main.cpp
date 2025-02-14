#include <iostream>
#include <map>
#include <iomanip>
#include "PolynomialEquation.hpp"
#include "mathsUtils.hpp"

bool	parsePolynomial(std::map<long int, double> &polynomial, std::string const &line);
void	printMap(std::map<long int, double> const &value);

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
	printMap(MyEquation.getReducedPolynomial());
	std::cout << "Polynomial degree: " << MyEquation.getDegree() << std::endl;
	if (MyEquation.getDegree() < 3)
	{
		MyEquation.solveInR();
		MyEquation.showRealSolutionValues();
	}
	else
		std::cout << "The polynomial degree is stricly greater than 2, I can't solve." << std::endl;
	return (0);
}
