// Final Project Milestone 5
/***********************************************************
// Name:Ricky Badyal
// Student Number:020028098
// Date:2018-10-15
// Email:jrbadyal@myseneca.ca
// Section:OOP244SAB
***********************************************************/
#ifndef AMA_DATE_H
#define AMA_DATE_H

#include <iostream>

namespace aid {

#define NO_ERROR 0
#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3
#define YEAR_ERROR 4
#define PAST_ERROR 5


	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;


	class Date {

		int year;
		int month;
		int day;
		int the_comparator;
		int error_state;

		void errCode(int);

		int mdays(int, int)const;

	public:

		Date();
		Date(int year, int month, int day);

		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		// Queries and modifier

		int errCode() const;
		bool bad() const;

		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;




	};

	// Helper Functions:

	std::istream& operator>>(std::istream& istr, Date&);
	std::ostream& operator<<(std::ostream& ostr, const Date&);






}
#endif
