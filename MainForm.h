﻿//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ButtonGroup.hpp>

#include "CargoFlow.h"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <iomanip>
#include <conio.h>


class TMF_CityRoutes : public TForm
{
__published:	// IDE-managed Components
	TPanel *P_Table;
	TStatusBar *SB_Inform;
	TMainMenu *Menu;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TStringGrid *T_CFCalc;
	TMenuItem *M_File;
	TMenuItem *M_Edit;
	TMenuItem *MF_Create;
	TMenuItem *MF_Open;
	TMenuItem *MF_Save;
	TMenuItem *MF_SaveAs;
	TMenuItem *ME_InsertCity;
	TMenuItem *ME_AddCity;
	TMenuItem *ME_DelCity;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *MF_Exit;
	TMenuItem *N4;
	TMenuItem *MF_Options;
	TMenuItem *MFO_EditMode;
	TMenuItem *MFO_AutoWidth;
	TMenuItem *MFO_GoTab;
	TImageList *ImageListStd;
	TImageList *ImageListStdDis;
	TToolBar *ToolBar1;
	TToolButton *CreateButton;
	TToolButton *OpenButton;
	TToolButton *SaveButton;
	TToolButton *AddCityButton;
	TToolButton *InsertCityButton;
	TToolButton *DelCityButton;
	TToolButton *CalcButton;
	TToolButton *SaveToTxt;
	TSaveDialog *SDText;
	TFontDialog *FontDlg;
	TMenuItem *MO_FontOptions;
	TMenuItem *N6;
	TToolButton *FontButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall MFO_EditModeClick(TObject *Sender);
	void __fastcall ME_InsertCityClick(TObject *Sender);
	void __fastcall ME_AddCityClick(TObject *Sender);
	void __fastcall MF_SaveClick(TObject *Sender);
	void __fastcall MF_ExitClick(TObject *Sender);
	void __fastcall ME_DelCityClick(TObject *Sender);
	void __fastcall MF_SaveAsClick(TObject *Sender);
	void __fastcall T_CFCalcDrawCell(TObject *Sender,
					  int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall MF_OpenClick(TObject *Sender);
	void __fastcall MFO_GoTabClick(TObject *Sender);
	void __fastcall T_CFCalcKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall T_CFCalcSetEditText(TObject *Sender,
						   int ACol, int ARow, const UnicodeString Value);
	void __fastcall T_CFCalcGetEditText(TObject *Sender,
						   int ACol, int ARow, UnicodeString &Value);
	void __fastcall T_CFCalcDblClick(TObject *Sender);
	void __fastcall CalcButtonClick(TObject *Sender);
	void __fastcall T_CFCalcContextPopup(TObject *Sender,
											TPoint &MousePos, bool &Handled);
	void __fastcall MF_CreateClick(TObject *Sender);
	void __fastcall T_CFCalcRowMoved(TObject *Sender,
									int FromIndex, int ToIndex);
	void __fastcall T_CFCalcColumnMoved(TObject *Sender,
									int FromIndex, int ToIndex);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall T_CFCalcSelectCell(TObject *Sender,
									int ACol, int ARow, bool &CanSelect);
	void __fastcall SaveToTxtClick(TObject *Sender);
	void __fastcall MO_FontOptionsClick(TObject *Sender);
	void __fastcall FontDlgApply(TObject *Sender, HWND Wnd);



private:	// User declarations
public:	// User declarations

	bool IsDelete;
	bool CanBlock;
	tddMatr CargoF;
	tdStrs NameCity;
	UnicodeString SavedCell;
	int FSortedColNbr;
	int FSortedRowNbr;
    TSize ts;

	int __fastcall TMF_CityRoutes::CalcGridColWidth(TStringGrid *table,
																int colIdx);
	__fastcall TMF_CityRoutes(TComponent* Owner);
	void __fastcall SaveData(bool showDlg);
	void __fastcall CreateEmptyT();
	bool __fastcall RecreateArrays(bool ThisIsSave = true);
};
//---------------------------------------------------------------------------
extern PACKAGE TMF_CityRoutes *MF_CityRoutes;
//---------------------------------------------------------------------------
#endif
