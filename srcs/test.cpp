#include <iostream>
#include "PolynomialEquation.hpp"
#include "mathsUtils.hpp"

void	printMap(std::map<long int, double> const &value)
{
	for (std::map<long int, double>::const_iterator it = value.begin(); it != value.end(); it++)
	{
		if (it->second >= 0 && it->first != 0)
			std::cout << "+ ";
		else if (it->second < 0)
			std::cout << "- ";
		std::cout << ft_abs(it->second) << " * X";
		printExponent(it->first);
		std::cout << " ";
	}
	if (value.size() == 0)
		std::cout << "0 ";
	std::cout << "= 0" << std::endl;
}
