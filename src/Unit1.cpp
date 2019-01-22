//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace std;

TForm1 *Form1;

// isEnabled 表示目前是否正在啟用 Disk Not Sleep。
bool isEnabled;
// isFirstTimeMinimized 表示這是否是初次在啟用時最小化。
bool isFirstTimeMinimized = true;
// availableDisks 存放著目前可用的所有磁碟名稱（如：`C:\`、`D:\`）。
vector<String> availableDisks;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	// GetLogicalDrives 能夠以 Bitmask 的方式取得所有可用的邏輯磁碟（如：A 是 1、B 為 2，兩者皆可用則為 3）。
	DWORD drives = GetLogicalDrives();

	// 遞迴整個英文字母的邏輯磁碟。
	for (int i=0; i<26; i++)
	{
		// 如果這個磁碟不可用則進行到下一個。
		if(! ( drives & ( 1 << i ) ) )
		{
			continue;
		}

		// driveName 是個能夠保存將此可用邏輯磁碟的名稱的 ANSI 正整數陣列。
		int driveName[] = {TEXT('A') + i, TEXT(':'), TEXT('\\'), TEXT('\0')};

		// str 是標準的字串，用以將 ANSI 字元轉換為標準的字串來取得邏輯磁碟名稱。
		std::string str;
		for(int i =0;i<sizeof(driveName);++i)
		{
			str.push_back(driveName[i]);
		}

		// 將組合後的可用邏輯磁碟名稱推入 availableDisks 的可用磁碟字串陣列。
		availableDisks.push_back(str.c_str());
	}

	// 遞迴整個可用磁碟名稱陣列，並將所有可用的磁碟展列到下拉式清單中。
	for (int i = 0; i < availableDisks.size(); i++)
	{
		this->ComboBox1->Items->Add(availableDisks[i]);
	}

	// 將下拉式清單的項目索引設為第一個項目。
	this->ComboBox1->ItemIndex = 0;
	this->ComboBox2->ItemIndex = 0;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    // 在結束程式時，移除所有不必要的檔案。
	this->Destroy();
	// 完全結束程式。
    Application->Terminate();
}

//---------------------------------------------------------------------------
int __fastcall TForm1::StringToInterval(String string){
	if (string == "5 秒") {
		return 5 * 1000;
	} else if (string == "10 秒") {
		return 10 * 1000;
	} else if (string == "30 秒") {
		return 30 * 1000;
	} else if (string == "1 分鐘") {
		return 60 * 1000;
	} else if (string == "3 分鐘") {
		return 60 * 3 * 1000;
	} else if (string == "5 分鐘") {
		return 60 * 5 * 1000;
	} else if (string == "30 分鐘") {
		return 60 * 30 * 1000;
	} else if (string == "1 小時") {
		return 60 * 60 * 1000;
	} else if (string == "3 小時") {
		return 60 * 60 * 3 * 1000;
	} else if (string == "5 小時") {
		return 60 * 60 * 5 * 1000;
	}
	return 5 * 1000;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	// 由於切換按鈕被按下了，所以將啟用狀態轉換到另一個狀態。
	isEnabled = !isEnabled;

	// 如果狀態啟用。
	if (isEnabled) {
		this->Button1->Caption = "停用";
		// 首次先直接檢查硬碟能否正常寫入，不行的話就提示一下，但正常執行，
		// 避免有可能是因為硬碟暫時無法存取而發生錯誤。
		if (!this->WriteBuffer()) {
			Application->MessageBoxW(L"無法將防怠速暫存檔案寫入指定的磁碟中，這有可能是應用程式權限不足（需透過管理員權限開啟此應用程式），亦有可能是裝置暫時離線。\n\n接下來的程式將會照常執行，但無法確保暫存檔案是否能正確寫入磁碟中。", L"無法寫入磁碟", 48);
		}

	// 如果狀態停用。
	} else {
		this->Button1->Caption = "啟用";
		// 在停用時，移除所有不必要的檔案。
		this->Destroy();
	}

	// 將下拉式選單全部改為啟用狀態的反面狀態，
	// 所以如果是「啟用」，下拉式選單就會全部停用，反之亦然。
	this->ComboBox1->Enabled = !isEnabled;
	this->ComboBox2->Enabled = !isEnabled;

	// 將計時器設為目前下拉式選單所選的時間，
	// 並將所選時間字串轉換成相對應的時間。
	this->Timer1->Interval = this->StringToInterval(this->ComboBox2->Items->operator [](this->ComboBox2->ItemIndex));
	this->Timer1->Enabled = isEnabled;

	// 重設進度條的位置，並且將最大值設為計時器的時間，
	// 這樣才能透過另一個計時器遞加來呈現正確的百分比。
	this->ProgressBar1->Position = 0;
	this->ProgressBar1->Max = this->Timer1->Interval;

	// 啟用第二個計時器來遞加進度條。
	this->Timer2->Enabled = isEnabled;
}

//---------------------------------------------------------------------------
bool __fastcall TForm1::WriteBuffer() {
	// fileStream 是一個檔案串流。
	fstream fileStream;
	// 在已經選好的路徑開啟一個檔案。
	fileStream.open(this->GetPath().c_str(), ios::out);
	// 如果無法開啟則回傳 `false`。
	if(!fileStream) {
		fileStream.close();
		return false;
	}
	// 將目前的 Unix 時間戳寫入檔案內，不寫入相同內容避免檔案被快取。
	fileStream<<std::time(0)<<endl;
	// 關閉檔案串流。
	fileStream.close();
    // 回傳 `true` 表示沒有錯誤。
	return true;
}

//---------------------------------------------------------------------------
String __fastcall TForm1::GetPath () {
	// 取得目前的下拉式選單選項表示該選擇哪個邏輯磁碟，
	// 並且尾端加上 `diskNotSleep.tmp` 的檔案名稱作為暫存檔的格式。
	return this->ComboBox1->Items->operator [](this->ComboBox1->ItemIndex) + "diskNotSleep.tmp";
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	// 時間到的就更新暫存檔內容。
	this->WriteBuffer();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	// 遞加進度條。
	this->ProgressBar1->Position += 10;
	// 當進度條已滿時，重設進度條。
	if (this->ProgressBar1->Position >= this->Timer1->Interval) {
        this->ProgressBar1->Position = 0;
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ApplicationEvents1Minimize(TObject *Sender)
{
	// 隱藏視窗本體。
   	this->Hide();
	this->WindowState = wsMinimized;

	// 在工作列呈現一個圖示。
	this->TrayIcon1->Visible = true;
	this->TrayIcon1->Animate = true;

	// 如果是初次最小化，而且程式又正在啟用中，
	// 那麼就丟出一個氣泡訊息表示程式正在背景執行。
	if (isFirstTimeMinimized && isEnabled) {
		this->TrayIcon1->ShowBalloonHint();
	}

	// 如果程式正在執行而且現在是最小化中，
	// 就將初次最小化設為 `false`，下次最小化時就不會出現正在執行的惱人提示。
	if (isEnabled) {
		isFirstTimeMinimized = false;
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Open() {
	// 隱藏工作列的圖示。
	this->TrayIcon1->Visible = false;

	// 顯示視窗本體。
	this->Show();
	this->WindowState = wsNormal;

	// 將視窗帶至最前面。
	Application->BringToFront();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Destroy() {
	// 遞迴整個可用磁碟名稱陣列，並將每個磁碟中的暫存檔案移除。
	for (int i = 0; i < availableDisks.size(); i++)
	{
		// 將存放的檔案從 UnicodeString 轉為 char*。
		String unicodeFilename = availableDisks[i] + "diskNotSleep.tmp";
		char *filename = AnsiString(unicodeFilename).c_str();

		// 移除檔案。
		remove(filename);
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
	// 開啟主體程式，並且帶至最前面。
	this->Open();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::TrayIcon1BalloonClick(TObject *Sender)
{
    // 開啟主體程式，並且帶至最前面。
	this->Open();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	// 在結束程式時，移除所有不必要的檔案。
	this->Destroy();
}
