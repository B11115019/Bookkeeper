#include "tagCounter.h"
#include "Definitions.h"
#include "RecordSystem.h"

using namespace std;

unordered_map<string, U_Int32> TagCount;

void init()
{
	vector<Record>all_records = Database.getRecords(SearchPara(false, false, false));
	for (const Record& record : all_records)
	{
		vector<string> tags = record.getTags();
		for (const string tag : tags)
		{
			TagCount[tag]++;
		}
	}
}

void addTag(string& tag)
{
	TagCount[tag]++;
}

void removeTag(string& tag)
{
	TagCount[tag]--;
}

U_Int32 getTagCount(string& tag)
{
	return TagCount[tag];
}

std::vector<std::string> getAllTag()
{
	std::vector<std::string> res;

	for (auto& [key, value] : TagCount)
	{
		if(value != 0)
			res.push_back(key);
	}

	return res;
}
