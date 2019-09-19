// Final Project Milestone 5
/***********************************************************
// Name:Ricky Badyal
// Student Number:020028098
// Date:2018-11-30
// Email:jrbadyal@myseneca.ca
// Section:OOP244SAB
***********************************************************/


#ifndef AID_PERISABLE_H
#define AID_PERISHABLE_H
#include "Good.h"
#include "Date.h"

namespace aid {

	class Perishable : public Good {

		Date expDate;

	public:

		Perishable();

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		const Date& expiry() const;

	};
}



#endif 