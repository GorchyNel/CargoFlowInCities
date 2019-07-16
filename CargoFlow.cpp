﻿//---------------------------------------------------------------------------

#pragma hdrstop

#include "CargoFlow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include <fstream>

failsSave Save_Cities(tddMatr& CargoFlow, tdStrs& CityNames,
                                                            AnsiString FileName)
 {
 if(FileName.Length() == 0) return EmptyNameS;

 ofstream File;

 //открытие файла на запись с очисткой
 File.open(FileName.c_str(), ios::binary | ios::trunc);
 if(File.fail()) return FileFailS;

 // Сохранение пустой таблицы
 if(CityNames.Length == 0 /*тогда и CargoFlow.Length == 0 */)
 {
 File.close();
 return GoodS;
 }

 //записываем длину массива Названия Городов
 int length/*переменная для хранения длинн*/ = CityNames.Length;
 File.write((char*)&length, sizeof(length));

 /*Циклически записываем массив Названия Городов в виде:
	длина строки - строка(Назвыание Города)*/
 for(int i=0; i<CityNames.Length; i++)
 {
   length = CityNames[i].Length();
   File.write((char*)&length, sizeof(length));
   if(length > 0)
	  File.write((char*)CityNames[i].w_str(), sizeof(wchar_t)* length);
 }

 /*Циклически записываем матрицу (построчно) грузопотоков
	между Городами*/
 for(int i=0; i<CargoFlow.Length; i++)
   File.write((char*)&CargoFlow[i][0], sizeof(MatrType) * CargoFlow[i].Length);

  File.close();
  return GoodS;
 }

failsOpen Load_Cities(tddMatr& CargoFlow, tdStrs& CityNames,
                                                        AnsiString FileName)
{
 if(!FileName.Length()) return EmptyNameO;

 ifstream File;

 File.open(FileName.c_str(), ios::binary); //открытие файла на чтение

 if(File.eof()) return EmptyTableO; //сработает, если в файле нет данных
 if(File.fail()) return FileFailO; //сработает, если нет доступа к файлу

 int length; //переменная для хранения длинн

//----------------------Считывание названий городов---------------------------

 File.read((char*)&length, sizeof(length));//считывание длинны массива строк
 if(length == 0) return EmptyTableO;//сработает,

 try
 {
   CityNames.set_length(length);
 }
 catch(...)
 {
   File.close();
   return MemoryFailO;
 }

 for(int i=0; i<CityNames.Length; i++)
 {
   File.read((char*)&length, sizeof(length));//считывание длины строки

   if(length > 0)
   {
   //выделение памяти под строку Название Города
	try
	{
	  CityNames[i].SetLength(length); /*установка длины строки Название Города*/
	}
	catch(...)
	{
	  CityNames.set_length(0); //удаление массива строк Названия Городов
	  File.close(); //закрытие файла
	  return MemoryFailO;
	}
	//считывание в созданную строку строку из файла
	File.read((char*)CityNames[i].w_str(), sizeof(wchar_t) * length);
   }
   else CityNames[i] = "";
 }

//-----------------Считывание данных о грузоперевозках-------------------------

 //выделение памяти под матрицу
 try
 {
  CargoFlow.set_length(CityNames.Length/*длина массива с
	названиями городов совпадает с размерностями матрицы*/);
  for(int i = 0; i < CargoFlow.Length; i++)
	  CargoFlow[i].set_length(CargoFlow.Length/*матрица квадратная*/);
 }
 catch(...)
 {
  CargoFlow.set_length(0);//если матрица Грузопоток
  //была заполнена, очищаем ее
  CityNames.set_length(0);//удаление массива строк Названия Городов
  File.close(); //закрытие файла
  return MemoryFailO;
 }

 //Циклично считываем в созданную матрицу данные из файла
 for(int i=0; i<CityNames.Length; i++)
	File.read((char*)&CargoFlow[i][0], sizeof(MatrType) * CargoFlow[i].Length);

 File.close();//закрываем файл
 return GoodO; //говорим, что все хорошо
}

float ExportCrg2City(tddMatr CargoFlow, int RowIndex)
{
 RowIndex--;
 if(CargoFlow.Length==0 || RowIndex < 0 || RowIndex >= CargoFlow.Length)
																 return -1;
 float sum = 0;
 for (int i = 0; i < CargoFlow[0].Length; i++)
					   sum += CargoFlow[RowIndex][i];
 return sum;
}

float ImportCrg2City(tddMatr CargoFlow, int ColIndex)
{
 ColIndex--;
 if(CargoFlow.Length==0 || ColIndex < 0 || ColIndex >= CargoFlow.Length)
																 return -1;
 float sum = 0;
 for (int i = 0; i < CargoFlow.Length; i++)
					   sum += CargoFlow[i][ColIndex];
 return sum;
}

float CalcP(tddMatr CargoFlow)
{
  if(CargoFlow.Length==0) return -1;
  float P;
  for (int i = 0; i < CargoFlow.Length; i++)
	 for (int j = 0; j < CargoFlow[0].Length; j++)
		  P += CargoFlow[i][j];
  return  P;
}

float ImportCrgFlWeight(tddMatr CargoFlow, int ColIndex, float P)
//ввозимые грузы для города считаем по столбцу
{
  ColIndex--;
  if(CargoFlow.Length==0 || ColIndex < 0 || ColIndex >= CargoFlow.Length
														  || P < 0) return -1;
  float CalcRes = 0;
  if(P == -1) P = CalcP(CargoFlow);
  for (int i = 0; i < CargoFlow.Length; i++)
	  if(i != /*на самом деле RowIndex, который ==*/ColIndex)
		   CalcRes += CargoFlow[i][ColIndex];

  return  (float)(1 / P * CalcRes);
}

float ExportCrgFlWeight(tddMatr CargoFlow, int RowIndex, float P)
{
  RowIndex--;
  if(CargoFlow.Length==0 || RowIndex < 0 || RowIndex >= CargoFlow.Length
														  || P < 0) return -1;
  float CalcRes = 0;
  if(P == -1) P = CalcP(CargoFlow);
  for (int i = 0; i < CargoFlow[0].Length; i++)
	  if(i != /*на самом деле ColIndex, который ==*/RowIndex)
		   CalcRes += CargoFlow[RowIndex][i];
  return (float)(1 / P * CalcRes);
}
