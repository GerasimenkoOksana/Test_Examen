#pragma once
#include"User.h"
#include"Test.h"

 
class BaseTest
{
	map<string, Student> stud;
	User admin;
	AllTest t;
	
public:
	void menu();
	void vhod();
	void vhod(string log);
	void vhodAdmin();
	void print();
	void registr();
	void load();
	void saveAll();
	void saveUser();
	void goTest(string login);
	void goNewTest(string login);
	void goOldTest(string login, int nomTUF);
	void editStudProfile(string login);
	void editAdminProfile();
	void getStat();
	void editStud();
	void printAllStudent();
	void delStud();
	void addStud();
	void editStudProfileAdmin();
	void printStatAll();
	void printStatCatTest();
	void printStatStud();
	void printStat(ostream& out, string nameCat, string nameTest);
};
