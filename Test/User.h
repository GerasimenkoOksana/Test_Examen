#pragma once
#include<string>
#include<map>
#include<iostream>
#include<iomanip>
#include<list>
#include"Color.h"
#include"Test.h"

using namespace std;

bool isSymbol(string s, char c);


class User
{
protected:
	string login;
	string password;
	string fio;
	string email;
	string tel;	
	
public:
	User() {};
	User(const User& us);
	User operator=(const User& us);
	void setLogin(string log);
	void setPas(string pas);
	void setFIO(string fi);
	void setEmail(string em);
	void setTel(string t);
	string getLogin();
	string getPassword();
	string getFIO();
	string getEmail();
	string getTel();
	friend istream& operator>>(istream& in, User& us);
	friend ostream& operator<<(ostream& out, const User& us);
	void editProfile();
};



class TestFinished
{
protected:	
	string name;
	string category;		
	int kolPrav; //кол-во правильных ответов
	int percent; //процент правильных ответов
	int bal;
private:
	int mark;
public:
	TestFinished() {};
	TestFinished(string nam, string cat, int k, int p, int b, int m);
	TestFinished(const TestFinished& tf);
	TestFinished operator=(const TestFinished& tf);
	friend ostream& operator<<(ostream& out, const TestFinished& t);
	void print(ostream& out);
	string getName() { return name; }
	string getCategory() { return category; }
	int getKolPrav() { return kolPrav; }
	int getPer() { return percent; }
	int getBalTest() { return bal; }
	int getMark() { return mark; }
};
class TestUnFinished :public TestFinished
{
	int kolQFinished;
public:
	TestUnFinished() {};
	TestUnFinished(string nam, string cat, int k, int p, int b, int kQ);
	TestUnFinished(const TestUnFinished& tf);
	TestUnFinished operator=(const TestUnFinished& tf);
	friend ostream& operator<<(ostream& out, const TestUnFinished& t);
	void print(ostream& out);
	int getKolQFinished() { return kolQFinished; }
};
class Student :public User
{
	list<TestFinished> testFinished;
	list<TestUnFinished> testUnFinished;	

public:	
	Student() {};
	Student(const Student& st);
	Student operator=(const Student& st);
	void pushTF(TestFinished t);
	void pushTUF(TestUnFinished t);
	friend ostream& operator<<(ostream& out, const Student& us);
	void printTestResult(ostream& out);
	void printTestResultStat(ostream& out);
	void printUnFinished();
	int getKolFinished();
	int getKolUnFinished();
	void getTUF(int nomTUF, TestUnFinished& tuf);
	void delTUF(int nom);
	void printStatTF(ostream& out, string nameCat, string nameTest);
	void printStatTUF(ostream& out, string nameCat, string nameTest);
};

