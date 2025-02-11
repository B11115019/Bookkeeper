#include "Record.h"

using namespace std;

U_Int32 generateNewID() {
	static U_Int32 NextID = 0;

	return NextID++;
}

Record::~Record() {
	
}

Record::Record() {
	this->ID = generateNewID();
}

Record::Record(RecordType Type) {
	this->Type = Type;

	this->ID = generateNewID();
}

Record::Record(RecordType Type, U_Int64 Amount) {
	this->Type = Type;
	this->Amount = Amount;

	this->ID = generateNewID();
}

Record::Record(RecordType Type, string Name) {
	this->Type = Type;
	this->Name = Name;

	this->ID = generateNewID();
}

Record::Record(RecordType Type, string Name, U_Int64 Amount) {
	this->Type = Type;
	this->Name = Name;
	this->Amount = Amount;

	this->ID = generateNewID();
}

string Record::getName() const {
	return this->Name;
}

void Record::setName(string Name) {
	this->Name = Name;
}

bool Record::containsTag(string Tag) const {
	return Tags.count(Tag);
}

void Record::insertTag(string Tag) {
	this->Tags.insert(Tag);
}

void Record::removeTag(string Tag) {
	if (this->containsTag(Tag)) this->Tags.erase(Tag);
}

vector<string> Record::getTags() const {
	int Index = 0;
	vector<string> Result(Tags.size());
	unordered_set<string>::const_iterator I;

	for (I = Tags.begin(); I != Tags.end(); ++I) Result[Index++] = *I;

	return Result;
}

RecordType Record::getType() const {
	return this->Type;
}

void Record::setType(RecordType Type) {
	this->Type = Type;
}

U_Int64 Record::getAmount() const {
	return this->Amount;
}

void Record::setAmount(U_Int64 Amount) {
	this->Amount = Amount;
}

Date Record::getDate() const {
	return this->RecordDate;
}

void Record::setDate(Date D) {
	this->RecordDate = D;
}

U_Int32 Record::getId() const {
	return this->ID;
}

string Record::toString() const {
	string Result = "Record information : \n";

	Result += "\tID : " + to_string(this->getId()) + "\n";

	Result += "\tName : " + this->getName() + "\n";

	Result += "\tAmount : " + to_string(this->getAmount()) + "\n";

	switch (this->getType()) {
		case RecordType::Expense: {
			Result += "\tType : Expense\n";
			break;
		}

		case RecordType::Income: {
			Result += "\tType : Income\n";
			break;
		}

		default: {
			break;
		}
	}

	Result += "\tDate : " + this->getDate().toString() + '\n';

	vector<string> TagArr = this->getTags();

	Result += "\tTags : ";

	for (int i = 0; i < TagArr.size(); ++i) {
		if (i) Result += ", ";

		Result += TagArr[i];
	}

	return Result;
}