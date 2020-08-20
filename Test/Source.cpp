#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<Windows.h>
#include"Color.h"
#include"Test.h"
#include"BaseTest.h"
#include <string>
using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
    BaseTest bt;
	bt.menu();
	/*AllTest at;
	at.menu();*/
	
}