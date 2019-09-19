// Final Project Milestone 3
/***********************************************************
// Name:Ricky Badyal
// Student Number:020028098
// Date:2018-10-15
// Email:jrbadyal@myseneca.ca
// Section:OOP244SAB
***********************************************************/



#ifndef AMA_ERROR_STATE_H
#define AMA_ERROR_STATE_H
#include <iostream>
#include <cstring>
#include <string>


namespace aid {

	class Error {

		char* Erorrmsge;

	public:

		explicit Error(const char* errorMessage = nullptr);
		Error(const Error& em) = delete;
		Error& operator=(const Error& em) = delete;
		virtual ~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
		bool isEmpty() const;

	};

	// helper operator:

	std::ostream& operator<<(std::ostream&, const Error&);



}

#pragma once
#endif
