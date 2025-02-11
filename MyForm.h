#pragma once

#include "Bookkeeper/Record.h"
#include "Bookkeeper/RecordSystem.h"
#include "Bookkeeper/tagCounter.h"
#include "Bookkeeper/FileManager.h"
#include <string>
#include <iostream>
#include <climits>
#include <set>

namespace Bookkeeper {

	using namespace System::Runtime::InteropServices;

	namespace Win32 {

		[DllImport("kernel32.dll", CallingConvention = CallingConvention::StdCall)]
			int AllocConsole();

		[DllImport("kernel32.dll", CallingConvention = CallingConvention::StdCall)]
			int FreeConsole();
	}

	using namespace Win32;


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			loadRecordData(Database);
			init();
			writeToListView(SearchPara(false, false, false));
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ inputRecord_Button;
	protected:

	protected:

	private:
		//*** 物件
		Form^ inputForm;
		ListView^ recordListTag = gcnew ListView(); //子視窗(紀錄)中的ListView

		TextBox^ textBox = gcnew TextBox();
		NumericUpDown^ numAmount = gcnew NumericUpDown();

		DateTimePicker^ dateTimePicker = gcnew DateTimePicker();
		Label^ dateLabel = gcnew Label();

		ComboBox^ comboBoxTag = gcnew ComboBox();
		ComboBox^ comboBoxType = gcnew ComboBox();
		Label^ tagLabel = gcnew Label();
		Label^ typeLabel = gcnew Label();

		RecordType type = RecordType::Expense; //判斷類型
		//***

	private: System::Windows::Forms::ListView^ listView_allInfo;


	private: System::Windows::Forms::ColumnHeader^ 類型;

	private: System::Windows::Forms::ColumnHeader^ 名稱;

	private: System::Windows::Forms::ColumnHeader^ 日期;

	private: System::Windows::Forms::ColumnHeader^ 金額;
	private: System::Windows::Forms::Button^ removeRecord_Button;
	private: System::Windows::Forms::ColumnHeader^ Tag;
	private: System::Windows::Forms::CheckBox^ year_checkBox;
	private: System::Windows::Forms::CheckBox^ month_checkBox;
	private: System::Windows::Forms::CheckBox^ day_checkBox;
	private: System::Windows::Forms::NumericUpDown^ year_numeric;
	private: System::Windows::Forms::NumericUpDown^ month_numeric;
	private: System::Windows::Forms::NumericUpDown^ day_numeric;

	private: System::Windows::Forms::CheckBox^ Tag_checkBox;
	private: System::Windows::Forms::CheckBox^ Name_checkBox;

	private: System::Windows::Forms::TextBox^ Name_textBox;
	private: System::Windows::Forms::ComboBox^ tag_comboBox;
	private: System::Windows::Forms::GroupBox^ SearchCondition;
	private: System::Windows::Forms::Button^ averageCompute_button;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->inputRecord_Button = (gcnew System::Windows::Forms::Button());
			this->listView_allInfo = (gcnew System::Windows::Forms::ListView());
			this->類型 = (gcnew System::Windows::Forms::ColumnHeader());
			this->名稱 = (gcnew System::Windows::Forms::ColumnHeader());
			this->日期 = (gcnew System::Windows::Forms::ColumnHeader());
			this->金額 = (gcnew System::Windows::Forms::ColumnHeader());
			this->Tag = (gcnew System::Windows::Forms::ColumnHeader());
			this->removeRecord_Button = (gcnew System::Windows::Forms::Button());
			this->year_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->month_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->day_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->year_numeric = (gcnew System::Windows::Forms::NumericUpDown());
			this->month_numeric = (gcnew System::Windows::Forms::NumericUpDown());
			this->day_numeric = (gcnew System::Windows::Forms::NumericUpDown());
			this->Tag_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->Name_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->Name_textBox = (gcnew System::Windows::Forms::TextBox());
			this->tag_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->SearchCondition = (gcnew System::Windows::Forms::GroupBox());
			this->averageCompute_button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->year_numeric))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->month_numeric))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->day_numeric))->BeginInit();
			this->SearchCondition->SuspendLayout();
			this->SuspendLayout();
			// 
			// inputRecord_Button
			// 
			this->inputRecord_Button->Location = System::Drawing::Point(59, 115);
			this->inputRecord_Button->Name = L"inputRecord_Button";
			this->inputRecord_Button->Size = System::Drawing::Size(102, 39);
			this->inputRecord_Button->TabIndex = 0;
			this->inputRecord_Button->Text = L"新增紀錄";
			this->inputRecord_Button->UseVisualStyleBackColor = true;
			this->inputRecord_Button->Click += gcnew System::EventHandler(this, &MyForm::inputRecord_Click);
			// 
			// listView_allInfo
			// 
			this->listView_allInfo->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->listView_allInfo->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->類型, this->名稱,
					this->日期, this->金額, this->Tag
			});
			this->listView_allInfo->HideSelection = false;
			this->listView_allInfo->Location = System::Drawing::Point(347, 115);
			this->listView_allInfo->Name = L"listView_allInfo";
			this->listView_allInfo->Size = System::Drawing::Size(600, 419);
			this->listView_allInfo->TabIndex = 1;
			this->listView_allInfo->UseCompatibleStateImageBehavior = false;
			this->listView_allInfo->View = System::Windows::Forms::View::Details;
			// 
			// 類型
			// 
			this->類型->Text = L"類型";
			this->類型->Width = 120;
			// 
			// 名稱
			// 
			this->名稱->Text = L"名稱";
			this->名稱->Width = 120;
			// 
			// 日期
			// 
			this->日期->Text = L"日期";
			this->日期->Width = 120;
			// 
			// 金額
			// 
			this->金額->Text = L"金額";
			this->金額->Width = 120;
			// 
			// Tag
			// 
			this->Tag->Text = L"Tag";
			this->Tag->Width = 120;
			// 
			// removeRecord_Button
			// 
			this->removeRecord_Button->Location = System::Drawing::Point(226, 115);
			this->removeRecord_Button->Name = L"removeRecord_Button";
			this->removeRecord_Button->Size = System::Drawing::Size(102, 39);
			this->removeRecord_Button->TabIndex = 2;
			this->removeRecord_Button->Text = L"刪除紀錄";
			this->removeRecord_Button->UseVisualStyleBackColor = true;
			this->removeRecord_Button->Click += gcnew System::EventHandler(this, &MyForm::removeRecord_Button_Click);
			// 
			// year_checkBox
			// 
			this->year_checkBox->AutoSize = true;
			this->year_checkBox->Location = System::Drawing::Point(6, 21);
			this->year_checkBox->Name = L"year_checkBox";
			this->year_checkBox->Size = System::Drawing::Size(36, 16);
			this->year_checkBox->TabIndex = 3;
			this->year_checkBox->Text = L"年";
			this->year_checkBox->UseVisualStyleBackColor = true;
			this->year_checkBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::year_checkBox_CheckedChanged);
			// 
			// month_checkBox
			// 
			this->month_checkBox->AutoSize = true;
			this->month_checkBox->Enabled = false;
			this->month_checkBox->Location = System::Drawing::Point(6, 76);
			this->month_checkBox->Name = L"month_checkBox";
			this->month_checkBox->Size = System::Drawing::Size(36, 16);
			this->month_checkBox->TabIndex = 4;
			this->month_checkBox->Text = L"月";
			this->month_checkBox->UseVisualStyleBackColor = true;
			this->month_checkBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::month_checkBox_CheckedChanged);
			// 
			// day_checkBox
			// 
			this->day_checkBox->AutoSize = true;
			this->day_checkBox->Enabled = false;
			this->day_checkBox->Location = System::Drawing::Point(6, 134);
			this->day_checkBox->Name = L"day_checkBox";
			this->day_checkBox->Size = System::Drawing::Size(36, 16);
			this->day_checkBox->TabIndex = 5;
			this->day_checkBox->Text = L"日";
			this->day_checkBox->UseVisualStyleBackColor = true;
			this->day_checkBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::day_checkBox_CheckedChanged);
			// 
			// year_numeric
			// 
			this->year_numeric->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->year_numeric->Location = System::Drawing::Point(6, 43);
			this->year_numeric->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->year_numeric->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1900, 0, 0, 0 });
			this->year_numeric->Name = L"year_numeric";
			this->year_numeric->Size = System::Drawing::Size(81, 27);
			this->year_numeric->TabIndex = 6;
			this->year_numeric->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1900, 0, 0, 0 });
			this->year_numeric->Visible = false;
			this->year_numeric->ValueChanged += gcnew System::EventHandler(this, &MyForm::year_numeric_ValueChanged);
			// 
			// month_numeric
			// 
			this->month_numeric->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->month_numeric->Location = System::Drawing::Point(6, 98);
			this->month_numeric->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 12, 0, 0, 0 });
			this->month_numeric->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->month_numeric->Name = L"month_numeric";
			this->month_numeric->Size = System::Drawing::Size(81, 27);
			this->month_numeric->TabIndex = 7;
			this->month_numeric->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->month_numeric->Visible = false;
			this->month_numeric->ValueChanged += gcnew System::EventHandler(this, &MyForm::month_numeric_ValueChanged);
			// 
			// day_numeric
			// 
			this->day_numeric->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->day_numeric->Location = System::Drawing::Point(6, 156);
			this->day_numeric->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->day_numeric->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->day_numeric->Name = L"day_numeric";
			this->day_numeric->Size = System::Drawing::Size(81, 27);
			this->day_numeric->TabIndex = 8;
			this->day_numeric->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->day_numeric->Visible = false;
			this->day_numeric->ValueChanged += gcnew System::EventHandler(this, &MyForm::day_numeric_ValueChanged);
			// 
			// Tag_checkBox
			// 
			this->Tag_checkBox->AutoSize = true;
			this->Tag_checkBox->Location = System::Drawing::Point(140, 21);
			this->Tag_checkBox->Name = L"Tag_checkBox";
			this->Tag_checkBox->Size = System::Drawing::Size(42, 16);
			this->Tag_checkBox->TabIndex = 10;
			this->Tag_checkBox->Text = L"Tag";
			this->Tag_checkBox->UseVisualStyleBackColor = true;
			this->Tag_checkBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Tag_checkBox_CheckedChanged);
			// 
			// Name_checkBox
			// 
			this->Name_checkBox->AutoSize = true;
			this->Name_checkBox->Location = System::Drawing::Point(140, 76);
			this->Name_checkBox->Name = L"Name_checkBox";
			this->Name_checkBox->Size = System::Drawing::Size(48, 16);
			this->Name_checkBox->TabIndex = 12;
			this->Name_checkBox->Text = L"名稱";
			this->Name_checkBox->UseVisualStyleBackColor = true;
			this->Name_checkBox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Name_checkBox_CheckedChanged);
			// 
			// Name_textBox
			// 
			this->Name_textBox->Enabled = false;
			this->Name_textBox->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Name_textBox->Location = System::Drawing::Point(140, 98);
			this->Name_textBox->Name = L"Name_textBox";
			this->Name_textBox->Size = System::Drawing::Size(102, 27);
			this->Name_textBox->TabIndex = 14;
			this->Name_textBox->TextChanged += gcnew System::EventHandler(this, &MyForm::Name_textBox_TextChanged);
			// 
			// tag_comboBox
			// 
			this->tag_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->tag_comboBox->Enabled = false;
			this->tag_comboBox->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->tag_comboBox->FormattingEnabled = true;
			this->tag_comboBox->Location = System::Drawing::Point(140, 43);
			this->tag_comboBox->Name = L"tag_comboBox";
			this->tag_comboBox->Size = System::Drawing::Size(121, 24);
			this->tag_comboBox->TabIndex = 15;
			this->tag_comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::tag_comboBox_SelectedIndexChanged);
			// 
			// SearchCondition
			// 
			this->SearchCondition->Controls->Add(this->year_checkBox);
			this->SearchCondition->Controls->Add(this->tag_comboBox);
			this->SearchCondition->Controls->Add(this->month_checkBox);
			this->SearchCondition->Controls->Add(this->Name_textBox);
			this->SearchCondition->Controls->Add(this->day_checkBox);
			this->SearchCondition->Controls->Add(this->Name_checkBox);
			this->SearchCondition->Controls->Add(this->year_numeric);
			this->SearchCondition->Controls->Add(this->Tag_checkBox);
			this->SearchCondition->Controls->Add(this->month_numeric);
			this->SearchCondition->Controls->Add(this->day_numeric);
			this->SearchCondition->Location = System::Drawing::Point(59, 343);
			this->SearchCondition->Name = L"SearchCondition";
			this->SearchCondition->Size = System::Drawing::Size(269, 191);
			this->SearchCondition->TabIndex = 16;
			this->SearchCondition->TabStop = false;
			this->SearchCondition->Text = L"篩選";
			// 
			// averageCompute_button
			// 
			this->averageCompute_button->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->averageCompute_button->Location = System::Drawing::Point(541, 25);
			this->averageCompute_button->Name = L"averageCompute_button";
			this->averageCompute_button->Size = System::Drawing::Size(168, 71);
			this->averageCompute_button->TabIndex = 17;
			this->averageCompute_button->UseVisualStyleBackColor = true;
			this->averageCompute_button->Click += gcnew System::EventHandler(this, &MyForm::averageCompute_button_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(980, 591);
			this->Controls->Add(this->averageCompute_button);
			this->Controls->Add(this->SearchCondition);
			this->Controls->Add(this->removeRecord_Button);
			this->Controls->Add(this->listView_allInfo);
			this->Controls->Add(this->inputRecord_Button);
			this->Name = L"MyForm";
			this->Text = L"Bookkeeper";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->year_numeric))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->month_numeric))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->day_numeric))->EndInit();
			this->SearchCondition->ResumeLayout(false);
			this->SearchCondition->PerformLayout();
			this->ResumeLayout(false);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		}
#pragma endregion
	private:
		System::Void inputRecord_Click(System::Object^ sender, System::EventArgs^ e)
		{
			init_searchPara();
			// 創建輸入視窗
			inputForm = gcnew Form();
			inputForm->Text = "紀錄";
			inputForm->Size = System::Drawing::Size(800, 550);
			inputForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;

			// *** TextBox 輸入名稱
			Label^ textlabel = gcnew Label();

			textBox->Size = System::Drawing::Size(80, 20);
			textBox->Font = gcnew System::Drawing::Font("Arial", 13, FontStyle::Regular);
			textlabel->Location = System::Drawing::Point(40, 40);
			textBox->Location = System::Drawing::Point(40, 60);

			textlabel->Text = "名稱";
			textBox->Text = "無";

			inputForm->Controls->Add(textBox);
			inputForm->Controls->Add(textlabel);
			// ***

			// *** NumericUpDown 輸入金額
			Label^ numlabel = gcnew Label();

			numAmount->Minimum = 0;
			numAmount->Maximum = ULLONG_MAX; //unsign long long最大值
			numlabel->Location = System::Drawing::Point(161, 40);
			numAmount->Location = System::Drawing::Point(161, 60);
			numAmount->Font = gcnew System::Drawing::Font("Arial", 13, FontStyle::Regular);

			numlabel->Text = "金額(輸入數字)";
			numAmount->Value = 0;

			inputForm->Controls->Add(numAmount);
			inputForm->Controls->Add(numlabel);
			// ***

			// *** DateTimePicker物件
			dateLabel->Text = "日期";

			dateTimePicker->MinDate = DateTime::DateTime(1900, 1, 1);
			dateTimePicker->Format = DateTimePickerFormat::Long; //日期格式設定
			dateTimePicker->Location = System::Drawing::Point(40, 120);
			dateTimePicker->Size = System::Drawing::Size(200, 100);
			dateLabel->Location = System::Drawing::Point(40, 100);
			dateTimePicker->Font = gcnew System::Drawing::Font("Arial", 13, FontStyle::Regular);
			dateTimePicker->Value = DateTime::Now;

			inputForm->Controls->Add(dateTimePicker);
			inputForm->Controls->Add(dateLabel);
			// ***

			// *** ComboBox物件
			tagLabel->Text = "Tag";
			typeLabel->Text = "Type";

			comboBoxTag->Location = System::Drawing::Point(40, 240);
			comboBoxType->Location = System::Drawing::Point(40, 180);
			tagLabel->Location = System::Drawing::Point(40, 220);
			typeLabel->Location = System::Drawing::Point(40, 160);
			comboBoxTag->Size = System::Drawing::Size(200, comboBoxTag->Height);
			comboBoxType->Size = System::Drawing::Size(200, comboBoxType->Height);
			comboBoxTag->Font = gcnew System::Drawing::Font("Arial", 13, FontStyle::Regular);
			comboBoxType->Font = gcnew System::Drawing::Font("Arial", 13, FontStyle::Regular);

			ClearList(comboBoxTag->Items);
			comboBoxTag->Text = "飲食";
			insertExistTags(comboBoxTag);

			ClearList(comboBoxType->Items);
			comboBoxType->Items->Clear();
			comboBoxType->Items->Add("花費");
			comboBoxType->Items->Add("收入");
			comboBoxType->Text = "花費";
			comboBoxType->DropDownStyle = ComboBoxStyle::DropDownList;

			inputForm->Controls->Add(comboBoxTag);
			inputForm->Controls->Add(comboBoxType);
			inputForm->Controls->Add(tagLabel);
			inputForm->Controls->Add(typeLabel);
			// ***

			// 新增、刪除按鈕
			Button^ insertButton = gcnew Button();
			Button^ confirmButton = gcnew Button();
			Button^ deleteButton = gcnew Button();

			insertButton->Text = "新增";
			confirmButton->Text = "確認";
			deleteButton->Text = "刪除";

			insertButton->Location = System::Drawing::Point(40, 290);
			confirmButton->Location = System::Drawing::Point(40, 350);
			deleteButton->Location = System::Drawing::Point(165, 290);

			inputForm->Controls->Add(insertButton);
			inputForm->Controls->Add(confirmButton);
			inputForm->Controls->Add(deleteButton);

			// listView設定
			recordListTag->Items->Clear();
			recordListTag->Columns->Clear();
			recordListTag->Size = System::Drawing::Size(150, 400);
			recordListTag->Location = System::Drawing::Point(300, 40);

			recordListTag->View = View::Details;
			recordListTag->Columns->Add("Tag", 150);

			inputForm->Controls->Add(recordListTag);

			// 按鈕點擊
			insertButton->Click += gcnew System::EventHandler(this, &MyForm::InsertButtonClickHandler);
			confirmButton->Click += gcnew System::EventHandler(this, &MyForm::ConfirmButtonClickHandler);
			deleteButton->Click += gcnew System::EventHandler(this, &MyForm::DeleteButtonClickHandler);

			inputForm->ShowDialog();
		}

		void insertExistTags(ComboBox^ comboBox)
		{
			std::vector<std::string> Tags = getAllTag();
			comboBox->Items->Add("飲食");
			comboBox->Items->Add("購物");
			comboBox->Items->Add("娛樂");
			comboBox->Items->Add("帳單");

			for (int i = 0; i < Tags.size(); ++i)
			{
				String^ temp = toSystemStringFromUTF8(Tags[i]);

				if (!comboBox->Items->Contains(temp) && getTagCount(toStdString(temp)) > 0)
					comboBox->Items->Add(temp);
			}
		}

		void init_searchPara()
		{
			this->year_checkBox->Checked = false;
			this->year_numeric->Visible = false;
			this->year_numeric->Value = this->year_numeric->Minimum;

			this->month_checkBox->Enabled = false;
			this->month_checkBox->Checked = false;
			this->month_numeric->Visible = false;
			this->month_numeric->Value = this->month_numeric->Minimum;

			this->day_checkBox->Checked = false;
			this->day_checkBox->Enabled = false;
			this->day_numeric->Visible = false;
			this->day_numeric->Value = this->day_numeric->Minimum;

			this->Tag_checkBox->Checked = false;
			this->tag_comboBox->Enabled = false;
			this->tag_comboBox->Text = "";

			this->Name_checkBox->Checked = false;
			this->Name_textBox->Enabled = false;
			this->Name_textBox->Clear();
		}

		void InsertButtonClickHandler(System::Object^ sender, System::EventArgs^ e)
		{
			bool flag = true;
			String^ comboTag = comboBoxTag->Text->Trim();

			for each (ListViewItem ^ item in recordListTag->Items)
			{
				if (item->Text == comboTag)
					flag = false;
			}

			if (flag)
			{
				// 創建 ListViewItem
				ListViewItem^ item = gcnew ListViewItem(gcnew array<String^>{
					comboTag // Tag
				});

				addTag(toStdString(comboTag));
				recordListTag->Items->Add(item);
			}
			else
			{
				MessageBox::Show("此Tag已經存在右側列表中，請重新選擇", "警告", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}

		void ConfirmButtonClickHandler(System::Object^ sender, System::EventArgs^ e)
		{
			if (comboBoxType->Text == "收入") type = RecordType::Income;
			else type = RecordType::Expense;

			//存到dataBase和更新listView
			Record record(type, toStdString(textBox->Text), Decimal::ToUInt64(numAmount->Value));
			Date date(dateTimePicker->Value.Year, dateTimePicker->Value.Month, dateTimePicker->Value.Day);

			// ***拿出所有Tag
			for each (ListViewItem ^ item in recordListTag->Items)
			{
				std::string temp = toStdString(item->Text);
				record.insertTag(temp);
			}
			// ***

			record.setDate(date);

			Database.insertRecord(record);
			saveRecordData(Database);

			writeToListView(SearchPara(false, false, false));
			computeSpendAndEarn();

			inputForm->Close();
		}

		void writeToListView(SearchPara& para)
		{
			listView_allInfo->Items->Clear();
			std::vector<Record> allRecords = Database.getRecords(para);

			for (const Record& record : allRecords)
			{

				String^ type = "";
				if (record.getType() == RecordType::Income) type = "收入";
				else type = "花費";

				std::vector<std::string> tags = record.getTags();
				std::string temp = "";

				// *** 拿tag出來
				if (!tags.empty())
				{
					for (const std::string& str : tags)
						temp += (str + ", ");

					temp.pop_back();
					temp.pop_back();
				}
				// ***

				std::string date = record.getDate().toString();
				date = date.substr(1, date.size() - 2);

				// 創建 ListViewItem
				ListViewItem^ item = gcnew ListViewItem(gcnew array<String^>{
					type,    // 類型
						toSystemStringFromUTF8(record.getName()),  // 名稱
						toSystemStringFromUTF8(date), // 日期
						record.getAmount().ToString(),  // 金額
						toSystemStringFromUTF8(temp) // Tag
				});

				// 加入ListView中
				item->Tag = record.getId();
				this->listView_allInfo->Items->Add(item);
			}
		}

		void DeleteButtonClickHandler(System::Object^ sender, System::EventArgs^ e)
		{
			if (recordListTag->SelectedItems->Count > 0)
			{
				ListViewItem^ selectedItem = recordListTag->SelectedItems[0];

				// 從 ListView移除
				recordListTag->Items->Remove(selectedItem);
				removeTag(toStdString(selectedItem->Text));
			}
			else
			{
				MessageBox::Show("請選擇一個要刪除項目", "警告", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}

		void updateListView()
		{
			bool dateFlag = year_checkBox->Checked;
			bool tagFlag = Tag_checkBox->Checked;
			bool nameFlag = Name_checkBox->Checked;

			U_Int32 year = year_checkBox->Checked ? Convert::ToUInt32(this->year_numeric->Value) : 0;
			U_Octet month = month_checkBox->Checked ? Convert::ToByte(this->month_numeric->Value) : 0;
			U_Octet day = day_checkBox->Checked ? Convert::ToByte(this->day_numeric->Value) : 0;

			SearchPara para = SearchPara(tagFlag, dateFlag, nameFlag);
			para.setTargetTag(toStdString(this->tag_comboBox->Text));

			para.setTargetDate(Date(year, month, day));
			para.setTargetName(toStdString(this->Name_textBox->Text));

			writeToListView(para);
		}

	private: System::Void removeRecord_Button_Click(System::Object^ sender, System::EventArgs^ e)
	{

		if (listView_allInfo->SelectedItems->Count > 0)
		{
			ListViewItem^ selectedRecord = listView_allInfo->SelectedItems[0];

			U_Int32 id = Convert::ToUInt32(selectedRecord->Tag);

			Record temp = Database.getRecord(id);

			// 減掉移除的tag的個數
			std::vector<std::string> tags = temp.getTags();
			for (std::string& tag : tags)
				removeTag(tag);

			Database.removeRecord(id);
			saveRecordData(Database);

			listView_allInfo->Items->Remove(selectedRecord);
			computeSpendAndEarn();
		}
		else
		{
			MessageBox::Show("請選擇一個要刪除的紀錄", "警告", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

	private: System::Void year_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		updateListView();
		computeSpendAndEarn();
		if (this->year_checkBox->Checked == true) {
			this->year_numeric->Visible = true;
			this->month_checkBox->Enabled = true;
		}
		else {
			this->year_numeric->Value = this->year_numeric->Minimum;
			this->year_numeric->Visible = false;
			this->month_checkBox->Checked = false;
			this->month_checkBox->Enabled = false;
			this->month_numeric->Visible = false;
			this->day_checkBox->Checked = false;
			this->day_checkBox->Enabled = false;
			this->day_numeric->Visible = false;
		}
	}

	private: System::Void month_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		updateListView();
		computeSpendAndEarn();
		if (this->month_checkBox->Checked == true && this->year_checkBox->Checked == true) {
			this->month_numeric->Visible = true;
			this->day_checkBox->Enabled = true;
		}
		else {
			this->month_numeric->Value = this->month_numeric->Minimum;
			this->month_numeric->Visible = false;
			this->day_checkBox->Checked = false;
			this->day_checkBox->Enabled = false;
			this->day_numeric->Visible = false;
		}
	}

	private: System::Void day_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		updateListView();
		computeSpendAndEarn();
		if (this->day_checkBox->Checked == true && this->month_checkBox->Checked == true && this->year_checkBox->Checked == true) {
			this->day_numeric->Visible = true;
		}
		else {
			this->day_numeric->Value = this->day_numeric->Minimum;
			this->day_numeric->Visible = false;
		}
	}

	private: System::Void Tag_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		updateListView();
		computeSpendAndEarn();
		if (this->Tag_checkBox->Checked == true)
		{
			this->tag_comboBox->Enabled = true;
			insertExistTags(this->tag_comboBox);
		}
		else
		{
			ClearList(tag_comboBox->Items);
			this->tag_comboBox->Enabled = false;
		}
	}

	private: System::Void Name_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		updateListView();
		computeSpendAndEarn();
		if (this->Name_checkBox->Checked == true)
			this->Name_textBox->Enabled = true;
		else
		{
			this->Name_textBox->Clear();
			this->Name_textBox->Enabled = false;
		}
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
		computeSpendAndEarn();

	}

	private: System::Void year_numeric_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (year_numeric->Value < 1900)
			year_numeric->Value = 1900;
		else if (year_numeric->Value > 9999)
			year_numeric->Value = 9999;

		updateListView();
		computeSpendAndEarn();
	}
	private: System::Void month_numeric_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		updateListView();
		computeSpendAndEarn();
	}
	private: System::Void day_numeric_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		updateListView();
		computeSpendAndEarn();
	}
	private: System::Void tag_comboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		updateListView();
		computeSpendAndEarn();
	}
	private: System::Void Name_textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		updateListView();
		computeSpendAndEarn();
	}

	void computeAverage(Label^ year_average, Label^ month_average, Label^ day_average, RecordType type)
	{
		std::set<std::vector<U_Int64>> yearAmount;
		std::set<std::vector<U_Int64>> monthAmount;
		std::set<std::vector<U_Int64>> dayAmount;

		U_Int64 sum = 0;
		for each (ListViewItem ^ item in listView_allInfo->Items)
		{
			Record record = Database.getRecord(Convert::ToUInt32(item->Tag));
			std::vector<U_Int64> temp;

			if (record.getType() == type)
			{
				sum += record.getAmount();
				std::cout << sum << '\n';
				temp.push_back(record.getDate().getYear());
				yearAmount.insert(temp);
				temp.push_back(record.getDate().getMonth());
				monthAmount.insert(temp);
				temp.push_back(record.getDate().getDay());
				dayAmount.insert(temp);
			}
		}

		std::cout << dayAmount.size() << ' ' << monthAmount.size() << ' ' << yearAmount.size() << '\n';
		if (dayAmount.size() != 0)
		{
			if (day_checkBox->Checked)
			{
				year_average->Text = "";
				month_average->Text = "";
				day_average->Text = Convert::ToString(sum);
			}
			else if (month_checkBox->Checked)
			{
				year_average->Text = "";
				month_average->Text = "";
				day_average->Text = Convert::ToString(sum / dayAmount.size());
			}
			else if (year_checkBox->Checked)
			{
				year_average->Text = "";
				month_average->Text = Convert::ToString(sum / monthAmount.size());
				day_average->Text = Convert::ToString(sum / dayAmount.size());
			}
			else
			{
				year_average->Text = Convert::ToString(sum / yearAmount.size());
				month_average->Text = Convert::ToString(sum / monthAmount.size());
				day_average->Text = Convert::ToString(sum / dayAmount.size());
			}
		}
		else
		{
			year_average->Text = "";
			month_average->Text = "";
			day_average->Text = "";
		}

		return;
	}

	void computeSpendAndEarn()
	{
		U_Int64 spend = 0;
		U_Int64 earn = 0;
		for each (ListViewItem ^ item in listView_allInfo->Items)
		{
			Record record = Database.getRecord(Convert::ToUInt32(item->Tag));
			RecordType type = record.getType();

			if (type == RecordType::Income)
				earn += record.getAmount();
			else
				spend += record.getAmount();
		}

		this->averageCompute_button->Text = L"總花費 : " + Convert::ToString(spend) + "元\n\n";
		this->averageCompute_button->Text += L"總收入 : " + Convert::ToString(earn) + "元";
	}

	private: System::Void averageCompute_button_Click(System::Object^ sender, System::EventArgs^ e) {
		Form^ average_computeForm = gcnew Form();
		average_computeForm->Text = "花費/收入平均";
		average_computeForm->Size = System::Drawing::Size(450, 200);
		average_computeForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;

		computeSpendAndEarn();

		Label^ expense_Label = gcnew Label();
		Label^ income_Label = gcnew Label();

		Label^ year_Label = gcnew Label();
		Label^ month_Label = gcnew Label();
		Label^ day_Label = gcnew Label();

		Label^ year_average_spend = gcnew Label();
		Label^ month_average_spend = gcnew Label();
		Label^ day_average_spend = gcnew Label();

		Label^ year_average_earn = gcnew Label();
		Label^ month_average_earn = gcnew Label();
		Label^ day_average_earn = gcnew Label();

#pragma region Label
		year_Label->Text = "年平均";
		month_Label->Text = "月平均";
		day_Label->Text = "日平均";

		expense_Label->Text = "花費";
		income_Label->Text = "收入";

		year_Label->Size = System::Drawing::Size(100, year_Label->Height);
		month_Label->Size = System::Drawing::Size(100, month_Label->Height);
		day_Label->Size = System::Drawing::Size(100, day_Label->Height);

		expense_Label->Size = System::Drawing::Size(100, expense_Label->Height);
		income_Label->Size = System::Drawing::Size(100, income_Label->Height);

		year_Label->Location = System::Drawing::Point(100, 20);
		month_Label->Location = System::Drawing::Point(200, 20);
		day_Label->Location = System::Drawing::Point(300, 20);

		expense_Label->Location = System::Drawing::Point(50, 50);
		income_Label->Location = System::Drawing::Point(50, 80);

		year_Label->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);
		month_Label->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);
		day_Label->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);

		expense_Label->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);
		income_Label->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);
#pragma endregion

		computeAverage(year_average_spend, month_average_spend, day_average_spend, RecordType::Expense);
		computeAverage(year_average_earn, month_average_earn, day_average_earn, RecordType::Income);

#pragma region average
		year_average_spend->Size = System::Drawing::Size(100, year_average_spend->Height);
		month_average_spend->Size = System::Drawing::Size(100, month_average_spend->Height);
		day_average_spend->Size = System::Drawing::Size(100, day_average_spend->Height);

		year_average_spend->Location = System::Drawing::Point(100, 50);
		month_average_spend->Location = System::Drawing::Point(200, 50);
		day_average_spend->Location = System::Drawing::Point(300, 50);

		year_average_spend->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);
		month_average_spend->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);
		day_average_spend->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);

		year_average_earn->Size = System::Drawing::Size(100, year_average_earn->Height);
		month_average_earn->Size = System::Drawing::Size(100, month_average_earn->Height);
		day_average_earn->Size = System::Drawing::Size(100, day_average_earn->Height);

		year_average_earn->Location = System::Drawing::Point(100, 80);
		month_average_earn->Location = System::Drawing::Point(200, 80);
		day_average_earn->Location = System::Drawing::Point(300, 80);

		year_average_earn->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);
		month_average_earn->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);
		day_average_earn->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Regular);
#pragma endregion

		average_computeForm->Controls->Add(year_Label);
		average_computeForm->Controls->Add(month_Label);
		average_computeForm->Controls->Add(day_Label);

		average_computeForm->Controls->Add(year_average_spend);
		average_computeForm->Controls->Add(month_average_spend);
		average_computeForm->Controls->Add(day_average_spend);

		average_computeForm->Controls->Add(year_average_earn);
		average_computeForm->Controls->Add(month_average_earn);
		average_computeForm->Controls->Add(day_average_earn);

		average_computeForm->Controls->Add(expense_Label);
		average_computeForm->Controls->Add(income_Label);

		average_computeForm->ShowDialog();
	}
	};
}
