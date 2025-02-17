#include "PolynomialEquation.hpp"
#include <iomanip>

double	ft_abs(double const &value);

PolynomialEquation::PolynomialEquation(void)
: _degree(0), _hasInfiniteSolutions(true)
{
	return ;
}

PolynomialEquation::PolynomialEquation(PolynomialEquation const &cpy)
: _degree(cpy.getDegree()), _hasInfiniteSolutions(cpy.getHasInfiniteSolutions()), _solutions(cpy.getSolutions()), 
	_leftPolynomial(cpy.getLeftPolynomial()), _rightPolynomial(cpy.getRightPolynomial()), _reducedPolynomial(cpy.getReducedPolynomial())
{
	return ;
}

PolynomialEquation::PolynomialEquation(std::map<long int, double> const &left, std::map<long int, double> const &right)
: _leftPolynomial(left), _rightPolynomial(right)
{
	reduceEquation();
	if (_reducedPolynomial.size() == 0)
		_degree = 0;
	else
		_degree = _reducedPolynomial.rbegin()->first;
	if (_reducedPolynomial.size() == 0)
		_hasInfiniteSolutions = true;
	else
		_hasInfiniteSolutions = false;
	solveInR();
	solveInC();
}


// Destructor //

PolynomialEquation::~PolynomialEquation(void)
{
	return ;
}

// Getters //

int const	&PolynomialEquation::getDegree(void) const
{
	return (_degree);
}

bool const	&PolynomialEquation::getHasInfiniteSolutions(void) const
{
	return (_hasInfiniteSolutions);
}

std::vector<double>  const	&PolynomialEquation::getSolutions(void) const
{
	return (_solutions);
}

std::vector<std::pair<double, double> > const	&PolynomialEquation::getComplexSolutions(void) const
{
	return (_complexSolutions);
}

std::map<long int, double> const	&PolynomialEquation::getLeftPolynomial(void) const
{
	return (_leftPolynomial);
}

std::map<long int, double> const	&PolynomialEquation::getRightPolynomial(void) const
{
	return (_rightPolynomial);
}

std::map<long int, double> const	&PolynomialEquation::getReducedPolynomial(void) const
{
	return (_reducedPolynomial);
}

double	PolynomialEquation::evaluateDelta(void)
{
	if (this->_degree != 2)
	{
		std::cout << "Can't calculate discriminant if the degree isn't 2" << std::endl;
		return (0);
	}
	else
	{
		double const a = _reducedPolynomial[2];
		double const b = _reducedPolynomial.count(1) ? _reducedPolynomial[1] : 0;
		double const c = _reducedPolynomial.count(0) ? _reducedPolynomial[0] : 0;
		return (b * b - 4 * a * c);
	}
}

void	PolynomialEquation::reduceEquation(void)
{
	for (std::map<long int, double>::const_iterator it = _leftPolynomial.begin(); it != _leftPolynomial.end(); it++)
	{
		if (it->second != 0)
			_reducedPolynomial[it->first] = it->second;
	}
	for (std::map<long int, double>::const_iterator it = _rightPolynomial.begin(); it != _rightPolynomial.end(); it++)
	{
		if (it->second != 0)
		{
			if (_reducedPolynomial.count(it->first) == 1)
			{
				_reducedPolynomial[it->first] -= it->second;
				if (_reducedPolynomial[it->first] == 0)
				{
					_reducedPolynomial.erase(it->first);
				}
			}
			else
				_reducedPolynomial[it->first] = -1 * it->second;
		}
	}
}

void	PolynomialEquation::solveInR(void)
{
	if (_degree == 2)
	{
		double a = _reducedPolynomial[2];
		double b = _reducedPolynomial.count(1) ? _reducedPolynomial[1] : 0;
		double c = _reducedPolynomial.count(0) ? _reducedPolynomial[0] : 0;
		double delta = b * b - 4 * a * c;
		if (delta > 0)
		{
			double x1 = (-b - ft_sqrt(delta)) / (2 * a);
			double x2 = (-b + ft_sqrt(delta)) / (2 * a);
			_solutions.push_back(x1);
			_solutions.push_back(x2);
		}
		else if (delta == 0)
			_solutions.push_back((-b) / (2 * a));
	}
	else if (_degree == 1)
	{
		double a = _reducedPolynomial[1];
		double b = _reducedPolynomial.count(0) ? _reducedPolynomial[0] : 0;
		_solutions.push_back(-b/a);
	}
}

void	PolynomialEquation::solveInC(void)
{
	if (_degree == 2)
	{
		double a = _reducedPolynomial[2];
		double b = _reducedPolynomial.count(1) ? _reducedPolynomial[1] : 0;
		double c = _reducedPolynomial.count(0) ? _reducedPolynomial[0] : 0;
		double delta = b * b - 4 * a * c;
		if (delta > 0)
		{
			double x1_r = (-b - ft_sqrt(delta)) / (2 * a);
			double x2_r = (-b + ft_sqrt(delta)) / (2 * a);
			std::pair<double, double>	x1(x1_r, 0);
			std::pair<double, double>	x2(x2_r, 0);
			_complexSolutions.push_back(x1);
			_complexSolutions.push_back(x2);
		}
		else if (delta == 0)
		{
			double	x_r = (-b) / (2 * a);
			std::pair<double, double>	x(x_r, 0);
			_complexSolutions.push_back(x);
		}
		else
		{
			double x1_r = -b / (2 * a);
			double x2_r = -b / (2 * a);
			double x1_i = - ft_sqrt(-delta) / (2 * a);
			double x2_i = + ft_sqrt(-delta) / (2 * a);
			
			std::pair<double, double>	x1(x1_r, x1_i);
			std::pair<double, double>	x2(x2_r, x2_i);
			
			_complexSolutions.push_back(x1);
			_complexSolutions.push_back(x2);
		}
	}
	else if (_degree == 1)
	{
		double a = _reducedPolynomial[1];
		double b = _reducedPolynomial.count(0) ? _reducedPolynomial[0] : 0;
		
		double	x_r = (-b / a);
		std::pair<double, double>	x(x_r, 0);
		
		_complexSolutions.push_back(x);
	}
}

void	PolynomialEquation::showRealSolutionValues(void) const
{
	if (_degree == 2)
	{
		double a = _reducedPolynomial.at(2);
		double b = _reducedPolynomial.count(1) ? _reducedPolynomial.at(1) : 0;
		double c = _reducedPolynomial.count(0) ? _reducedPolynomial.at(0) : 0;
		double delta = b * b - 4 * a * c;
		if (delta > 0)
		{
			std::cout << std::setprecision(20) << "(" << -b << " - " << "sqrt((" << b << ")^2 - 4 * " << a << " * " << c << "))" << " / " << 2 * a << std::endl;
			std::cout << std::setprecision(20) << "(" << -b << " + " << "sqrt((" << b << ")^2 - 4 * " << a << " * " << c << "))" << " / " << 2 * a << std::endl;
		}
		else if (delta == 0)
			std::cout << std::setprecision(20) << -b << " / " << 2 * a << std::endl;
		else
			std::cout << "There are no real solutions" << std::endl;
	}
	if (_degree == 1)
	{
		double a = _reducedPolynomial.at(1);
		double b = _reducedPolynomial.count(0) ? _reducedPolynomial.at(0) : 0;
		std::cout << std::setprecision(20) << -b << " / " << a << std::endl;
	}
	if (_degree == 0)
	{
		if (_reducedPolynomial.size() == 0 || _reducedPolynomial.at(0) == 0)
			std::cout << "Any real number is a solution!" << std::endl;
		else
			std::cout << "There are no solutions" << std::endl;
	}
}

void	PolynomialEquation::showComplexSolutionValues(void) const
{
	if (_degree == 2)
	{
		double a = _reducedPolynomial.at(2);
		double b = _reducedPolynomial.count(1) ? _reducedPolynomial.at(1) : 0;
		double c = _reducedPolynomial.count(0) ? _reducedPolynomial.at(0) : 0;
		double delta = b * b - 4 * a * c;
		if (delta > 0)
		{
			std::cout << std::setprecision(20) << "(" << -b << " - " << "sqrt((" << b << ")^2 - 4 * " << a << " * " << c << "))" << " / " << 2 * a << std::endl;
			std::cout << std::setprecision(20) << "(" << -b << " + " << "sqrt((" << b << ")^2 - 4 * " << a << " * " << c << "))" << " / " << 2 * a << std::endl;
		}
		else if (delta == 0)
			std::cout << std::setprecision(20) << -b << " / " << 2 * a << std::endl;
		else
		{
			std::cout << std::setprecision(20) << "(" << -b << " - " << "i * sqrt(" << "-((" << b << ")^2 - 4 * " << a << " * " << c << ")))" << " / " << 2 * a << std::endl;
			std::cout << std::setprecision(20) << "(" << -b << " + " << "i * sqrt(" << "-((" << b << ")^2 - 4 * " << a << " * " << c << ")))" << " / " << 2 * a << std::endl;
		}
	}
	if (_degree == 1)
	{
		double a = _reducedPolynomial.at(1);
		double b = _reducedPolynomial.count(0) ? _reducedPolynomial.at(0) : 0;
		std::cout << std::setprecision(20) << -b << " / " << a << std::endl;
	}
	if (_degree == 0)
	{
		if (_reducedPolynomial.size() == 0 || _reducedPolynomial.at(0) == 0)
			std::cout << "Any complex number is a solution!" << std::endl;
		else
			std::cout << "There are no solutions" << std::endl;
	}
}

std::ostream	&operator<<(std::ostream &o, PolynomialEquation const &obj)
{
	std::map<long int, double> const &value = obj.getReducedPolynomial();
	for (std::map<long int, double>::const_iterator it = value.begin(); it != value.end(); it++)
	{
		if (it->second >= 0 && it->first != 0)
			o << "+ ";
		else if (it->second < 0 && it->first != 0)
			o << "- ";
		else if (it->second < 0)
			o << "-";
		std::cout << ft_abs(it->second);
		if (it->first != 0)
		{
			o << " * X";
			if (it->first != 1)
				printExponent(it->first);
		}
		o << " ";
		
	}
	if (value.size() == 0)
		o << "0 ";
	o << "= 0" << std::endl;
	return (o);
}
