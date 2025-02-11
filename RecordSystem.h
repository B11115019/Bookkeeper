#pragma once
#include "Record.h"
#include "SearchPara.h"

#include <unordered_map>
#include <algorithm>
#include <queue>

class RecordSystem {
	private:
		// All records
		std::unordered_map<U_Int32, Record> records;

	public:
		RecordSystem();
		~RecordSystem();

		/* Functions */
		
		/**
		 * Insert a record into the database
		 * 
		 * @param record The record to be inserted
		 */
		void insertRecord(Record record);

		/**
		 * Remove a record from the database
		 * 
		 * @param uuid The UUID of the record to be removed
		 */
		void removeRecord(const U_Int32& uuid);

		/**	
		 * Remove the records that match the search parameters from the database
		 * 
		 * @param para The search parameters
		 */
		void removeRecords(SearchPara para);

		/* Getter */	
		/**
		 * Get a record from the database
		 * 
		 * @param uuid The UUID of the record to be retrieved
		 * @return The record with the given UUID
		 */
		Record getRecord(const U_Int32& uuid) const;

		/**
		 * Get records from the database
		 * 
		 * @param para The search parameters (default: all records)
		 * @return The records that match the search parameters
		 */
		std::vector<Record> getRecords(SearchPara para = SearchPara(false, false, false)) const;
};

extern RecordSystem Database;