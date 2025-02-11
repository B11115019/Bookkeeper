#pragma once
#include "Definitions.h"
#include "Date.h"
#include <unordered_set>

class Record {
	private:
		RecordType Type = RecordType::Expense;
		U_Int64 Amount = 0;
		std::string Name = "";
		Date RecordDate = Date(0, 0, 0);
		std::unordered_set<std::string> Tags;
		U_Int32 ID = 0xffffffffu;

	public:
		~Record();

		Record();

		// 使用「收支類型」來初始化。
		Record(RecordType);

		// 使用「收支類型」與「金額」來初始化。
		Record(RecordType, U_Int64);

		// 使用「收支類型」與「名稱」來初始化。
		Record(RecordType, std::string);

		// 使用「收支類型」、「名稱」與「金額」來初始化。
		Record(RecordType, std::string, U_Int64);

		// 取得該筆消費(支出)的名稱。
		std::string getName() const;

		// 設定該筆消費(支出)的名稱。
		void setName(std::string);

		// 檢查該筆消費(支出)是否包含給定的 Tag。
		bool containsTag(std::string) const;				

		// 為該筆消費(支出)新增一個 Tag。
		void insertTag(std::string);	

		// 為該筆消費(支出)移除一個指定的 Tag。
		void removeTag(std::string);

		// 取得該筆消費(支出)的所有 Tag。
		std::vector<std::string> getTags() const;

		// 取得該筆資料的收支類型。
		RecordType getType() const;				

		// 設定該筆資料的收支類型。
		void setType(RecordType);					

		// 取得該筆消費(支出)的金額。
		U_Int64 getAmount() const;

		// 設定該筆消費(支出)的金額。
		void setAmount(U_Int64);

		// 取得該筆消費(支出)的日期。
		Date getDate() const;

		// 設定該筆消費(支出)的日期。
		void setDate(Date);

		// 取得該筆資料的 ID。
		U_Int32 getId() const;

		// 以字串表達物件全資訊，通常用於 Debug 直接輸出。
		std::string toString() const;	
};