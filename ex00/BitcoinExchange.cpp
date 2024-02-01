#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &dataBase)
{
	setExchangeRates(dataBase, exchangeRates);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	exchangeRates = other.exchangeRates;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		exchangeRates = other.exchangeRates;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::printResult(const std::string &inputFile)
{
	std::ifstream file(inputFile);
	if (!file)
		throw std::runtime_error("Error: Could not open input file.");

	std::string line;
	std::getline(file, line);
	size_t delimeter;
	while (getline(file, line))
	{
		delimeter = line.find("|");
		std::string date = line.substr(0, delimeter - 1);
		if (!exchangeRates.count(date))
		{
			if (findClosestDate(date) == false)
				continue ;

		}
		double value;
		try
		{
			value = std::stod(line.substr(delimeter + 2));
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "Invalid argument: " << e.what() << std::endl;
			continue;
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Out of Range error: " << e.what() << std::endl;
			continue;
		}
		if (value < 0)
			std::cerr << "Error: not a positive number." << std::endl;
		else if (value > 1000)
			std::cerr << "Error: too large a number." << std::endl;
		else
			std::cout << date << " => " << value << " = " << exchangeRates[date] * value << std::endl;
	}

}

void BitcoinExchange::setExchangeRates(const std::string &dataBase, std::map<std::string, double> &exchangeRates)
{
	std::ifstream file(dataBase);
	if (!file)
		throw std::runtime_error("Error: Could not open data file.");

	std::string line;
	std::getline(file, line);
	size_t delimeter;
	while (getline(file, line))
	{
		delimeter = line.find(',');
		std::string date = line.substr(0, delimeter);
		double rate = std::stod(line.substr(delimeter + 1));
		exchangeRates[date] = rate;
	}
}

bool BitcoinExchange::findClosestDate(std::string &date)
{
	int year, month, day;

	std::istringstream ss(date);
	std::tm tm = {};
	ss >> std::get_time(&tm, "%Y-%m-%d");

	if (ss.fail() || std::mktime(&tm) == static_cast<std::time_t>(-1))
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}
	year = tm.tm_year + 1900; // Note: tm_year is years since 1900
	month = tm.tm_mon + 1; // Note: tm_mon is zero-based
	day = tm.tm_mday;

	std::ostringstream validDateTest;
	validDateTest << year << '-'
			<< std::setw(2) << std::setfill('0') << month << '-'
			<< std::setw(2) << std::setfill('0') << day;

	if (validDateTest.str().compare(date))
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}

	while (year > 2008)
	{
		while (month > 0)
		{
			while (day)
			{
				std::ostringstream convert;
				convert << year << '-'
						<< std::setw(2) << std::setfill('0') << month << '-'
						<< std::setw(2) << std::setfill('0') << day;
				std::string nearestDate(convert.str());

				if (exchangeRates.count(nearestDate))
				{
					date = nearestDate;
					return true;
				}
				day--;
			}
		day = 31;
		month--;
		}
	month = 12;
	year--;
	}
	std::cerr << "Error: bad input => " << date << std::endl;
	return false;
}
