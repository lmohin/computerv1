#include <iostream>
#include <map>
#include <iomanip>

bool	parsePolynomial(std::map<long int, double> &polynomial, std::string const &line);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Wrong number of arguments\n";
		std::cout << "Example: \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
		return (1);
	}
	std::map<long int, double>	leftPolynomial;
	std::map<long int, double>	rightPolynomial;
	std::string	line(argv[1]);
	if (!parsePolynomial(leftPolynomial, line))
		return (1);
	if (!parsePolynomial(rightPolynomial, line.substr(line.find('=') + 1) + "="))
		return (1);
	for (std::map<long int, double>::iterator it = leftPolynomial.begin(); it != leftPolynomial.end(); it++)
	{
		std::cout << std::setprecision(10) << it->second << "X^" << it->first << std::endl;
	}
	std::cout << std::endl << std::endl;
	for (std::map<long int, double>::iterator it = rightPolynomial.begin(); it != rightPolynomial.end(); it++)
	{
		std::cout << std::setprecision(10) << it->second << "X^" << it->first << std::endl;
	}
}
