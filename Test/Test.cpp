#include "Test.h"
#include<conio.h>


char getValue()
{
	char buff[100] = "";
	int i = 0;
	unsigned char c;
	do
	{
		cout << '\r' << buff;
		c = _getch();
		if (isdigit(c) && i == 0)
		{
			buff[i++] = c;
			buff[i] = '\0';
		}

	} while (c != '\r');
	cout << endl;
	return buff[0];
}

char getValue0123()
{
	char buff[100] = "";
	int i = 0;
	unsigned char c;
	do
	{
		cout << '\r' << buff;
		c = _getch();
		if ((c == '1' || c == '2' || c == '3' || c == '0') && i == 0)
		{
			buff[i++] = c;
			buff[i] = '\0';
		}
	} while (c != '\r');
	cout << endl;
	return buff[0];
}

char getValue12()
{
	char buff[100] = "";
	int i = 0;
	unsigned char c;
	do
	{
		cout << '\r' << buff;
		c = _getch();
		if ((c == '1' || c == '2') && i == 0)
		{
			buff[i++] = c;
			buff[i] = '\0';
		}
	} while (c != '\r');
	char v = buff[0];
	cout << endl;
	return v;
}

ostream& operator<<(ostream& out, const Question& q)
{
	out << q.ques << endl;
	out << q.numAnswer << endl;
	out << q.bal << endl;
	out << q.answer.size() << endl;
	for (auto& x : q.answer)
		out << x << endl;
	return out;
}

ostream& operator<<(ostream& out, const Test& t)
{
	out << t.name << endl;
	out << t.category << endl;
	out << t.comment << endl;
	out << t.active << endl;
	out << t.bal << endl;
	out << t.unFinished << endl;
	out << t.questions.size() << endl;
	for (auto& x : t.questions)
		out << x;
	return out;
}

QuestionYesNo::QuestionYesNo()
{
	answer.push_back("�����");
	answer.push_back("�������");
}

void QuestionYesNo::newQues()
{
	cout << "������: " << endl;
	getline(cin, ques);
	cout << "�������� ������: 1 - �����, 2 - �������" << endl;
	cout << "������� ����� ����������� ������: " << endl;
	numAnswer = getValue12() - 48;
	cout << "���������� ������ �� ���������� �����: ";
	cin >> bal;
	cin.ignore();
}

Question::Question(string ques_, int numAnswer_, int bal_)
{
	ques = ques_;
	numAnswer = numAnswer_;
	bal = bal_;
}

void Question::print(ostream& out)
{
	out << ques << endl;
	int nom = 1;
	out << "  �������� ������:" << endl;
	for (auto& x : answer)
		out << nom++ << ". " << x << endl;
	out << "����� ����������� ������: " << numAnswer << " ��� �� ���������� �����: " << bal << endl;
	out << "------------------------------------------------------------------" << endl;
}

void Question::printGo()
{
	cout << ques << endl;
	int n = 1;
	cout << "  �������� ������:" << endl;
	for (auto& x : answer)
		cout << n++ << ". " << x << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "�������� ����� ������: "<<endl;
}

void QuestionOneOfMany::newQues()
{
	cout << "������: " << endl;
	getline(cin, this->ques);
	cout << "�������� ������: " << endl;
	string ans;
	char c = 0, vibor = '1';
	int nom = 1;
	do {
		cout << nom++ << ". ";
		/*if (_kbhit())
			c = _getch();
		if (c == 27)  break;	*/
		getline(cin, ans);
		answer.push_back(ans);
		cout << "�������� ��� ������� ������: 1 - ��, 2 - ���" << endl;
		vibor = getValue12();
	} while (vibor == '1');
	cout << "������� ����� ����������� ������: " << endl;
	numAnswer = getValue() - 48;
	while (numAnswer <= 0 || numAnswer >= nom)
	{
		cout << "������! ����� ����������� ������ ������ ���� �� 1 �� " << nom - 1 << endl;
		numAnswer = getValue() - 48;
	}
	cout << "���������� ������ �� ���������� �����: ";
	cin >> bal;
	cin.ignore();
}

void Question::edit(int& d)
{
	print(cout);
	cout << "�������� ������? 1 - ��, 2 - ���" << endl;
	char vibor = getValue12();
	if (vibor == '1')
	{
		cout << "������� ������: ";
		getline(cin, ques);
		cout << "������ �������!" << endl;
	}
	cout << "�������� ������ ? 1 - ��, 2 - ���" << endl;
	vibor = getValue12();
	while (vibor == '1')
	{
		cout << "������� ����� ������, ������� ������ ��������" << endl;
		int nom = getValue() - 48;
		while (nom <= 0 || nom > answer.size())
		{
			cout << "������! ����� ������ ������ ���� �� 1 �� " << answer.size() << endl;
			nom = getValue() - 48;
		}
		cout << "������� ����� �����: ";
		string ans;
		getline(cin, ans);
		auto it = answer.begin();
		advance(it, nom - 1);
		answer.erase(it);
		answer.insert(it, ans);
		cout << "����� �������!" << endl;
		cout << "�������� ��� ���� �����? 1 - ��, 2 - ���" << endl;
		vibor = getValue12();
	}
	do {
		cout << "�������� ��� ���� �����? 1 - ��, 2 - ���" << endl;
		vibor = getValue12();
		if (vibor == '1')
		{
			cout << "������� �����: ";
			string ans;
			getline(cin, ans);
			answer.push_back(ans);
			cout << "����� ��������!" << endl;
		}
	} while (vibor == 1);
	cout << "����� ����������� ������: " << numAnswer << " ��������? 1 - ��, 2 - ���" << endl;
	vibor = getValue12();
	if (vibor == '1')
	{
		cout << "������� ����� ����������� ������: ";
		cin >> numAnswer;
		cout << "����� ����������� ������ �������!" << endl;
	}
	cout << "���� �� ���������� �����: " << bal << " ��������? 1 - ��, 2 - ���" << endl;
	vibor = getValue12();
	d = 0;
	if (vibor == '1')
	{
		d = bal;
		cout << "������� ����: ";
		cin >> bal;
		d = bal - d;
		cout << "���� �������!" << endl;
	}
	system("pause");
}

Test::Test(const Test& obj)
{
	this->name = obj.name;
	this->category = obj.category;
	this->comment = obj.comment;
	this->active = obj.active;
	this->bal = obj.bal;
	this->unFinished = obj.unFinished;
	list<Question> q = obj.questions;
	this->questions = q;
}

Test Test::operator=(const Test& obj)
{
	this->name = obj.name;
	this->category = obj.category;
	this->comment = obj.comment;
	this->active = obj.active;
	this->bal = obj.bal;
	this->unFinished = obj.unFinished;
	list<Question> q = obj.questions;
	this->questions = q;
	return *this;
}

void Test::changeActive()
{
	if (active)
		cout << "���� �������";
	else cout << "���� ���������";
	cout << "  �������� ? 1 - �� 2 - ���:  " << endl;
	char vibor = getValue12();
	if (vibor == '1')
		active = !active;
}

void Test::edit()
{
	do
	{
		system("cls");
		cout << "------------------------------------------------------------------" << endl;
		cout << "                       �������������� ����� " << endl;
		cout << "------------------------------------------------------------------" << endl;
		cout << "1 - �������� ������ " << endl;
		cout << "2 - ������� ������ " << endl;
		cout << "3 - ������������� ������ " << endl;
		cout << "4 - �������� �������� �����" << endl;
		cout << "5 - �������� ����������� � �����" << endl;
		cout << "6 - �������� ���������� �����" << endl;
		cout << "0 - �����" << endl;
		char vibor = getValue();
		switch (vibor)
		{
		case '1': addQuest(); break;
		case '2': delQuest(); break;
		case '3': editQuest(); break;
		case '4':
			cout << "�������� �����: " << name << endl;
			cout << "������� ����� ��������: ";
			getline(cin, name);
			cout << "�������� ����� ��������" << endl;
			break;
		case '5':
			cout << "����������� � �����: " << comment << endl;
			cout << "������� ����� �����������: ";
			getline(cin, comment);
			cout << "����������� �������" << endl;
			break;
		case '6': changeActive(); break;
		case '0': return;
		default: break;
		}
	} while (true);
}

void Test::addQuest()
{
	char vibor = '1';
	do {
		cout << "�������� ���: 1 - �����/�������  2 - ���� �� ����������" << endl;
		char type = getValue12();
		if (type == '1')
		{
			QuestionYesNo q;
			q.newQues();
			questions.push_back(q);
			bal += q.getBal();
		}
		else
		{
			QuestionOneOfMany q;
			q.newQues();
			questions.push_back(q);
			bal += q.getBal();
		}
		cout << "�������� ��� ������?  1 - ��  2 - ���: ";
		vibor = getValue12();
	} while (vibor == '1');
}

void Test::delQuest()
{
	int nom = 1;
	for (auto& x : questions)
	{
		cout << "������ �" << nom++ << ".  ";
		x.print(cout);
	}
	cout << "������� ����� ������� ��� ��������: " << endl;
	int nomQ = getValue() - 48;
	if (nomQ > 0 && nomQ < nom)
	{
		auto it = questions.begin();
		advance(it, nomQ - 1);
		questions.erase(it);
		cout << "������ ������ �� �����!" << endl;
	}
	else cout << "�������� �����" << endl;
	system("pause");
}

void Test::editQuest()
{
	int nom = 1;
	for (auto& x : questions)
	{
		cout << "������ �" << nom++ << ".  ";
		x.print(cout);
	}
	cout << "������� ����� ������� ��� ��������������: " << endl;
	int nomQ = getValue() - 48;
	if (nomQ > 0 && nomQ < nom)
	{
		auto it = questions.begin();
		advance(it, nomQ - 1);
		int d;
		it->edit(d);
		bal += d;
		cout << "������ �������!" << endl;
	}
	else cout << "�������� �����" << endl;
	system("pause");
}

void Test::print(ostream& out)
{
	out << "------------------------------------------------------------------" << endl;
	int vir;
	if (getSizeName() < 80)
		vir = 80 - (80 - getSizeName()) / 2 - 1;
	else vir = 79;
	out << setw(vir) << name << endl;
	if (!active)
		cout << "(���� �� �������!)" << endl;
	out << "------------------------------------------------------------------" << endl;
	out << "���������: " << category << endl;
	out << comment << endl;
	out << "��������� �������� � �����: " << questions.size() << endl;
	out << "������������ ���������� ������: " << bal << endl;
	out << "������������ ������:  12" << endl;
	out << "------------------------------------------------------------------" << endl;
	int nm = 1;
	for (auto& x : questions)
	{
		out << "������ �" << nm++ << ":   ";
		x.print(out);
	}
}

void Test::create()
{
	cout << "������� �������� �����: ";
	getline(cin, this->name);
	cout << "������� ����������� (���������) � �����: ";
	getline(cin, this->comment);
	this->active = true;
	int b = 0;
	list < Question> quest;
	char vibor = 1;
	do {
		cout << "1 - �������� ����� ������ � �����, 2 - ��������� �������� �����" << endl;
		vibor = getValue12();
		if (vibor == '1')
		{
			cout << "�������� ���: 1 - �����/�������  2 - ���� �� ����������" << endl;
			char type = getValue12();
			if (type == '1')
			{
				QuestionYesNo q;
				q.newQues();
				quest.push_back(q);
				b += q.getBal();
			}
			else
			{
				QuestionOneOfMany q;
				q.newQues();
				quest.push_back(q);
				b += q.getBal();
			}
		}
	} while (vibor == '1');
	this->questions = quest;
	this->bal = b;
	this->unFinished = false;
}

void Test::go(int& kolQFinished, int &kolPrav, int& b)
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "����: " << name << " �� ���������: " << category << endl;
	cout << comment << endl;
	cout << "���� �������� " << questions.size() << " ��������, ������������ ���: " << bal << endl;
	cout << "�� ������ � ����� ������ �������� ������������ � ���������� � ����� ������� �����" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	int nom = 1;
	b=0;
	kolPrav = 0;
	kolQFinished = 0;
	for (auto& x : questions)
	{
		system("cls");
		cout << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << " ������ �" << nom++ << ". ";
		x.printGo();
		int nomAns = getValue()-48;
		if (nomAns == x.getNomPravAnswer())
		{
			b += x.getBal();
			kolPrav++;
		}
		kolQFinished++;
		if (nom - 1 < questions.size())
		{
			cout << "����������? 1 - �� 2 - �������� ������������" << endl;
			char vibor = getValue12();
			if (vibor == '2') 	break;
		}
	}
}

void Test::goOld(int kolQFin1, int kolPrav1, int b1, int& kolQFin2, int& kolPrav2, int& b2)
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "����: " << name << " �� ���������: " << category << endl;
	cout << comment << endl;
	cout << "���� �������� ����� " << questions.size() << " ��������, ������������ ���: " << bal << endl;
	cout << "�� �������� �� "<<kolQFin1<<" ��������, �� ��� "<<kolPrav1<<" ���������� ������� � ������� "<<b1<< " ������"<< endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	int nom = 1;
	b2 = b1;
	kolPrav2 = kolPrav1;
	kolQFin2 = kolQFin1;
	for (auto& x : questions)
	{
		if (nom > kolQFin1)
		{
			system("cls");
			cout << endl;
			cout << "-------------------------------------------------------------------------------------------------" << endl;
			cout << " ������ �" << nom++ << ". ";
			x.printGo();
			int nomAns = getValue() - 48;
			if (nomAns == x.getNomPravAnswer())
			{
				b2 += x.getBal();
				kolPrav2++;
			}
			kolQFin2++;
			if (nom - 1 < questions.size())
			{
				cout << "����������? 1 - �� 2 - �������� ������������" << endl;
				char vibor = getValue12();
				if (vibor == '2')
					break;
			}
		}
		else nom++;
	}
}

void AllTest::addTest()
{
	system("cls");
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "                   �������� ������ �����" << endl;
	cout << "------------------------------------------------------------------" << endl;
	Test t;
	if (!allTest.size())
	{
		cout << "������� �������� ��������� �����:";
		string cat;
		cin.ignore();
		getline(cin, cat);
		list<Test> l;
		allTest.insert(make_pair(cat, l));
		t.setCategory(cat);
		t.create();
		auto it = allTest.begin();
		allTest[it->first].push_back(t);
	}
	else
	{
		cout << "�������� ��������� �� ������:" << endl;
		int nom = 1;
		cout << "------------------------------------------------------------------" << endl;
		for (auto& x : allTest)
		{
			cout << nom++ << "." << x.first << endl;
		}
		char vibor = getValue();
		if (vibor - 48 > 0 && (vibor - 48) <= allTest.size())
		{
			int vib = vibor - 48;
			auto it = allTest.begin();
			advance(it, vib - 1);
			t.setCategory(it->first);
			cin.ignore();
			t.create();
			allTest[it->first].push_back(t);
		}
		else {
			cout << "�������� �����" << endl;
			system("pause");
		}
	}
	save();
}

void AllTest::addCategory()
{
	cout << "������� �������� ��������� �����:";
	string cat;
	getline(cin, cat);
	list<Test> l;
	allTest.insert(make_pair(cat, l));
	cout << "��������� ���������" << endl;
	system("pause");
	save();
}

void AllTest::delTest()
{
	system("cls");
	cout << "------------------------------------------------------------------" << endl;
	cout << "                       �������� ����� " << endl;
	cout << "------------------------------------------------------------------" << endl;
	printCategoryWithNameTest(cout);
	cout << "�������� ���������" << endl;
	int nomCat = getValue() - 48;
	if (nomCat > 0 && nomCat <= allTest.size())
	{
		auto it = allTest.begin();
		advance(it, nomCat - 1);
		string nameCat = it->first;
		cout << "���������: " << nameCat << " �������� �����:" << endl;
		int nom = 1;
		for (auto& x : allTest[nameCat])
			cout << nom++ << ". " << x.getName() << endl;
		cout << "�������� ����� �����: " << endl;
		int nomT = getValue() - 48;
		if (nomT > 0 && nomT < nom)
		{
			if (nameCat == "�����")
			{
				cout << "�� �������, ��� ������ ������� ���� �" << nomT << " �� ���������: " << nameCat << "   1 - ��  2 - ������" << endl;
				char uver = getValue12();
				if (uver == '1')
				{
					auto it = allTest[nameCat].begin();
					advance(it, nomT - 1);
					allTest[nameCat].erase(it);
					cout << "���� ������" << endl;
				}
				else cout << "�������� ��������" << endl;
			}
			else {
				cout << "1 - ����������� ���� � ����� (�������� ��������������)" << endl;
				cout << "2 - ������� ���� (��� ����������� ��������������)" << endl;
				char ud = getValue12();
				if (ud == '1')
				{
					auto it = allTest[nameCat].begin();
					advance(it, nomT - 1);
					if (!allTest.count("�����")) {
						list<Test> l;
						allTest.insert(make_pair("�����", l));
					}
					Test test = *it;
					test.setCategory("�����");
					allTest["�����"].push_back(test);
					allTest[nameCat].erase(it);
					cout << "���� ��������� � �����" << endl;
				}
				else {
					cout << "�� �������, ��� ������ ������� ���� �" << nomT << " �� ���������: " << nameCat << "   1 - ��  2 - ������" << endl;
					char uver = getValue12();
					if (uver == '1')
					{
						auto it = allTest[nameCat].begin();
						advance(it, nomT - 1);
						allTest[nameCat].erase(it);
						cout << "���� ������" << endl;
					}
					else cout << "�������� ��������" << endl;
				}
			}
		}
		else cout << "�������� ����� �����" << endl;
	}
	else cout << "�������� ����� ���������" << endl;
	system("pause");
	save();
}

void AllTest::delCategory()
{
	system("cls");
	cout << "------------------------------------------------------------------" << endl;
	cout << "                       �������� ��������� " << endl;
	cout << "------------------------------------------------------------------" << endl;
	printCategoryWithNameTest(cout);
	cout << "�������� ���������" << endl;
	int nomCat = getValue() - 48;
	if (nomCat > 0 && nomCat <= allTest.size())
	{
		auto it = allTest.begin();
		advance(it, nomCat - 1);
		string nameCat = it->first;
		if (!allTest[nameCat].size())
		{
			allTest.erase(it);
			cout << "��������� �������" << endl;
		}
		else {
			if (nameCat == "�����") {
				cout << "����� �������� " << allTest[nameCat].size() << " �����(��)" << endl;
				cout << "����� �������� ��������� ������ ����� ����� ������� �������� ��� ����������� ��������������" << endl;
				cout << "����������? 1 - ��  2 - ������ " << endl;
				char vibor = getValue12();
				if (vibor == '1')
				{
					allTest[nameCat].clear();
					allTest.erase(it);
					cout << "��������� �������" << endl;
				}
				else {
					cout << "�������� ��������" << endl;
					system("pause");
					return;
				}
			}
			else {
				cout << "��������� ��������� �������� " << allTest[nameCat].size() << " �����(��), � ������ �������� ��� ����� ���������� � �����" << endl;
				cout << "����� �������� ������ ����� ����� ���������� � ��������� ����� � ������������ ��������������" << endl;
				cout << "����������? 1 - ��  2 - ������ " << endl;
				char vibor = getValue12();
				if (vibor == '1')
				{
					if (!allTest.count("�����")) {
						list<Test> l;
						allTest.insert(make_pair("�����", l));
					}
					for (auto& x : allTest[nameCat])
					{
						x.setCategory("�����");
						allTest["�����"].push_back(x);
					}
					allTest[nameCat].clear();
					allTest.erase(it);
					cout << "��������� �������, ����� ���������� � �����" << endl;
				}
				else {
					cout << "�������� ��������" << endl;
					system("pause");
					return;
				}
			}
		}
	}
	else cout << "�������� ����� ���������" << endl;
	system("pause");
	save();
}

void AllTest::editTest()
{
	system("cls");
	cout << "------------------------------------------------------------------" << endl;
	cout << "                       �������������� ����� " << endl;
	cout << "------------------------------------------------------------------" << endl;
	printCategoryWithNameTest(cout);
	cout << "�������� ���������" << endl;
	int nomCat = getValue() - 48;
	if (nomCat > 0 && nomCat <= allTest.size())
	{
		auto it = allTest.begin();
		advance(it, nomCat - 1);
		string nameCat = it->first;
		cout << "���������: " << nameCat << " �������� �����:" << endl;
		int nom = 1;
		for (auto& x : allTest[nameCat])
			cout << nom++ << ". " << x.getName() << endl;
		cout << "�������� ����� �����: " << endl;
		int nomT = getValue() - 48;
		if (nomT > 0 && nomT < nom)
		{
			auto it = allTest[nameCat].begin();
			advance(it, nomT - 1);
			it->edit();
			cout << "��������� � ���� �������" << endl;
		}
		else cout << "�������� ����� �����" << endl;
	}
	else cout << "�������� ����� ���������" << endl;
	system("pause");
	save();
}

void AllTest::restoreTest()
{
	if (!allTest.count("�����") || !allTest["�����"].size())
		cout << "��� ������ ��� ��������������" << endl;
	else {
		system("cls");
		cout << "------------------------------------------------------------------" << endl;
		cout << "                     �������������� ����� �� ������" << endl;
		cout << "------------------------------------------------------------------" << endl;
		cout << "����� �������� �����:" << endl;
		int nom = 1;
		for (auto& x : allTest["�����"])
			cout << nom++ << ". " << x.getName() << endl;
		cout << "�������� ����� �����: " << endl;
		int nomT = getValue() - 48;
		if (nomT > 0 && nomT < nom)
		{
			printCategoryWithoutArc();
			cout << "�������� ���������, � ������� ����� ������������ ����" << endl;
			int nomCat = getValue()-48;
			if (nomCat > 0 && nomCat < allTest.size())
			{
				auto it = allTest.begin();
				advance(it, nomCat);
				string nameCat = it->first;
				auto it1 = allTest["�����"].begin();
				advance(it1, nomT - 1);
				Test test = *it1;
				test.setCategory(nameCat);
				allTest[nameCat].push_back(test);
				allTest["�����"].erase(it1);
				cout << "���� ������������" << endl;
			}
			else cout << "�������� ����� ���������" << endl;
		}
		else cout << "�������� ����� �����" << endl;
	}system("pause");
	save();
}

void AllTest::editCategory()
{
	system("cls");
	cout << "------------------------------------------------------------------" << endl;
	cout << "                       �������������� ��������� " << endl;
	cout << "------------------------------------------------------------------" << endl;
	printCategory();
	cout << "�������� ���������" << endl;
	int nomCat = getValue() - 48;
	if (nomCat > 0 && nomCat <= allTest.size())
	{
		auto it = allTest.begin();
		advance(it, nomCat - 1);
		string nameCat = it->first;
		if (nameCat == "�����")
			cout << "��������� ����� �� �������� ��������������" << endl;
		else {
			cout << "������� ����� �������� ���������: ";
			string newName;
			getline(cin, newName);
			if (allTest[nameCat].size())
			{
				for (auto& x : allTest[nameCat])
					x.setCategory(newName);
			}
			list<Test> l=allTest[nameCat];
			allTest.insert(make_pair(newName, l));
			allTest.erase(it);			
		}
	}
	else cout << "�������� ����� ���������" << endl;
	system("pause");
	save();
}

void AllTest::save()
{
	ofstream fout("test.txt");
	fout << getKolTest() << endl;
	for (auto& x : allTest)
	{
		for (auto& it : x.second)
		{
			fout << it;
		}
	}
	fout.close();
	//cout << "����� ���������!" << endl;
	//system("pause");
}

void AllTest::load()
{
	ifstream fin("test.txt");
	if (fin.is_open())
	{
		int k;
		fin >> k;
		fin.get();
		for (int i = 0; i < k; i++)
		{
			int bal_, kolQ;
			string name_, category_, comment_;
			bool active_, unFinished_;
			getline(fin, name_);
			getline(fin, category_);
			getline(fin, comment_);
			fin >> active_;
			fin >> bal_;
			fin >> unFinished_;
			fin >> kolQ;
			fin.get();
			Test t(name_, category_, comment_, active_, bal_, unFinished_);
			list<Question> lq;
			for (int i = 0; i < kolQ; i++)
			{
				string ques_, ans_;
				int numAnswer_, bal_, kolAns;
				getline(fin, ques_);
				fin >> numAnswer_;
				fin >> bal_;
				Question q(ques_, numAnswer_, bal_);
				fin >> kolAns;
				fin.get();
				list<string> answer_;
				for (int i = 0; i < kolAns; i++)
				{
					getline(fin, ans_);
					answer_.push_back(ans_);
				}
				q.setAnswer(answer_);
				lq.push_back(q);
			}
			t.setQuestions(lq);
			if (allTest.count(category_))
			{
				auto it = allTest.find(category_);
				it->second.push_back(t);
			}
			else
			{
				list<Test> lt;
				lt.push_back(t);
				allTest.insert(make_pair(category_, lt));
			}
		}
		cout << "����� ���������" << endl;
	}
	else  cout << "���� � ������� ������ �� ������" << endl;	
}

void AllTest::printCategory()
{
	if (allTest.size())
	{
		int nom = 1;
		cout << "------------------------------------------------------------------" << endl;
		for (auto& x : allTest)
		{
			cout << nom++ << "." << x.first << " -  " << x.second.size() << " ����." << endl;
		}
		cout << "------------------------------------------------------------------" << endl;
	}
	else cout << "��� ����������� ���������!" << endl;
}

void AllTest::printCategoryWithoutArc()
{
	if (allTest.size())
	{
		int nom = 1;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		for (auto& x : allTest)
		{
			if (x.first != "�����")
			cout << nom++ << "." << x.first << " -  " << x.second.size() << " ����." << endl;
		}
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}
	else cout << "��� ����������� ���������!" << endl;
}

void AllTest::print()
{
	system("cls");
	cout << "1 - ������ ���� ������" << endl;
	cout << "2 - ������� ���������" << endl;
	char vibor = getValue12();
	if (vibor == '1')
		printAllTest();
	else {
		printCategory();
		cout << "�������� ���������:" << endl;
		int nomCat = getValue() - 48;
		if (nomCat > 0 && nomCat <= allTest.size())
		{
			auto it = allTest.begin();
			advance(it, nomCat - 1);
			string nameCat = it->first;
			cout << "------------------------------------------------------------------" << endl;
			cout << "1 - ������ ���� ������ ��������� ���������" << endl;
			cout << "2 - ������� ����" << endl;
			char kolT = getValue12();
			if (kolT == '1')
				printAllTestFromCateg(nameCat);
			else
			{
				cout << "------------------------------------------------------------------" << endl;
				cout << "���������: " << nameCat << " �������� " << allTest[nameCat].size() << " �����(��)" << endl;
				int nom = 1;
				for (auto& x : allTest[nameCat])
					cout << nom++ << ". " << x.getName() << endl;
				cout << "�������� ����� �����: " << endl;
				int nomT = getValue() - 48;
				if (nomT > 0 && nomT < nom)
				{
					auto it = allTest[nameCat].begin();
					advance(it, nomT - 1);
					system("cls");
					it->print(cout);
				}
				else cout << "������������ �����" << endl;
				system("pause");
			}
		}
		else
		{
			cout << "�������� ����� ���������" << endl;
			system("pause");
		}
	}
}

void AllTest::printFileCategory()
{
	cout << "������� ��� �����: ";
	string namef;
	do
	{
		cin >> namef;
		if (namef == "test.txt" || namef == "user.txt")
			cout << "��� ��������� ����� ������, ������� ������ ���: ";
	} while (namef == "test.txt" || namef == "user.txt");
	ofstream fout(namef);
	printCategoryWithNameTest(fout);
	fout.close();
	cout << "������ ������� ��������� � ����!" << endl;
	system("pause");
}

void AllTest::printCategoryWithNameTest(ostream& out)
{
	int nom = 1;
	for (auto& x : allTest)
	{
		out << nom++ << ".  " << x.first << " - " << x.second.size() << " �����(��)" << endl;
		for (auto& it : x.second)
			out << "            " << it.getName() << endl;
		out << "------------------------------------------------------------------" << endl;
	}
}

void AllTest::printAllTest()
{
	if (allTest.size())
	{
		for (auto& x : allTest)
		{
			system("cls");
			cout << "------------------------------------------------------------------" << endl;
			cout << x.first << " -  " << x.second.size() << " ������" << endl;
			cout << "------------------------------------------------------------------" << endl;
			system("pause");
			for (auto& it : x.second)
			{
				system("cls");
				it.print(cout);
				system("pause");
			}
		}
	}
	else {
		cout << "��� ����������� ������" << endl;
		system("pause");
	}
}

void AllTest::printFileAllTest(string namef)
{
	if (allTest.size())
	{
		ofstream fout(namef);
		fout << "------------------------------------------------------------------" << endl;
		for (auto& x : allTest)
		{
			fout << x.first << " -  " << x.second.size() << " ������" << endl;
			fout << "------------------------------------------------------------------" << endl;
			for (auto& it : x.second)
			{
				it.print(fout);
			}
		}
		fout.close();
		cout << "����� ������� �������� � ��������� ����!" << endl;
		//system("pause");
	}
	else {
		cout << "��� ����������� ������" << endl;
		//system("pause");
	}
}

void AllTest::printFileAllTestFromCateg(string namef, string nameCat)
{
	ofstream fout(namef);
	fout << "------------------------------------------------------------------" << endl;
	fout << "���������: " << nameCat << " - " << allTest[nameCat].size() << " ������" << endl;
	fout << "------------------------------------------------------------------" << endl;
	for (auto& it : allTest[nameCat])
		it.print(fout);
	fout.close();
	cout << "��� ����� ���������: " << nameCat << " �������� � ��������� ����" << endl;
}

void AllTest::printAllTestFromCateg(string nameCat)
{
	cout << "------------------------------------------------------------------" << endl;
	cout << "���������: " << nameCat << " - " << allTest[nameCat].size() << " ������" << endl;
	cout << "------------------------------------------------------------------" << endl;
	for (auto& x : allTest[nameCat])
	{
		x.print(cout);
		system("pause");
		system("cls");
	}
}

void AllTest::printFileOneTest(string namef, string nameCat, int nom)
{
	ofstream fout(namef);
	auto it = allTest[nameCat].begin();
	advance(it, nom - 1);
	it->print(fout);
	fout.close();
	cout << "���� ������� � ��������� ����" << endl;
}

void AllTest::printFile()
{
	system("cls");
	cout << "------------------------------------------------------------------" << endl;
	cout << "                       ������ ������ � ����" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "������� ��� �����: ";
	string namef;
	do
	{
		cin >> namef;
		if (namef == "test.txt" || namef == "user.txt")
			cout << "��� ��������� ����� ������, ������� ������ ���: ";
	} while (namef == "test.txt" || namef == "user.txt");
	cout << "1 - ������ � ���� ���� ������" << endl;
	cout << "2 - ������� ���������" << endl;
	char vibor = getValue12();
	if (vibor == '1')
		printFileAllTest(namef);
	else {
		printCategory();
		cout << "�������� ���������:" << endl;
		int nomCat = getValue() - 48;
		if (nomCat > 0 && nomCat <= allTest.size())
		{
			auto it = allTest.begin();
			advance(it, nomCat - 1);
			string nameCat = it->first;
			cout << "------------------------------------------------------------------" << endl;
			cout << "1 - ������ � ���� ���� ������ ��������� ���������" << endl;
			cout << "2 - ������� ����" << endl;
			char kolT = getValue12();
			if (kolT == '1')
				printFileAllTestFromCateg(namef, nameCat);
			else
			{
				cout << "------------------------------------------------------------------" << endl;
				cout << "���������: " << nameCat << " �������� " << allTest[nameCat].size() << " �����(��)" << endl;
				int nom = 1;
				for (auto& x : allTest[nameCat])
					cout << nom++ << ". " << x.getName() << endl;
				cout << "�������� ����� �����: " << endl;
				int nomT = getValue() - 48;
				if (nomT > 0 && nomT < nom)
				{
					printFileOneTest(namef, nameCat, nomT);
				}
				else cout << "������������ �����" << endl;
			}
		}
		else	cout << "�������� ����� ���������" << endl;
	}
	system("pause");
}

int AllTest::getKolTest()
{
	int kol = 0;;
	for (auto& x : allTest)
	{
		kol += x.second.size();
	}
	return kol;
}

int AllTest::getSize()
{
	return allTest.size();
}

void AllTest::workTest()
{	
	do
	{
		system("cls");
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << setw(65) << " ������ � �������  "<<endl;		
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - �������� ���� " << endl;
		cout << "2 - ������� ���� " << endl;
		cout << "3 - ������������� ���� " << endl;
		cout << "4 - ������������ ���� �� ������ " << endl;
		cout << "5 - ������ �� �����" << endl;
		cout << "6 - ��������� � ����" << endl;
		cout << "0 - �����" << endl;
		char vibor = getValue();
		switch (vibor)
		{
		case '1':addTest(); break;
		case '2': delTest(); break;
		case '3': editTest(); break;
		case '4': restoreTest(); break;
		case '5': print(); break;
		case '6': printFile(); break;
		case '0': return;
		default: break;
		}
	} while (true);
}

void AllTest::workCategory()
{
	do
	{
		system("cls");
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << setw(65) << " ������ � �����������  " << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - �������� ��������� " << endl;
		cout << "2 - ������� ��������� " << endl;
		cout << "3 - ������������� ��������� " << endl;
		cout << "4 - ������ �� ����� " << endl;
		cout << "5 - ��������� � ����" << endl;
		cout << "0 - �����" << endl;
		char vibor = getValue();
		switch (vibor)
		{
		case '1': addCategory(); break;
		case '2': delCategory(); break;
		case '3': editCategory(); break;
		case '4': printCategoryWithNameTest(cout); system("pause"); break;
		case '5': printFileCategory(); break;
		case '0': return;
		default: break;
		}
	} while (true);
}

void AllTest::getTest(Test& t, bool& uspeh)
{
	printCategoryWithoutArc();
	cout << "�������� ����� ���������" << endl;
	int nomCat = getValue() - 48;
	int kolCat = getSize();
	if (allTest.count("�����"))
		kolCat--;
	if (nomCat > 0 && nomCat <= kolCat)
	{
		auto it = allTest.begin();
		if (allTest.count("�����"))
			advance(it, nomCat);
		else advance(it, nomCat-1);
		string nameCat = it->first;
		cout << "���������: " << nameCat << " �������� �����:" << endl;
		int nom = 1;
		for (auto& x : allTest[nameCat])			
				cout << nom++ << ". " << x.getName() << endl;		
			cout << "�������� ����� �����: " << endl;
			int nomT = getValue() - 48;
			if (nomT > 0 && nomT < nom)
			{
				auto it = allTest[nameCat].begin();
				advance(it, nomT - 1);
				t = *it;
				uspeh = true;
			}
			else {
				cout << "�������� ����� �����" << endl;
				uspeh = false;
				system("pause");
			}				
	}
	else {
		cout << "�������� ����� ���������" << endl;
		uspeh = false;
		system("pause");
	}
}

void AllTest::getOldTest(string nameTest, string nameCat, Test& t, bool& uspeh)
{
	uspeh = false;
	for (auto& x : allTest[nameCat])
		if (x.getName() == nameTest)
		{
			t = x;
			uspeh = true;
		}
}

string AllTest::getNameCatStat(int nomCat)
{
	auto it = allTest.begin();
	if (allTest.count("�����"))
		advance(it, nomCat);
	else advance(it, nomCat - 1);
	return it->first;
}

string AllTest::getNameTest(string nameCat, int nomTest)
{
	auto it = allTest[nameCat].begin();
	advance(it, nomTest);
	return it->getName();
}

void AllTest::printNameTestStat(string nameCat)
{
	int n = 1;
	for (auto& x : allTest[nameCat])
		cout << n++ << ". " << x.getName() << endl;
}

int AllTest::getKolTestCat(string nameCat)
{
	return allTest[nameCat].size();
}

void AllTest::menu()
{
	do
	{
		system("cls");
		cout << "1 + ������ � ������� " << endl;
		cout << "2 + ������ � �����������" << endl;
		cout << "3 + ���������" << endl;
		cout << "4 + ���������" << endl;
		cout << "0 + �����" << endl;
		char vibor = getValue();
		switch (vibor)
		{
		case '1': workTest(); break;
		case '2': workCategory(); break;
		case '3': save(); break;
		case '4': load(); system("pause"); break;
		case '0': exit(0); break;
		default: break;
		}
	} while (true);
}

Test::Test(string name_, string category_, string comment_, bool active_, int bal_, bool unFinished_)
{
	name = name_;
	category = category_;
	comment = comment_;
	active = active_;
	bal = bal_;
	unFinished = unFinished_;
}
