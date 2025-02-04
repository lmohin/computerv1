#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
//TO DO : Gerer les overflow et clean le code 

static void	printInvalidFormat(void)
{
	std::cout << "Error: Invalid format.\nExample: \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
}

static void	printOverflowError(void)
{
	std::cout << "Error: Overflow detected.\nTry again with smaller numbers!" << std::endl;
}

static bool	parseCoef(std::string const &line, size_t &i)
{
	bool	pointDetected = false;
	
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (isspace(line[i]))
		i++;
	while (isdigit(line[i]) || (!pointDetected && line[i] == '.' && isdigit(line[i + 1])))
	{
		if (line[i] == '.')
			pointDetected = true;
		i++;
	}
	while (isspace(line[i]))
		i++;
	if (line[i] == '*')
		i++;
	while (isspace(line[i]))
		i++;
	return (true);
}

static bool	parsePower(std::string const &line, size_t &i)
{
	if (!isdigit(line[i]))
		return (false);
	while (isdigit(line[i]))
		i++;
	return (true);
}

static int	getSign(std::string const &line, size_t &i, int &sign, bool const &firstCoef)
{
	while (isspace(line[i]))
		i++;
	if (line[i] == '-')
	{
		i++;
		sign = -1;
	}
	else if (line[i] == '+')
	{
		i++;
		sign = 1;
	}
	else if (!firstCoef)
		return (false);
	else
		sign = 1;
	while (isspace(line[i]))
		i++;
	return (true);
}

static bool	getCoef(std::string const &line, size_t &i, double &newCoef, bool const &firstCoef)
{
	char	*endptr;
	int	sign;

	if (!getSign(line, i, sign, firstCoef))
	{
		printInvalidFormat();
		return (false);
	}
	if (!isdigit(line[i]) && line[i] != 'X' && line[i] != 'x')
	{
		printInvalidFormat();
		return (false);
	}
	errno = 0;
	newCoef = std::strtod(line.substr(i).c_str(), &endptr);
	if (errno == ERANGE)
	{
		printOverflowError();
		return (false);
	}
	if (newCoef == 0 && (line[i] == 'X' || line[i] == 'x'))
		newCoef = 1;
	newCoef *= sign;
	if (!parseCoef(line, i))
	{
		printInvalidFormat();
		return (false);
	}
	return (true);
}

static bool	getPower(std::string const &line, size_t &i, long int &power)
{
	char	*endptr;

	if ((line[i] == 'X' || line[i] == 'x') && line[i + 1] == '^')
	{
		i += 2;
		errno = 0;
		power = std::strtol(line.substr(i).c_str(), &endptr, 10);
		if (errno == ERANGE || !parsePower(line, i))
		{
			printOverflowError();
			return (false);
		}
	}
	else if (line[i] == 'X' || line[i] == 'x')
	{
		i += 1;
		power = 1;
	}
	else
		power = 0;
	return (true);
}

bool	parsePolynomial(std::map<long int, double> &values, std::string const &line)
{
	size_t		i = 0;
	bool		firstCoef = true;

	if (line.find('=') == std::string::npos)
	{
		printInvalidFormat();
		return (false);
	}
	while (1)
	{
		double		newCoef;
		long int	power;

		if (!getCoef(line, i, newCoef, firstCoef))
			return (false);
		if (!getPower(line, i, power))
			return (false);
		if (values.find(power) != values.end())
			values[power] += newCoef;
		else
			values[power] = newCoef;
		while (isspace(line[i]))
			i++;
		firstCoef = false;
		if (line[i] == '=')
			return (true);
	}
	return (false);
}

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
	if (line.substr(line.find('=') + 1).find('=') != std::string::npos)
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
	//parseRightPolynomial(rightPolynomial, argv[1]);
}
