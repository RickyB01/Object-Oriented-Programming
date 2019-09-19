// Final Project Milestone 3
/***********************************************************
// Name:Ricky Badyal
// Student Number:020028098
// Email:jrbadyal@myseneca.ca
// Section:OOP244SAB
***********************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
//#include <memory>
#include "Error.h"

#include "Good.h"

#define _CRT_SECURE_NO_WARNINGS


using namespace std;
namespace aid {

	Good::Good(char type = 'N') {
		GoodType = type;
	}

	Good::Good(const char * MgoodSku, const char * MgoodName,
		const char * MgoodUnits, int MgoodonHand, bool MgoodTaxable,
		double MpriceofGood, int MgoodNeeded) : Good()
	{
		strncpy(GoodSku, MgoodSku, max_sku_length);
		GoodSku[max_sku_length - 1] = '\0';
		strncpy(GoodUnits, MgoodUnits, max_unit_length);
		GoodUnits[max_unit_length - 1] = '\0';

		name(MgoodName);
		GoodOnHand = MgoodonHand;
		GoodNeeded = MgoodNeeded;
		PriceOfGood = MpriceofGood;
		TaxableGood = MgoodTaxable;
	}

	Good::Good(const Good & Mtype) {
		*this = Mtype;
	}

	Good & Good::operator=(const Good & Mgoods) {
		GoodType = Mgoods.GoodType;
		strcpy(GoodSku, Mgoods.GoodSku);
		strcpy(GoodUnits, Mgoods.GoodUnits);
		name(Mgoods.GoodName);
		GoodOnHand = Mgoods.GoodOnHand;
		GoodNeeded = Mgoods.GoodNeeded;
		PriceOfGood = Mgoods.PriceOfGood;
		TaxableGood = Mgoods.TaxableGood;

		return *this;

	}

	Good::~Good() {
		delete[] GoodName;
	}

	std::fstream & Good::store(std::fstream & file, bool newLine) const {
		file << GoodType << ','
			<< GoodSku << ','
			<< GoodName << ','
			<< GoodUnits << ','
			<< TaxableGood << ','
			<< PriceOfGood << ','
			<< GoodOnHand << ','
			<< GoodNeeded;

		if (newLine) {
			file << endl;
		}

		return file;
	}

	std::fstream & Good::load(std::fstream & file) {
	
		char nSku[max_sku_length];

		char nName[max_name_length];

		char nUnit[max_unit_length];

		double price;

		int quantity, required;

		char tax;

		file.open("ms3.txt");
		file >> nSku;
		file >> nName;
		file >> nUnit;
		file >> tax;
		file >> price;
		file >> quantity;
		file >> required;
		file.clear();
		file.close();

		Good temp;

		temp = Good(nSku, nName, nUnit, tax, price, quantity, required);

		return file;
		
	}

	std::ostream & Good::write(std::ostream & os, bool linear) const {

		if (linear) {
			os << setw(max_sku_length) << left << GoodSku << '|'
				<< setw(20) << left << GoodName << '|'
				<< setw(7) << right << fixed << setprecision(2) << itemCost() << '|'
				<< setw(4) << right << GoodOnHand << '|'
				<< setw(10) << left << GoodUnits << '|'
				<< setw(4) << right << GoodNeeded << '|';
		}
		else {

			os << " Sku: " << GoodSku << endl
				<< " Name (no spaces): " << GoodName << endl
				<< " Price: " << PriceOfGood << endl;

			if (TaxableGood) {
				os << " Price after tax: " << itemCost() << endl;
			}
			else {
				os << " Price after tax: N/A" << endl;
			}

			os << " Quantity on Hand: " << GoodOnHand << ' ' << GoodUnits << endl
				<< " Quantity needed: " << GoodNeeded;
		}
		return os;
	}

	std::istream & Good::read(std::istream & is) {

		char taxed;
		char * address = new char[max_name_length + 1];
		int qty, need;
		double _price;

		if (!is.fail()) {

			cout << " Sku: ";

			is >> GoodSku;

			cin.ignore();

			cout << " Name (no spaces): ";

			is >> address;
			name(address);

			cout << " Unit: ";
			is >> GoodUnits;

			cout << " Taxed? (y/n): ";
			is >> taxed;

			if (!is.fail()) {

				if (taxed) {

					bool y_valid = taxed == 'y' || taxed == 'Y';
					bool n_valid = taxed == 'n' || taxed == 'N';

					if (y_valid) {
						TaxableGood = true;
					}

					if (n_valid) {
						TaxableGood = false;
					}

					if (!(y_valid || n_valid)) {
						is.setstate(std::ios::failbit);
						GoodError.message("Only (Y)es or (N)o are acceptable");
						return is;
					}
				}
			}
			else {
				is.setstate(std::ios::failbit);
				GoodError.message("Only (Y)es or (N)o are acceptable");
				return is;
			}
			cout << " Price: ";
			is >> _price;

			if (is.fail()) {
				GoodError.clear();
				is.setstate(ios::failbit);
				GoodError.message("Invalid Price Entry");
				return is;
			}
			else {
				PriceOfGood = _price;
			}

			cout << " Quantity on hand: ";
			is >> qty;

			if (is.fail()) {
				GoodError.clear();
				GoodError.message("Invalid Quantity Entry");
				is.setstate(ios::failbit);

				return is;
			}
			else {
				quantity(qty);
			}

			cout << " Quantity needed: ";
			is >> need;
			cin.ignore();

			if (is.fail()) {
				GoodError.clear();
				GoodError.message("Invalid Quantity Needed Entry");
				is.setstate(ios::failbit);
				return is;
			}
			else {
				GoodNeeded = need;
			}

			if (!is.fail()) {
				GoodError.clear();
			}
		}
		return is;
	}

	void Good::message(const char * message) {
		GoodError.message(message);
	}

	bool Good::operator==(const char * Msku) const {

		bool result = false;
		if (strcmp(Msku, GoodSku) == 0) {
			
			result = true;
		}
		
		return result;
	}
		

	double Good::total_cost() const {
		return GoodOnHand * itemCost();
	}

	void Good::quantity(int GoodQuantity) {
		GoodOnHand = GoodQuantity;
	}

	bool Good::isEmpty() const {
		bool result = false;
		if(GoodName[0] == '\0'){
			result = true;
		}

		return result;

	}

	int Good::qtyNeeded() const {
		return GoodNeeded;
	}

	int Good::quantity() const {
		return GoodOnHand;
	}

	bool Good::operator>(const char * Msku) const {
		bool result = false;
		if (strcmp(GoodSku, Msku) > 0)
		{
			result = true;
		}
		return result;
	}

	bool Good::operator>(const Good & Mgood) const {
		if (strcmp(GoodName, Mgood.name()) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	int Good::operator+=(int Munits) {
		if (Munits > 0) 
		{
			GoodOnHand += Munits;
			return GoodOnHand;
		}
		else 
		{
			return GoodOnHand;
		}
	}

	void Good::name(const char * MgoodName) {
		int len = strlen(MgoodName);

		if (MgoodName != nullptr || MgoodName[0] != '\0') {
			GoodName = new char[len + 1];
			strncpy(GoodName, MgoodName, len);
			GoodName[strlen(MgoodName)] = '\0';

		}
	}

	const char * Good::name() const {
		return GoodName;
	}

	const char * Good::sku() const {
		return GoodSku;
	}

	const char * Good::unit() const {
		return GoodUnits;
	}

	bool Good::taxed() const {
		return TaxableGood;
	}

	double Good::itemPrice() const {
		return PriceOfGood;
	}

	double Good::itemCost() const {

		double itemCost;
		if (taxed()) 
		{
			itemCost = itemPrice()*(1 + TaxRate);
		}
		else 
		{ itemCost = itemPrice();}

		return itemCost;
	}

	bool Good::isClear() const {
		if (GoodError.isClear()) {
			return true;
		}
		else {
			return false;
		}
	}

	std::ostream & operator<<(std::ostream & os, const Good & Mgood) {
		// TODO: insert return statement here
		return  Mgood.write(os, true);
	}

	std::istream & operator>>(std::istream & is, Good & Mgood) {
		// TODO: insert return statement here
		return Mgood.read(is);
	}

	double operator+=(double & Mholder, const Good & Mgood) {
		
		Mholder += Mgood.total_cost();
		
		return Mholder;
	}
}

			






