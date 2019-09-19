// Final Project Milestone 3
/***********************************************************
// Name:Ricky Badyal
// Student Number:020028098
// Date:2018-10-15
// Email:jrbadyal@myseneca.ca
// Section:OOP244SAB
***********************************************************/
#ifndef aid_good_h
#define aid_good_h

#include <iostream>
#include "Error.h"
#include "iGood.h"


namespace aid {


	const int  max_sku_length = 7;
	const int  max_unit_length = 10;
	const int  max_name_length = 75;
	const double TaxRate = 0.13;


	class Good : public iGood
	{

		char GoodType;
		char GoodSku[max_sku_length + 1];
		char GoodUnits[max_unit_length + 1];
		char* GoodName;
		int GoodOnHand;
		int GoodNeeded;
		double PriceOfGood;
		bool TaxableGood;
		
	protected:

		Error GoodError;

		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;

	public:
	
		Good(char Mytpe ='N');
		Good(const char* MgoodSku, const char* MgoodUnits, const char* MgoodName, int MGoodonHand = 0, bool MtaxableGood = true, double Mprice = 0.0, int MGoodNeeded = 0);
		Good(const Good& Mgood);
		Good& operator =(const Good& Mgood);
		~Good();

		

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		bool operator==(const char* Msku) const;
		double total_cost() const;
		void quantity(int Mquaty);

		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char* Mgood) const;
		bool operator>(const iGood& Mgood) const;
		int operator+=(int Munits);


	};

	std::ostream& operator<<(std::ostream&, const iGood& Mgood);
	std::istream& operator>>(std::istream&, iGood& Mgood);
	double operator+=(double& Mholder, const iGood& Mgood);


}

#endif 