/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:34:09 by tspoof            #+#    #+#             */
/*   Updated: 2024/02/21 18:55:32 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <chrono>
#include <iomanip>
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " [number] [number] ..." << std::endl;
		return (1);
	}
	argv++;

	std::vector<unsigned int> seq_vec = PmergeMe::parseInput<std::vector>(argv);
	std::cout << "Before: " << std::flush;
	PmergeMe::print(seq_vec);
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	PmergeMe::dick_johnson(seq_vec);
	std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> delta_vec = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	std::cout << "After: ";
	PmergeMe::print(seq_vec);

	std::deque<unsigned int> seq_deque = PmergeMe::parseInput<std::deque>(argv);
	// std::cout << "Before: " << std::flush;
	// PmergeMe::print(seq_deque);
	start = std::chrono::high_resolution_clock::now();
	PmergeMe::dick_johnson(seq_deque);
	stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> delta_seq = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
	// std::cout << "After: ";
	// PmergeMe::print(seq_deque);

	std::cout << "Time to process a range of " << seq_vec.size() << " elements with std::vector: "
			  << std::fixed << std::setprecision(6) << delta_vec.count() << " seconds" << std::endl;
	std::cout << "Time to process a range of " << seq_deque.size() << " elements with std::deque: "
			  << std::fixed << std::setprecision(6) << delta_seq.count() << " seconds" << std::endl;

	return (0);
}
