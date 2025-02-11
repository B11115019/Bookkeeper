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
	// �ϥ� System.Text.Encoding.UTF8 �s�X
	if (oriString == "")
		oriString = " ";
	using namespace System::Text;
	array<unsigned char>^ utf8Bytes = Encoding::UTF8->GetBytes(oriString);
	pin_ptr<unsigned char> pinnedBytes = &utf8Bytes[0];
	return std::string(reinterpret_cast<char*>(pinnedBytes), utf8Bytes->Length);
}

// �N UTF-8 �s�X�� std::string �ഫ�� System::String^
inline System::String^ toSystemStringFromUTF8(const std::string& utf8String)
{
	// �ϥ� System.Text.Encoding.UTF8 �ӱN UTF-8 �r�Ŧ��ഫ�� .NET �r�Ŧ�
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