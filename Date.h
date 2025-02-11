#pragma once
#include "Definitions.h"

struct Date {
	private:
		U_Int32 Year;
		U_Octet Month, Day;

	public:
		Date(U_Int32, U_Octet, U_Octet);

		// 取得年份。
		U_Int32 getYear();

		// 取得月份。
		U_Int32 getMonth();

		// 取得日。
		U_Int32 getDay();

		// 以字串表達物件全資訊，通常用於 Debug 直接輸出。
		std::string toString();

		bool operator<(Date);
		bool operator>(Date);
		bool operator==(Date);
		bool operator<=(Date);
		bool operator>=(Date);
};