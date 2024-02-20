/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:36:36 by tspoof            #+#    #+#             */
/*   Updated: 2024/02/20 14:21:13 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool RPN::is_operator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	return false;
}

typedef double (*operation)(double, double);

double RPN::calc(std::string &expr)
{
	std::stack<float> stack;
	static const std::string operators = "+-*/";
	static const operation calculate[] = {
		[](double a, double b)
		{ return a + b; },
		[](double a, double b)
		{ return a - b; },
		[](double a, double b)
		{ return a * b; },
		[](double a, double b)
		{ return a / b; }};

	for (char c : expr)
	{
		if (c == ' ')
			continue;
		if (!isdigit(c) && !is_operator(c))
			throw std::invalid_argument("Invalid character in expression");
		if (isdigit(c))
			stack.push(c - '0');
		else if (is_operator(c))
		{
			double right = stack.top();
			stack.pop();
			double left = stack.top();
			stack.pop();
			size_t op = operators.find(c);
			stack.push(calculate[op](left, right));
		}
	}
	if (stack.size() != 1)
		throw std::invalid_argument("Invalid expression");

	return stack.top();
}
