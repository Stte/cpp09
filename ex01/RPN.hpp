/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:35:55 by tspoof            #+#    #+#             */
/*   Updated: 2024/02/20 14:12:41 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <stdexcept>

class RPN
{
public:
	static double calc(std::string &expr);

private:
	RPN();
	~RPN();
	RPN(const RPN &rpn);
	RPN &operator=(const RPN &rpn);

	static bool is_operator(char c);
};

#endif
