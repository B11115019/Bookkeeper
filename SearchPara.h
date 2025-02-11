#pragma once
#include "Definitions.h"
#include "Date.h"

struct SearchPara {
	private:
		U_Octet SearchCriteria = 0;
		std::string TargetTag = "", TargetName = "";
		Date TargetDate = Date(0, 0, 0);

	public:
		// 是否啟用搜尋條件「Tag」、「日期」、「名稱」。
		SearchPara(bool, bool, bool);

		//「Tag」是否屬於搜尋條件之一。
		bool isSearchByTag();

		//「日期」是否屬於搜尋條件之一。
		bool isSearchByDate();

		//「名稱」是否屬於搜尋條件之一。
		bool isSearchByName();

		// 設定要搜尋的「Tag」。
		void setTargetTag(std::string);

		// 設定要搜尋的「日期」。(不使用的部分塞 0)
		void setTargetDate(Date);

		// 設定要搜尋的「名稱」。
		void setTargetName(std::string);

		// 取得要搜尋的「Tag」。
		std::string getTargetTag();

		// 取得要搜尋的「日期」。
		Date getTargetDate();

		// 取得要搜尋的「名稱」。
		std::string getTargetName();

		// 以字串表達物件全資訊，通常用於 Debug 直接輸出。
		std::string toString();
};