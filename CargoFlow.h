//---------------------------------------------------------------------------
#pragma once

#ifndef CargoFlowH
#define CargoFlowH
//---------------------------------------------------------------------------

#include "CityRoutes_PCH1.h"

typedef int MatrType;
typedef DynamicArray<DynamicArray<MatrType> > tddMatr;
typedef DynamicArray<UnicodeString> tdStrs;
//typedef unsigned int uint;


enum failsOpen {GoodO, MemoryFailO, FileFailO, EmptyNameO, EmptyTableO};
enum failsSave {GoodS, FileFailS, EmptyNameS};

failsSave Save_Cities(tddMatr& CargoFlow, tdStrs& CityNames, AnsiString FileName);

failsOpen Load_Cities(tddMatr& CargoFlow, tdStrs& CityNames, AnsiString FileName);

float ExportCrg2City(tddMatr CargoFlow, int RowIndex);

float ImportCrg2City(tddMatr CargoFlow, int ColIndex);

float CalcP(tddMatr CargoFlow);

float ImportCrgFlWeight(tddMatr CargoFlow, int ColIndex, float P = -1);

float ExportCrgFlWeight(tddMatr CargoFlow, int RowIndex, float P = -1);

#endif