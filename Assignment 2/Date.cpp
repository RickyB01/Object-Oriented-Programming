// Final Project Milestone 1
/***********************************************************
// Name:Ricky Badyal
// Student Number:020028098
// Email:jrbadyal@myseneca.ca
// Section:OOP244SAB
***********************************************************/
/////////////////////////////////////////////////////////////////
#include "Date.h"

namespace aid {

	// number of days in month mon and year year
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	Date::Date() {
		year = 0000;
		month = 00;
		day = 00;
		the_comparator = 0;
		error_state = NO_ERROR;
	}

	Date::Date(int nyear, int nmonth, int nday) {
		year = nyear;
		month = nmonth;
		day = nday;

		the_comparator = nyear * 372 + nmonth * 31 + nday;
		error_state = NO_ERROR;

		if (year < min_year || year > max_year) {

			*this = Date();
			error_state = YEAR_ERROR;
		}

		else if (month < 1 || month > 12) {

			*this = Date();
			error_state = MON_ERROR;
		}

		else if (day < 1 || day >mdays(month, year)) {

			*this = Date();
			error_state = DAY_ERROR;

		}



	}

	void Date::errCode(int errorCode) {

		error_state = errorCode;
	}

	// Operators:

	bool Date::operator!=(const Date& rhs) const {
		bool results;
		if (the_comparator == rhs.the_comparator) {

			results = false;
		}
		else {
			results = true;
		}

		return results;

	}

	bool Date::operator==(const Date& rhs) const {
		if (this->year == rhs.year && this->month == rhs.month && this->day == rhs.day)
			return true;
		else
			return false;
	}

	bool Date::operator<(const Date& rhs)const {
		if (this->year < rhs.year)
			return true;
		else if (this->year == rhs.year && this->month < rhs.month)
			return true;
		else if (this->year == rhs.year && this->month == rhs.month && this->day < rhs.day)
			return true;
		else
		return false;
	}

	bool Date::operator>(const Date& rhs) const {

		if (the_comparator < rhs.the_comparator)
			return false;
		else
			return true;
	}

	bool Date::operator>=(const Date& rhs)const {

		if (the_comparator >= rhs.the_comparator)
			return true;
		else
			return false;
	}

	bool Date::operator<=(const Date& rhs)const {

		if (the_comparator <= rhs.the_comparator)
			return true;
		else
			return false;

	}

	// Quereies & Modifers:

	int Date::errCode() const {

		return error_state;

	}

	bool Date::bad() const {

		if (error_state != NO_ERROR)
			return true;
		else
			return false;

	}

	std::ostream& Date::write(std::ostream& ostr) const {

		ostr.fill('0');
		ostr << year << '/';

		ostr.width(2);
		ostr << month << '/';

		ostr.width(2);
		ostr << day;

		return ostr;


	}

	std::istream& Date::read(std::istream& istr) {
		char divide;

		istr >> year >> divide >> month >> divide >> day;
		this->the_comparator = year * 372 + month * 31 + day;

		if (istr.fail()) {

			*this = Date();
			errCode(CIN_FAILED);
		}

		else if (year < min_year || year > max_year)
 {

			*this = Date();
			errCode(YEAR_ERROR);

		}

		else if (1 > month || month > 12) {

			*this = Date();
			errCode(MON_ERROR);

		}


		else if (day > mdays(month, year)) {

			*this = Date();
			errCode(DAY_ERROR);

		}

		else if (this->the_comparator < min_date) {
			*this = Date();
			errCode(PAST_ERROR);
		}

		else if (day % 4 == 0) {
			if (day % 100 == 0) {
				if (day % 400 == 0)
					*this = Date();
				errCode(PAST_ERROR);
			}
		}

		istr.clear();
		return istr;

	}

	std::istream& operator>>(std::istream& istr, Date& obj1) {

		return obj1.read(istr);
	}

	std::ostream& operator<<(std::ostream& ostr, Date& obj2) {

		return obj2.write(ostr);
	}



}
