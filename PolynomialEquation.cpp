#include "PolynomialEquation.hpp"

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


// Setters //

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

//void	PolynomialEquation::evaluateDegree(void)
//{
//	int i = 0;
//	for (std::vector<double>::iterator it = _reducedPolynomial
//}
