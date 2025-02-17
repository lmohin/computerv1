#ifndef POLYNOMIAL_EQUATION_HPP
# define POLYNOMIAL_EQUATION_HPP

# include <string>
# include <iostream>
# include <vector>
# include <map>
# include "mathsUtils.hpp"

class PolynomialEquation
{
	public :
		PolynomialEquation(void);
		PolynomialEquation(PolynomialEquation const &cpy);
		PolynomialEquation(std::map<long int, double> const &reducedPolynomialEquation);
		PolynomialEquation(std::map<long int, double> const &leftPolynomial, std::map<long int, double> const &rightPolynomial);

		~PolynomialEquation();

		void	reducePolynomialEquation(void);
		void	solveInR(void);
		void	solveInC(void);

		int const		&getDegree(void) const;
		bool const		&getHasInfiniteSolutions(void) const;
		std::vector<double> const	&getSolutions(void) const;
		std::vector<std::pair<double, double> > const	&getComplexSolutions(void) const;
		std::map<long int, double> const	&getLeftPolynomial(void) const;
		std::map<long int, double> const	&getRightPolynomial(void) const;
		std::map<long int, double> const	&getReducedPolynomial(void) const;

		double	evaluateDelta(void);

		void	reduceEquation(void);
		
		void	showRealSolutionValues(void) const;
		void	showComplexSolutionValues(void) const;

		PolynomialEquation const	&operator=(PolynomialEquation const &cpy);	
	
	private :

		int			_degree;
		bool			_hasInfiniteSolutions;
		std::vector<double>	_solutions;	
		std::vector<std::pair<double, double> > _complexSolutions;

		std::map<long int, double>	_leftPolynomial;
		std::map<long int, double>	_rightPolynomial;
		std::map<long int, double>	_reducedPolynomial;
};

std::ostream	&operator<<(std::ostream &o, PolynomialEquation const &toPrint);

#endif
