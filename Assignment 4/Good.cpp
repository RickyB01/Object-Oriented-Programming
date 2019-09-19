// Final Project Milestone 3
/***********************************************************
// Name:Ricky Badyal
// Student Number:020028098
// Date:2018-10-15
// Email:jrbadyal@myseneca.ca
// Section:OOP244SAB
***********************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

#include "Good.h"

#define _CRT_SECURE_NO_WARNINGS

using namespace std;
namespace aid {

	Good::Good(char type) {
		GoodType = type;
		GoodOnHand = 0;
		GoodNeeded = 0;
		PriceOfGood = 0.0;
		GoodUnits[0] = '\0';
		GoodSku[0] = '\0';
		GoodName = nullptr;
		TaxableGood = false;
	}

	Good::Good(const char * MgoodSku, const char * MgoodName,
		const char * MgoodUnits, int MgoodonHand, bool MgoodTaxable,
		double MpriceofGood, int MgoodNeeded)
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
		if (Mtype.GoodName != nullptr) {
			GoodName = nullptr;
			*this = Mtype;
		}
	}

	Good & Good::operator=(const Good & Mgoods) {
		if (this != &Mgoods) {
			strncpy(GoodSku, Mgoods.GoodSku, max_sku_length + 1);
			GoodSku[strlen(Mgoods.GoodSku) + 1] = '\0';

			strncpy(GoodUnits, Mgoods.GoodUnits, max_unit_length + 1);
			GoodUnits[strlen(Mgoods.GoodUnits) + 1] = '\0';

			GoodType = Mgoods.GoodType;
			GoodOnHand = Mgoods.GoodOnHand;
			GoodNeeded = Mgoods.GoodNeeded;
			PriceOfGood = Mgoods.PriceOfGood;
			TaxableGood = Mgoods.TaxableGood;

			delete[] GoodName;

			name(Mgoods.GoodName);
		}
		return *this;
	}

	Good::~Good() {
		delete[] GoodName;
		GoodError.clear();
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
			file << std::endl;
		}

		return file;
	}

	std::fstream & Good::load(std::fstream & file) {

		char N_sku[max_sku_length + 1];
		char *N_name = new char[max_name_length + 1];
		char N_unit[max_unit_length + 1];
		char tax;
		int N_on_hand;
		int N_needed;
		double N_price_b4tax;
		bool N_taxable;

		if (file.is_open())
		{
			file.getline(N_sku, max_sku_length, ',');
			N_sku[strlen(N_sku)] = '\0';

			file.getline(N_name, max_name_length, ',');
			N_name[strlen(N_name)] = '\0';

			file.getline(N_unit, max_unit_length, ',');
			N_unit[strlen(N_unit)] = '\0';

			file >> tax;

			if (tax == '1')
				N_taxable = true;
			else if (tax == '0')
				N_taxable = false;

			file.ignore();

			file >> N_price_b4tax;
			file.ignore();

			file >> N_on_hand;
			file.ignore();

			file >> N_needed;
			file.ignore();

			*this = Good(N_sku, N_name, N_unit, N_on_hand, N_taxable, N_price_b4tax, N_needed);
		}
		return file;
	}
	std::ostream & Good::write(std::ostream & os, bool linear) const {
		if (GoodError.isClear()) {


			if (linear) {
				os << setw(max_sku_length) << left << sku() << "|"
					<< setw(20) << left << name() << "|"
					<< setw(7) << fixed << setprecision(2) << right << itemCost() << "|"
					<< setw(4) << right << quantity() << "|"
					<< setw(10) << left << unit() << "|"
					<< setw(4) << right << qtyNeeded() << "|";
			}
			else {
				os << " Sku: " << sku() << endl
					<< " Name (no spaces): " << name() << endl
					<< " Price: " << itemPrice() << endl
					<< " Price after tax: ";

				if (taxed()) {
					os << itemCost() << endl;
				}

				else
				{
					os << " N/A" << endl;

				}
				os << " Quantity on Hand: " << quantity() << " " << unit() << endl
					<< " Quantity needed: " << qtyNeeded();
			}
		}
		else
		{
			os << GoodError.message();
		}
		return os;
	}

	std::istream & Good::read(std::istream & is) {
		char *N_name = new char[max_name_length + 1];
		char tax_input;
		is.clear();

		cout << " Sku: ";
		is >> GoodSku;

		cout << " Name (no spaces): ";
		is >> N_name;
		name(N_name);

		cout << " Unit: ";
		is >> GoodUnits;

		cout << " Taxed? (y/n): ";
		is >> tax_input;

		if (tax_input == 'Y' || tax_input == 'y')
			TaxableGood = true;
		else if (tax_input == 'N' || tax_input == 'n')
			TaxableGood = false;
		else {
			GoodError.message("Only (Y)es or (N)o are acceptable");
			is.setstate(ios::failbit);
			return is;
		}

		if (!is.fail()) {
			cout << " Price: ";
			is >> PriceOfGood;
			if (is.fail()) {
				GoodError.message("Invalid Price Entry");
				is.setstate(ios::failbit);
				return is;
			}

		}

		if (!is.fail()) {
			cout << " Quantity on hand: ";
			is >> GoodOnHand;
			if (is.fail()) {
				GoodError.message("Invalid Quantity Entry");
				is.setstate(ios::failbit);
				return is;
			}
		}

		if (!is.fail()) {
			cout << " Quantity needed: ";
			is >> GoodNeeded;
			cin.ignore();
			if (is.fail()) {
				GoodError.message("Invalid Quantity Needed Entry");
				is.setstate(ios::failbit);
				return is;
			}
		}
		GoodError.clear();

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
		if (GoodName[0] == '\0') {
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

	bool Good::operator>(const char *Msku) const {

		bool result = false;

		if (strcmp(GoodSku, Msku) > 0) {

			result = true;
		}
		return result;
	}


	bool Good::operator>(const iGood& Mgood) const {
		bool result = false;
		if (strcmp(GoodName, Mgood.name()) > 0) {
			result = true;
		}
		return result;
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
		if (GoodName != nullptr) {
			return GoodName;
		}
		else
		{
			return nullptr;
		}

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
		{
			itemCost = itemPrice();
		}

		return itemCost;
	}

	bool Good::isClear() const {
		return GoodError.isClear();
	}

	std::ostream & operator<<(std::ostream & os, const iGood & Mgood) {

		return  Mgood.write(os, true);
	}

	std::istream & operator>>(std::istream & is, iGood & Mgood) {
		return Mgood.read(is);
	}

	double operator+=(double & Mholder, const iGood & Mgood) {

		Mholder += Mgood.total_cost();

		return Mholder;
	}
}