//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.AppEvnts.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTrayIcon *TrayIcon1;
	TLabel *Label1;
	TComboBox *ComboBox1;
	TGroupBox *GroupBox1;
	TLabel *Label2;
	TLabel *Label3;
	TProgressBar *ProgressBar1;
	TLabel *Label4;
	TButton *Button1;
	TButton *Button2;
	TTimer *Timer1;
	TComboBox *ComboBox2;
	TTimer *Timer2;
	TApplicationEvents *ApplicationEvents1;
	void __fastcall Button2Click(TObject *Sender);
	String __fastcall GetPath();
	bool __fastcall WriteBuffer();
	int __fastcall StringToInterval(String string);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall ApplicationEvents1Minimize(TObject *Sender);
	void __fastcall TrayIcon1Click(TObject *Sender);
	void __fastcall TrayIcon1BalloonClick(TObject *Sender);
	void __fastcall Open();
	void __fastcall Destroy();
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
