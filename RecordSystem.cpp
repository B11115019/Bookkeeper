#include "RecordSystem.h"

using namespace std;

RecordSystem Database;

RecordSystem::RecordSystem() {}

RecordSystem::~RecordSystem() {}

void RecordSystem::insertRecord(Record record) {
    U_Int32 uuid = record.getId();
    this->records.emplace(uuid, record);
}

void RecordSystem::removeRecord(const U_Int32& uuid) {
    this->records.erase(uuid);
}

void RecordSystem::removeRecords(SearchPara para) {
    std::vector<Record> removeList = this->getRecords(para);
    for (const auto& record : removeList) {
        this->removeRecord(record.getId());
    }
}

Record RecordSystem::getRecord(const U_Int32& uuid) const {
    return this->records.at(uuid);
}

std::vector<Record> RecordSystem::getRecords(SearchPara para) const {
    std::vector<Record> result;

    for (const auto& [uuid, record] : this->records) {
        if (para.isSearchByTag() && !record.containsTag(para.getTargetTag())) {
            continue;
        }
        if (para.isSearchByName() && record.getName().find(para.getTargetName()) == std::string::npos) {
            continue;
        }
        if (para.isSearchByDate()) {
            Date date = record.getDate();
            Date targetDate = para.getTargetDate();
            if (targetDate.getYear() != 0 && targetDate.getYear() != date.getYear()) {
                continue;
            }
            if (targetDate.getMonth() != 0 && targetDate.getMonth() != date.getMonth()) {
                continue;
            }
            if (targetDate.getDay() != 0 && targetDate.getDay() != date.getDay()) {
                continue;
            }
        }

        result.push_back(record);
    }

    std::sort(result.begin(), result.end(), [](const Record& a, const Record& b) {
        return a.getDate() < b.getDate();
    });

    return result;
}