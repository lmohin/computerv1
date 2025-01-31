#ifndef POLYNOMIAL_EQUATION_HPP
# define POLYNOMIAL_EQUATION_HPP

# include <string>
# include <iostream>
# include <vector>

class PolynomialEquation
{
	public :
		PolynomialEquation(void);
		PolynomialEquation(PolynomialEquation const &cpy);
		PolynomialEquation(std::vector<double> const &reducedPolynomialEquation);
		PolynomialEquation(std::vector<double> const &leftPolynomial, std::vector<double> const &rightPolynomial);

		~PolynomialEquation();

		void	reducePolynomialEquation(void);
		void	solveInR(void);
		void	solveInC(void);

		int const		&getDegree(void) const;
		bool const		&getHasInfiniteSolutions(void) const;
		std::vector<double> const	&getSolutions(void) const;
		std::vector<double> const	&getLeftPolynomial(void) const;
		std::vector<double> const	&getRightPolynomial(void) const;
		std::vector<double> const	&getReducedPolynomial(void) const;

		void	reduceEquation(void);
		
		void	showRealSolutionValues(void) const;
		
		PolynomialEquation const	&operator=(PolynomialEquation const &cpy);	
	
	private :

		int			_degree;
		bool			_hasInfiniteSolutions;
		std::vector<double>	_solutions;	
	
		std::vector<double>	_leftPolynomial;
		std::vector<double>	_rightPolynomial;
		std::vector<double>	_reducedPolynomial;
};

//std::ostream	&operator<<(std::ostream &o, Fixed const &obj);

#endif
