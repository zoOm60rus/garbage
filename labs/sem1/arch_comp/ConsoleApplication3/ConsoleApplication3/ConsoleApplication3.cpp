// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <new>
#include <random>
#include <fstream>
using namespace std;

int MAX_NUMBER = 16384;			//максимальное длина числа
int MAX_COUNT_BORD = 24;			//максимальное количество интервалов
bool GetInformation(int & NumRanDat, int* & Number, int & Xmin, int & Xmax, int & NInt, int* & LGrInt);//получение данных
bool InsertBorder(int* & LGrInt, int cur_len, int num, int min, int max);//вставка произвольных интервалов в массив
void GetRandomNum(int* & Number, int len, int min, int max);//генерирование случайных чисел
void InitArray(int* & Number, int len);		//запыление массива 0-ми
void PrintResult1(int* Number, int len);
void PrintResult2(int* LGrInt, int* CountNum, int len);

extern "C"
{
	void SORTSTEP1(int Number[], int NumRanDat, int CountNumUnit1[], int Xmin);
	void SORTSTEP2(int CountNumUnit1[], int lenUnit1, int LGrInt[], int CountNumN[], int NInt, int Xmin);
}

int main(void)
{
	int NumRanDat = 0; 		//количество псевдослучайных чисел
	int *Number = NULL; 		//массив чисел
	int Xmin = 0; 			//левая граница диапазона
	int Xmax = 0; 			//правая граница диапазона
	int NInt = 0; 			//количество границ (не в ключей граничный значения)
	int *LGrInt = NULL;		 //массив левых границ
	int *CountNumUnit1 = NULL;	//для интервалов единичной длины
	int lenUnit1 = 0;
	int* CountNumN = NULL; 	//для интервалов произвольной длины
	if (!GetInformation(NumRanDat, Number, Xmin, Xmax, NInt, LGrInt)) //получить значения
		return 1;
	lenUnit1 = Xmax - Xmin + 1;	 //выделение памяти
	CountNumUnit1 = new int[lenUnit1];
	if (!CountNumUnit1) { cout << "Ошибка: не удалось выделить память\n"; return 1; }
	InitArray(CountNumUnit1, lenUnit1);
	CountNumN = new int[NInt];
	if (!CountNumN) { cout << "Ошибка: не удалось выделить память\n"; return 1; }
	InitArray(CountNumN, NInt);
	SORTSTEP1(Number, NumRanDat, CountNumUnit1, Xmin); // распределение по интервалам 1
	SORTSTEP2(CountNumUnit1, lenUnit1, LGrInt, CountNumN, NInt, Xmin); //распределение по интервалам произвольной длины
	PrintResult1(CountNumUnit1, lenUnit1); 	//вывод результата первой процедуры
	PrintResult2(LGrInt, CountNumN, NInt); 	//вывод результата второй процедуры
	system("pause");
	delete[] CountNumN;
	delete[] CountNumUnit1;
	delete[] Number;
	delete[] LGrInt;
	return 0;
}

bool GetInformation(int & NumRanDat, int* & Number, int & Xmin, int & Xmax, int & NInt, int* & LGrInt)
{
	int len = 0;
	int i = 0;
	setlocale(LC_ALL, "rus");		//получение количества чисел
	cout << "1.Введите количество случайных чисел, 0 < N < 16384: ";
	cin >> NumRanDat;
	cout << NumRanDat << endl;
	while (NumRanDat <= 0 || NumRanDat >= 16384)
	{
		cin.clear();
		cin.sync();
		cout << "Ошибка: число должно быть в правильном диапазоне\n"
			<< " Введите количество случайных чисел: ";
		cin >> NumRanDat;
	}	//получение диапазона
	cout << "2.Введите диапазон случайных чисел: \n"
		<< "От: ";
	cin >> Xmin;
	cout << "До :";
	cin >> Xmax;
	while (Xmax <= Xmin)
	{
		cin.clear();
		cin.sync();
		cout << "Ошибка: правая граница диапазона должна быть больше левой\n"
			<< "Введите правую границу: ";
		cin >> Xmax;
	}	//выделяем память
	Number = new int[NumRanDat];
	if (!Number) { cout << "Ошибка: не удалось выделить память\n"; return false; }
	GetRandomNum(Number, NumRanDat, Xmin, Xmax); //получение количества интервалов
	cout << "3.Введите количество интервалов, но которые разобьется диапазон 0 < N < 25: ";
	cin >> NInt;
	while (NInt <= 0 || NInt >= 25)
	{
		cin.clear();
		cin.sync();
		cout << "Ошибка: количество интервалов не в указанном диапазоне\n"
			<< "Введите количество интервалов: ";
		cin >> NInt;
	}
	LGrInt = new int[NInt];
	if (!Number) { cout << "Ошибка: не удалось выделить память\n"; return 0; } //получение интервалов
	cout << "4.Выбор интервалов.\n"
		<< "\t1.Установить интервалы равномерно по диапазону\n"
		<< "\t2.Установить интервалы самостоятельно\n";
	while (i == 0)
	{
		cin >> i;
		switch (i)
		{
		case 1:		len = Xmax - Xmin;
			for (i = 0; i<NInt; i++) { LGrInt[i] = Xmin + len / NInt*i; }
			break;
		case 2:
			LGrInt[0] = Xmin;
			cout << "Граница 1: " << Xmin << "\n\n";
			for (i = 1; i<NInt; i++) {
				do {
					cout << "Граница " << i + 1 << ": ";
					cin >> len;
				} while (!InsertBorder(LGrInt, i, len, Xmin, Xmax));
			}
			break;
		default:
			cout << "Ошибка: неверный номер операции, введите номер еще раз: ";
			i = 0;
			break;
		}
	}
	return true;
}
bool InsertBorder(int* & LGrInt, int cur_len, int num, int min, int max)
{
	if (num < min || num > max) { cout << "Ошибка: число не в пределах интервала или уже задано\n"; return false; }
	int i = 0;
	int j = 0;
	while (i<cur_len)
	{
		if (LGrInt[i]<num) {
			i++;
		}
		else if (LGrInt[i] == num)
		{
			cout << "Ошибка: число уже присутствует в массиве\n";
			return false;
		}
		else {
			j = i;
			j = cur_len;
			while (i<j) {
				LGrInt[j] = LGrInt[j - 1];
				j--;
			}
			break;
		}
	}
	LGrInt[i] = num;
	return true;
}
void GetRandomNum(int* & Number, int len, int min, int max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(min, max);
	for (--len; len >= 0; len--) {
		Number[len] = distr(gen);
	}
}

void InitArray(int* & Arr, int len)
{
	for (--len; len >= 0; len--) {
		Arr[len] = 0;
	}
}

void PrintResult1(int* Number, int len)
{
	int i = 0;
	ofstream fout;
	fout.open("result1.txt");
	if (!fout.is_open()) {
		cout << "Error: can't open file " << '\n';
		return;
	}
	cout << "Распределение случайных чисел по интервалам единичной длины:\n";
	cout << "№\t Лев.гр.\tКл-во\t\n";
	fout << "Распределение случайных чисел по интервалам единичной длины:\n";
	fout << "№\t Лев.гр.\tКл-во\t\n";
	for (i = 0; i<len; i++)
	{
		cout << i << '\t' << i << "\t\t" << Number[i] << '\n';
		fout << i << '\t' << i << "\t\t" << Number[i] << '\n';
	}
	cout << "-----------------------------\n";
	fout.close();
}

void PrintResult2(int* LGrInt, int* CountNum, int len)
{
	int i = 0;
	ofstream fout;
	fout.open("result2.txt");
	if (!fout.is_open()) {
		cout << "Error: can't open file " << '\n';
		return;
	}
	cout << "Распределение случайных чисел по заданным интервалам:\n";
	cout << "№\t Лев.гр.\tКл-во\t\n";
	fout << "Распределение случайных чисел по инервалам еденичной длины:\n";
	fout << "№\t Лев.гр.\tКл-во\t\n";
	for (i = 0; i<len; i++) {
		cout << i << '\t' << LGrInt[i] << "\t\t" << CountNum[i] << '\n';
		fout << i << '\t' << LGrInt[i] << "\t\t" << CountNum[i] << '\n';
	}
	fout.close();

}
