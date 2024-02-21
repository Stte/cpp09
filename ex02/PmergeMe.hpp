/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:52:50 by tspoof            #+#    #+#             */
/*   Updated: 2024/02/21 18:40:01 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <exception>

class PmergeMe
{
public:
	template <template <typename...> class Container>
	static void dick_johnson(Container<unsigned int> &seq)
	{
		while (!std::is_sorted(seq.begin(), seq.end()))
		{
			Container<unsigned int> small;
			Container<unsigned int> large;

			for (size_t i = 0; i < seq.size() - 1; i += 2)
			{
				if (seq[i] > seq[i + 1])
				{
					small.push_back(seq[i + 1]);
					large.push_back(seq[i]);
				}
				else
				{
					small.push_back(seq[i]);
					large.push_back(seq[i + 1]);
				}
			}
			if (seq.size() % 2)
				small.push_back(seq.back());
			seq.clear();
			seq.insert(seq.begin(), large.begin(), large.end());
			for (auto &i : small)
			{
				auto it = seq.begin() + PmergeMe::binary_search(seq, i);
				seq.insert(it, i);
			}
		}
	}

	template <template <typename...> class Container>
	static Container<unsigned int> parseInput(char **input)
	{
		Container<unsigned int> container;

		for (int i = 0; input[i]; i++)
		{
			if (input[i][0] == '-')
				throw std::invalid_argument("Invalid argument");
			container.push_back(std::stoi(input[i]));
		}

		if (container.size() <= 1)
			throw std::invalid_argument("Not enough arguments");
		return container;
	}

	template <template <typename...> class Container>
	static void print(Container<unsigned int> container)
	{
		for (typename Container<unsigned int>::iterator it = container.begin(); it != container.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

private:
	template <template <typename...> class Container>
	static size_t binary_search(Container<unsigned int> &seq, unsigned int value)
	{
		size_t left = 0;
		size_t right = seq.size();

		while (left < right)
		{
			size_t mid = left + (right - left) / 2;
			if (seq[mid] < value)
				left = mid + 1;
			else
				right = mid;
		}

		return left;
	}
	PmergeMe();
	~PmergeMe();
};

#endif
