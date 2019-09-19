// Final Project Milestone 3
/***********************************************************
// Name:Ricky Badyal
// Student Number:020028098
// Date:2018-10-15
// Email:jrbadyal@myseneca.ca
// Section:OOP244SAB
***********************************************************/

#include <iostream>
#include <cstring>
#include "Error.h"



using namespace std;

namespace aid {

	Error::Error(const char * errorMessage) {
		if (errorMessage == nullptr)
			Erorrmsge = nullptr;

		else if (strcmp(errorMessage, "") == 0)
			Erorrmsge = nullptr;

		else {
			Erorrmsge = new char[strlen(errorMessage) + 1];
			strncpy(Erorrmsge, errorMessage, strlen(errorMessage) + 1);
		}

	}

	Error::~Error() {
		delete[] Erorrmsge;
		Erorrmsge = nullptr;
	}

	void Error::message(const char * str) {
		delete[] Erorrmsge;
		Erorrmsge = new char[strlen(str) + 1];
		strncpy(Erorrmsge, str, (strlen(str) + 1));


	}

	void Error::clear() {
		delete[] this->Erorrmsge;
		Erorrmsge = nullptr;

	}

	bool Error::isClear() const {
		if (Erorrmsge == nullptr)
			return true;
		else
			return false;

	}

	bool Error::isEmpty() const {

		if (Erorrmsge != 0) {
			return false;
		}
		else {
			return true;
		}

	}

	const char * Error::message() const {

		return Erorrmsge;

	}

	std::ostream& operator<<(std::ostream&  ostr, const Error& tml) {

		if (!tml.isClear()) {

			ostr << tml.message();
		}

		return ostr;

	}


}

