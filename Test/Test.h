#pragma once
#include<string>
#include<map>
#include<iterator>
#include<conio.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<list>
using namespace std;

char getValue();
char getValue0123();
char getValue12();

class Question
{
protected:
	string ques;	
	list<string> answer;
	int numAnswer;
	int bal;
public:
	Question() {};
	Question(string ques_,int numAnswer_, int bal_) ;
	void setAnswer(list<string> answer_) { answer = answer_; }
	void print(ostream& out);
	void printGo();
	int getBal() { return bal; }
	int getNomPravAnswer() { return numAnswer; }
	void edit(int &d);
	friend ostream& operator<<(ostream& out, const Question& q);
 };


class QuestionYesNo : public Question
{
	
public:
	QuestionYesNo();
	void newQues();
};

class QuestionOneOfMany : public Question
{
	
public:
	void newQues();	
};

class Test
{	
	string name;
	string category;
	string comment;	
	bool active=0;
	list<Question> questions;
	int bal=0;	
	bool unFinished=0; 

public:
	Test() {};
	Test(string name_, string category_, string comment_, bool active_, int bal_, bool unFinished_);
	Test(const Test& obj);
	Test operator=(const Test& obj);	
	string getName() { return name; }
	string getCategory() { return category; }
	string getComment() { return comment; }
	bool getActive() { return active; }
	int getBal() { return bal; }
	int getKolQ() { return questions.size(); }
	bool getUnFinished() { return unFinished; }	
	int getSizeName() { return name.length(); }
	void changeActive();	
	void setCategory(string cat) { category = cat; }
	void setQuestions(list<Question> q) { questions = q; }	
	void edit();
	void addQuest();
	void delQuest();
	void editQuest();
	void print(ostream& out);	
	friend ostream& operator<<(ostream& out, const Test& t);
	void create();
	void go(int& kolQFinished, int &kolPrav, int& b);
	void goOld(int kolQFin1, int kolPrav1, int b1, int& kolQFin2, int &kolPrav2, int& b2);
};

class AllTest
{
	map<string, list<Test>> allTest;
public:
	void addTest();
	void addCategory();
	void delTest();
	void delCategory();
	void editTest();
	void restoreTest();
	void editCategory();
	void save();
	void load ();	
	void menu(); 	
	void printAllTest();
	void printCategory();
	void printCategoryWithoutArc();
	void print() ;
	void printFileCategory();
	void printCategoryWithNameTest(ostream& out);
	void printAllTestFromCateg(string nameCat);
	void printFile();
	void printFileAllTest(string namef);
	void printFileAllTestFromCateg(string namef,string nameCat);
	void printFileOneTest(string namef, string nameCat, int nom);	
	int getKolTest();
	int getSize();
	void workTest();
	void workCategory();
	void getTest(Test& t, bool &uspeh);
	void getOldTest(string nameTest, string nameCat, Test& t, bool& uspeh);
	string getNameCatStat(int nomCat);
	string getNameTest(string nameCat, int nomTest);
	void printNameTestStat(string nameCat);
	int getKolTestCat(string nameCat);
	 
	
};

   