#include "Date.h"
#include <stdlib.h>

using namespace std;

bool isLeapYear(int Year) {
	if (!(Year % 400)) return 1;
	if (Year % 100) return 0;

	return !(Year % 4);
}

U_Int32 getDayCount(int Year, int Month) {
	const static Octet CountOfMonth[] = {
		0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

	U_Int32 Day = CountOfMonth[Month];

	if (Month == 2) Day += isLeapYear(Year);

	return Day;
}

Date::Date(U_Int32 Year, U_Octet Month, U_Octet Day) {
	if (Year < 1900) Month = Year = 0;
	if (Year > 9999) Year = 9999;
	if (Month > 12) Month = 12;
	
	this->Year = Year;
	this->Month = Month;
	this->Day = min((int)getDayCount(Year, Month), (int)Day);
}

U_Int32 Date::getYear() {
	return this->Year;
}

U_Int32 Date::getMonth() {
	return this->Month;
}

U_Int32 Date::getDay() {
	return this->Day;
}

string Date::toString() {
	string Result = "(";

	Result += to_string(this->getYear()) + "/";
	Result += ((this->getMonth() < 10) ? "0" : "") + to_string(this->getMonth()) + "/";
	Result += ((this->getDay() < 10) ? "0" : "") + to_string(this->getDay()) + ")";

	return Result;
}

bool Date::operator<(Date Another) {
	if (this->getYear() < Another.getYear()) return 1;
	if (this->getYear() > Another.getYear()) return 0;

	if (this->getMonth() < Another.getMonth()) return 1;
	if (this->getMonth() > Another.getMonth()) return 0;

	return this->getDay() < Another.getDay();
}

bool Date::operator>(Date Another) {
	return Another < (*this);
}

bool Date::operator==(Date Another) {
	return !((*this) < Another) && !((*this) > Another);
}

bool Date::operator<=(Date Another) {
	return !((*this) > Another);
}

bool Date::operator>=(Date Another) {
	return !((*this) < Another);
}