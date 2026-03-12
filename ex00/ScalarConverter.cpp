/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:30:12 by blohrer           #+#    #+#             */
/*   Updated: 2026/03/12 14:30:13 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	(void)other;
}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return (*this);
}
ScalarConverter::~ScalarConverter() {}

enum e_type
{
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_PSEUDO_FLOAT,
	TYPE_PSEUDO_DOUBLE,
	TYPE_INVALID
};

static bool	isPseudoFloat(const std::string &s)
{
	return (s == "nanf" || s == "+inff" || s == "-inff");
}

static bool	isPseudoDouble(const std::string &s)
{
	return (s == "nan" || s == "+inf" || s == "-inf");
}

static bool	isCharLiteral(const std::string &s)
{
	if (s.length() != 1)
		return (false);
	if (std::isdigit(s[0]))
		return (false);
	return (true);
}

static bool	isIntLiteral(const std::string &s)
{
	size_t	i;

	if (s.empty())
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (i == s.length())
		return (false);
	while (i < s.length())
	{
		if (!std::isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	isFloatLiteral(const std::string &s)
{
	size_t	i;
	bool	hasDigit;
	bool	hasDot;

	if (s.length() < 2 || s[s.length() - 1] != 'f')
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	hasDigit = false;
	hasDot = false;
	while (i < s.length() - 1)
	{
		if (std::isdigit(s[i]))
			hasDigit = true;
		else if (s[i] == '.' && !hasDot)
			hasDot = true;
		else
			return (false);
		i++;
	}
	if (!hasDigit || !hasDot)
		return (false);
	return (true);
}

static bool	isDoubleLiteral(const std::string &s)
{
	size_t	i;
	bool	hasDigit;
	bool	hasDot;

	if (s.empty())
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	hasDigit = false;
	hasDot = false;
	while (i < s.length())
	{
		if (std::isdigit(s[i]))
			hasDigit = true;
		else if (s[i] == '.' && !hasDot)
			hasDot = true;
		else
			return (false);
		i++;
	}
	if (!hasDigit || !hasDot)
		return (false);
	return (true);
}

static e_type	detectType(const std::string &literal)
{
	if (isPseudoFloat(literal))
		return (TYPE_PSEUDO_FLOAT);
	if (isPseudoDouble(literal))
		return (TYPE_PSEUDO_DOUBLE);
	if (isCharLiteral(literal))
		return (TYPE_CHAR);
	if (isIntLiteral(literal))
		return (TYPE_INT);
	if (isFloatLiteral(literal))
		return (TYPE_FLOAT);
	if (isDoubleLiteral(literal))
		return (TYPE_DOUBLE);
	return (TYPE_INVALID);
}

static void	printChar(double value)
{
	if (std::isnan(value) || std::isinf(value)
		|| value < std::numeric_limits<char>::min()
		|| value > std::numeric_limits<char>::max())
	{
		std::cout << "char: impossible" << std::endl;
		return ;
	}
	char	c = static_cast<char>(value);
	if (!std::isprint(static_cast<unsigned char>(c)))
	{
		std::cout << "char: Non displayable" << std::endl;
		return ;
	}
	std::cout << "char: '" << c << "'" << std::endl;
}

static void	printInt(double value)
{
	if (std::isnan(value) || std::isinf(value)
		|| value < std::numeric_limits<int>::min()
		|| value > std::numeric_limits<int>::max())
	{
		std::cout << "int: impossible" << std::endl;
		return ;
	}
	std::cout << "int: " << static_cast<int>(value) << std::endl;
}

static void	printFloat(double value)
{
	float	f = static_cast<float>(value);

	std::cout << "float: ";
	if (std::isnan(f))
		std::cout << "nanf";
	else if (std::isinf(f))
	{
		if (f < 0)
			std::cout << "-inff";
		else
			std::cout << "+inff";
	}
	else
	{
		if (f == static_cast<int>(f))
			std::cout << std::fixed << std::setprecision(1);
		std::cout << f << "f";
	}
	std::cout << std::endl;
}

static void	printDouble(double value)
{
	std::cout << "double: ";
	if (std::isnan(value))
		std::cout << "nan";
	else if (std::isinf(value))
	{
		if (value < 0)
			std::cout << "-inf";
		else
			std::cout << "+inf";
	}
	else
	{
		if (value == static_cast<int>(value))
			std::cout << std::fixed << std::setprecision(1);
		std::cout << value;
	}
	std::cout << std::endl;
}

static void	printAll(double value)
{
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}

void	ScalarConverter::convert(const std::string &literal)
{
	e_type	type;
	double	value;

	type = detectType(literal);
	if (type == TYPE_INVALID)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return ;
	}
	if (type == TYPE_CHAR)
		value = static_cast<double>(literal[0]);
	else if (type == TYPE_INT)
		value = std::strtod(literal.c_str(), NULL);
	else if (type == TYPE_FLOAT)
		value = static_cast<double>(std::strtof(literal.c_str(), NULL));
	else if (type == TYPE_DOUBLE)
		value = std::strtod(literal.c_str(), NULL);
	else if (type == TYPE_PSEUDO_FLOAT)
		value = static_cast<double>(std::strtof(literal.c_str(), NULL));
	else
		value = std::strtod(literal.c_str(), NULL);
	printAll(value);
}
