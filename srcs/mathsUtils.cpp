#include <iostream>

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
    	
	double value = 0;
	double epsilon = 1e-10;
	double nextValue = number / 2.0;
	
	while (ft_abs(nextValue - value) > epsilon)
	{
		value = nextValue;
		nextValue = 0.5 * (value + number / nextValue);
	}
	return nextValue;
}

