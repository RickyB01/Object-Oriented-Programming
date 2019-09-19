// Final Project Milestone 5
/***********************************************************
// Name:Ricky Badyal
// Student Number:020028098
// Date:2018-11-30
// Email:jrbadyal@myseneca.ca
// Section:OOP244SAB
***********************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include "Perishable.h"

namespace aid {

	Perishable::Perishable() :Good::Good('P') {
		expDate = Date();

	}

	std::fstream& Perishable::store(std::fstream& file, bool newline) const {
		Good::store(file, false);
		file << "," << Date(expDate);
		{
			file << endl;
		}
		return file;

	}

	std::fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		expDate.read(file);
		file.ignore();
		return file;
	}

	std::ostream & Perishable::write(std::ostream & os, bool linear) const {

		Good::write(os, linear);
		if (this->isClear()) {

			if (linear == true) {
				expDate.write(os);
			}
			else {
				os << "\n Expiry date: ";
			}
		}
		return os;
	}

    std::istream & Perishable::read(std::istream & is) 
	{
		Date mem;
		is.clear();

		if (Good::read(is)) {
			std::cout << " Expiry date (YYYY/MM/DD): ";
			is >> mem;

			if (mem.errCode() != 0) {
				is.setstate(std::ios::failbit);

				switch (mem.errCode())
				{
				case CIN_FAILED:
					Good::message("Invalid Date Entry");
					break;
				case YEAR_ERROR:
					Good::message("Invalid Year in Date Entry");
					break;
				case MON_ERROR:
					Good::message("Invalid Month in Date Entry");
					break;
				case DAY_ERROR:
					Good::message("Invalid Day in Date Entry");
					break;
				case PAST_ERROR:
					Good::message("Invalid Expiry in Date Entry");
					break;
				default:
					break;
				}
			}
		}
		if (!is.fail()) {
			expDate = mem;
		}
		return is;
	}


	const Date& Perishable::expiry() const {

		return expDate;
	}

	
	
}