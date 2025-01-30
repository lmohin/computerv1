#include <iostream>
#include <iomanip>
#include <vector>

// ¹²³⁴⁵⁶⁷⁸⁹ //

double	ft_abs(double const &value)
{
	if (value < 0)
		return (-1 * value);
	else
		return (value);
}

void	printFullVect(std::vector<double> const &value)
{
	int i = 0;
	for (std::vector<double>::const_iterator it = value.begin(); it != value.end(); it++)
	{
		if (i != 0)
		{
			if (*it > 0)
				std::cout << "+ ";
			else
				std::cout << "- ";
		}
		std::cout << ft_abs(*it) << " * X^" << i << " ";
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
	prout.push_back(4242343242.3432432432454365);
	printFullVect(prout);
}
