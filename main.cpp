#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <cstdlib>

//TO DO : Gerer les overflow et clean le code 

bool	parseCoef(std::string const &line, size_t &i)
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

bool	parsePower(std::string const &line, size_t &i)
{
	if (!isdigit(line[i]))
		return (false);
	while (isdigit(line[i]))
		i++;
	return (true);
}

bool	parseLeftPolynomial(std::map<long int, double> &leftValues, std::string const &line)
{
	if (line.find('=') == std::string::npos)
		return (false);
	size_t		i = 0;
	char		*endptr;
	bool		firstCoef = true;
	while (1)
	{
		while (isspace(line[i]))
			i++;
		int	sign = 1;
		char	*endptr;
		if (line[i] == '-')
		{
			i++;
			sign = -1;
		}
		else if (line[i] == '+')
			i++;
		else if (!firstCoef)
			return (false);
		while (isspace(line[i]))
			i++;
		if (!isdigit(line[i]) && line[i] != 'X' && line[i] != 'x')
			return (false);
		double	newCoef = std::strtod(line.substr(i).c_str(), &endptr);
		if (newCoef == 0 && (line[i] == 'X' || line[i] == 'x'))
			newCoef = 1;
		newCoef *= sign;
		if (!parseCoef(line, i))
			return (false);

		long int	power;
		if ((line[i] == 'X' || line[i] == 'x') && line[i + 1] == '^')
		{
			i += 2;
			power = std::strtol(line.substr(i).c_str(), &endptr, 10);
			if (!parsePower(line, i))
				return (false);
		}
		else if (line[i] == 'X' || line[i] == 'x')
		{
			i += 1;
			power = 1;
		}
		else
			power = 0;
		if (leftValues.find(power) != leftValues.end())
			leftValues[power] += newCoef;
		else
			leftValues[power] = newCoef;
		if (line[i] == '=')
			return (true);
		firstCoef = false;
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
	char *myptr;
	
	if (!parseLeftPolynomial(leftPolynomial, argv[1]))
		std::cout << "error\n" << std::endl;
	for (std::map<long int, double>::iterator it = leftPolynomial.begin(); it != leftPolynomial.end(); it++)
	{
		std::cout << std::setprecision(10) << it->second << "X^" << it->first << std::endl;
	}
	//parseRightPolynomial(rightPolynomial, argv[1]);
}
