#ifndef POLYNOMIAL_HPP
# define POLYNOMIAL_HPP

# include <string>
# include <iostream>

class PolynomialEquation
{
	public :
		PolynomialEquation();
		PolynomialEquation(const &cpy);
		PolynomialEquation(std::vector<double> const &reducedPolynomialEquation);
		PolynomialEquation(std::vector<double> const &leftPolynomial, std::vector<double> const &rightPolynomial)

		~PolynomialEquation();

		void	reducePolynomialEquation(void);
		void	solveInR(void);
		void	solveInC(void);

		const	&operator=(Const &cpy);
		
	private :

		std::vector<double> leftPolynomial;
		std::vector<double> rightPolynomial;
};

std::ostream	&operator<<(std::ostream &o, Fixed const &obj);

#endif
