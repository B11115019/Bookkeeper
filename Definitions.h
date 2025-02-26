#pragma once
#pragma warning(disable:4716)
#pragma warning(disable:4996)

#include <string>
#include <vector>

using U_Int64 = unsigned long long;
using U_Int32 = unsigned int;
using Octet = char;
using U_Octet = unsigned char;

enum class RecordType {
	Income,
	Expense
};

inline std::string toStdString(System::String^ oriString) {
	// 使用 System.Text.Encoding.UTF8 編碼
	if (oriString == "")
		oriString = " ";
	using namespace System::Text;
	array<unsigned char>^ utf8Bytes = Encoding::UTF8->GetBytes(oriString);
	pin_ptr<unsigned char> pinnedBytes = &utf8Bytes[0];
	return std::string(reinterpret_cast<char*>(pinnedBytes), utf8Bytes->Length);
}

// 將 UTF-8 編碼的 std::string 轉換為 System::String^
inline System::String^ toSystemStringFromUTF8(const std::string& utf8String)
{
	// 使用 System.Text.Encoding.UTF8 來將 UTF-8 字符串轉換為 .NET 字符串
	array<unsigned char>^ utf8Bytes = gcnew array<unsigned char>(utf8String.size());
	for (size_t i = 0; i < utf8String.size(); ++i)
	{
		utf8Bytes[i] = static_cast<unsigned char>(utf8String[i]);
	}

	return System::Text::Encoding::UTF8->GetString(utf8Bytes);
}

template<typename T> inline void ClearList(System::Collections::Generic::List<T>^ Lst) {
	for (int i = 0; i < Lst->Count; ++i) {
		delete Lst[i];
	}

	Lst->Clear();
}

inline void ClearList(System::Windows::Forms::ComboBox::ObjectCollection^ Lst) {
	for (int i = 0; i < Lst->Count; ++i) {
		delete Lst[i];
	}

	Lst->Clear();
}