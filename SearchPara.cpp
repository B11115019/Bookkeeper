#include "SearchPara.h"

using namespace std;

const U_Octet Mask_Tag = 0b001;
const U_Octet Mask_Date = 0b010;
const U_Octet Mask_Name = 0b100;

SearchPara::SearchPara(bool useTag, bool useDate, bool useName) {
	if (useTag) this->SearchCriteria |= Mask_Tag;

	if (useDate) this->SearchCriteria |= Mask_Date;

	if (useName) this->SearchCriteria |= Mask_Name;
}

bool SearchPara::isSearchByTag() {
	if (this->getTargetTag().empty()) return 0;

	return (this->SearchCriteria & Mask_Tag);
}

bool SearchPara::isSearchByDate() {
	if (!this->getTargetDate().getYear()) return 0;

	return (this->SearchCriteria & Mask_Date);
}

bool SearchPara::isSearchByName() {
	if (this->getTargetName().empty()) return 0;

	return (this->SearchCriteria & Mask_Name);
}

void SearchPara::setTargetTag(string Target) {
	this->TargetTag = Target;
}

void SearchPara::setTargetDate(Date Target) {
	this->TargetDate = Target;
}

void SearchPara::setTargetName(string Target) {
	this->TargetName = Target;
}

string SearchPara::getTargetTag() {
	return this->TargetTag;
}

Date SearchPara::getTargetDate() {
	return this->TargetDate;
}

string SearchPara::getTargetName() {
	return this->TargetName;
}

string SearchPara::toString() {
	bool HasTarget = 0;
	string Result = "Search targets:\n";

	if (this->isSearchByTag())
		Result += "\tTag : " + this->getTargetTag() + "\n", HasTarget = 1;
	
	if (this->isSearchByName())
		Result += "\tName : " + this->getTargetName() + "\n", HasTarget = 1;

	if (this->isSearchByDate()) {
		Date D = this->getTargetDate();

		Result += "\tDate : " + to_string(D.getYear()), HasTarget = 1;

		if (D.getMonth())
			Result += (D.getMonth() < 10 ? "/0" : "/") + to_string(D.getMonth());

		if (D.getDay())
			Result += (D.getDay() < 10 ? "/0" : "/") + to_string(D.getDay());
	}

	if (!HasTarget) Result += "\tThere are no valid search targets.";

	return Result;
}