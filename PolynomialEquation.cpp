#include "PolynomialEquation.hpp"
#include <cmath>
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

PolynomialEquation::PolynomialEquation(std::vector<double> const &left, std::vector<double> const &right)
: _leftPolynomial(left), _rightPolynomial(right)
{
	reduceEquation();
	_degree = _reducedPolynomial.size() - 1;
	if (_degree == 0 && _reducedPolynomial[0] == 0)
		_hasInfiniteSolutions = true;
	else
		_hasInfiniteSolutions = false;
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

std::vector<double> const	&PolynomialEquation::getLeftPolynomial(void) const
{
	return (_leftPolynomial);
}

std::vector<double> const	&PolynomialEquation::getRightPolynomial(void) const
{
	return (_rightPolynomial);
}

std::vector<double> const	&PolynomialEquation::getReducedPolynomial(void) const
{
	return (_reducedPolynomial);
}

void	PolynomialEquation::reduceEquation(void)
{
	std::vector<double>	newReducedForm;

	if (_leftPolynomial.size() < _rightPolynomial.size())
	{
		std::vector<double>::iterator rightIt = _rightPolynomial.begin();
		for (std::vector<double>::iterator leftIt = _leftPolynomial.begin(); leftIt != _leftPolynomial.end(); leftIt++)
		{
			newReducedForm.push_back(*leftIt - *rightIt);
			rightIt++;
		}
		while (rightIt != _rightPolynomial.end())
		{
			newReducedForm.push_back(-1 * (*rightIt));
			rightIt++;
		}
	}
	else
	{
		std::vector<double>::iterator leftIt = _leftPolynomial.begin();
		for (std::vector<double>::iterator rightIt = _rightPolynomial.begin(); rightIt != _rightPolynomial.end(); rightIt++)
		{
			newReducedForm.push_back(*leftIt - *rightIt);
			leftIt++;
		}
		while (leftIt != _leftPolynomial.end())
		{
			newReducedForm.push_back(*leftIt);
			leftIt++;
		}
	}
	std::vector<double>::iterator it = newReducedForm.end();
	while (it != newReducedForm.begin() && *it == 0)
		it--;
	if (it != newReducedForm.end() && it != newReducedForm.begin())
		newReducedForm.erase(it + 1, newReducedForm.end());
	_reducedPolynomial = newReducedForm;
}

void	PolynomialEquation::solveInR(void)
{
	if (_degree == 2)
	{
		double a = _reducedPolynomial[2];
		double b = _reducedPolynomial[1];
		double c = _reducedPolynomial[0];
		double delta = b * b - 4 * a * c;
		if (delta > 0)
		{
			double x1 = (-b - sqrt(delta)) / (2 * a);
			double x2 = (-b + sqrt(delta)) / (2 * a);
			if (c != 0 && (x1 == 0 || x2 == 0))
				std::cout << "cant solve this equation" << std::endl;
			_solutions.push_back(x1);
			_solutions.push_back(x2);
		}
		else if (delta == 0)
			_solutions.push_back((-b) / (2 * a));
	}
	else if (_degree == 1)
		_solutions.push_back(_reducedPolynomial[0] / _reducedPolynomial[1]);
}

void	PolynomialEquation::showRealSolutionValues(void) const
{
	if (_degree == 2)
	{
		double a = _reducedPolynomial[2];
		double b = _reducedPolynomial[1];
		double c = _reducedPolynomial[0];
		double delta = b * b - 4 * a * c;
		if (delta > 0)
		{
			std::cout << "(" << -b << " - " << "sqrt(" << delta << "))" << " / " << 2 * a << std::endl;
			std::cout << "(" << -b << " + " << "sqrt(" << delta << "))" << " / " << 2 * a << std::endl;
		}
		else if (delta == 0)
			std::cout << -b << " / " << 2 * a << std::endl;
	}
	if (_degree == 1)
		std::cout << _reducedPolynomial[0] << " / " << _reducedPolynomial[1] << std::endl;
	if (_degree == 0)
	{
		if (_reducedPolynomial[0] == 0)
			std::cout << "any real number is a solution!" << std::endl;
		else
			std::cout << "There are no solutions" << std::endl;
	}
}

//void	PolynomialEquation::evaluateDegree(void)
//{
//	int i = 0;
//	for (std::vector<double>::iterator it = _reducedPolynomial
//}
