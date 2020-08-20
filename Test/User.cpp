#include "User.h"

bool isSymbol(string s, char c)
{
	for (int i = 0; i < s.length(); i++)
		if (s[i] == c)
			return true;
	return false;
}

Student::Student(const Student& st)
{
	this->login = st.login;
	this->password = st.password;
	this->fio = st.fio;
	this->email = st.email;
	this->tel = st.tel;
	list<TestFinished> tf;
	tf = st.testFinished;
	this->testFinished = tf;
	list<TestUnFinished> tuf;
	tuf = st.testUnFinished;
	this->testUnFinished = tuf;
}

Student Student::operator=(const Student& st)
{
	this->login = st.login;
	this->password = st.password;
	this->fio = st.fio;
	this->email = st.email;
	this->tel = st.tel;
	list<TestFinished> tf;
	tf = st.testFinished;
	this->testFinished = tf;
	list<TestUnFinished> tuf;
	tuf = st.testUnFinished;
	this->testUnFinished = tuf;
	return *this;
}

void Student::pushTF(TestFinished t)
{
	testFinished.push_back(t);
}

void Student::pushTUF(TestUnFinished t)
{
	testUnFinished.push_back(t);
}

void Student::printTestResult(ostream& out)
{	
	out << "-------------------------------------------------------------------------------------------------" << endl;
	out << "                           ���������� ������������: " <<fio<< endl;
	out << "-------------------------------------------------------------------------------------------------" << endl;
	if (testFinished.size())
	{
		int nom = 1;
		for (auto& x : testFinished)
		{
			out << nom++ << ". ";
			x.print(out);
			out << "-------------------------------------------------------------------------------------------------" << endl;
		}
	}
	else {
		out << "��� ���������� ������" << endl;
		out << "-------------------------------------------------------------------------------------------------" << endl;
    }
	out << "                                  ������������� �����: " << endl;
	out << "-------------------------------------------------------------------------------------------------" << endl;
	if (testUnFinished.size())
	{
		int nom = 1;
		for (auto& x : testUnFinished)
		{
			out << nom++ << ". ";
			x.print(out);
			out << "-------------------------------------------------------------------------------------------------" << endl;
		}
	}
	else {
		out << "��� ������������� ������" << endl;
		out << "-------------------------------------------------------------------------------------------------" << endl;
	}
}

void Student::printTestResultStat(ostream& out)
{
	if (testFinished.size() || testUnFinished.size())
	{
		out << "-------------------------------------------------------------------------------------------------" << endl;
		out << "                           ���������� ������������: " << fio << endl;
		out << "-------------------------------------------------------------------------------------------------" << endl;
		if (testFinished.size())
		{
			int nom = 1;
			for (auto& x : testFinished)
			{
				out << nom++ << ". ";
				x.print(out);
				out << "-------------------------------------------------------------------------------------------------" << endl;
			}
		}		
		if (testUnFinished.size())
		{
			out << "                                  ������������� �����: " << endl;
			out << "-------------------------------------------------------------------------------------------------" << endl;
			int nom = 1;
			for (auto& x : testUnFinished)
			{
				out << nom++ << ". ";
				x.print(out);
				out << "-------------------------------------------------------------------------------------------------" << endl;
			}
		}		
	}
}

void Student::printUnFinished()
{
	int nom = 1;
	for (auto& x : testUnFinished)
	{		
		cout << nom++ << ". ";
		x.print(cout);
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}
}

int Student::getKolFinished()
{
	return testFinished.size();
}

int Student::getKolUnFinished()
{
	return testUnFinished.size();
}

void Student::getTUF(int nomTUF, TestUnFinished& tuf)
{
	auto it = testUnFinished.begin();
	advance(it, nomTUF - 1);
	tuf = *it;
}

void Student::delTUF(int nom)
{
	auto it = testUnFinished.begin();
	advance(it, nom - 1);
	testUnFinished.erase(it);
}

void Student::printStatTF(ostream& out, string nameCat, string nameTest)
{
	 for(auto& x:testFinished)
		 if (x.getName() == nameTest && x.getCategory() == nameCat)
			 out<<fio<< "  ������: " << x.getMark() << "   ���������� �������: " << x.getPer() 
			 << " %" << "���������� ��������� ������: " << x.getBalTest() << endl;
}

void Student::printStatTUF(ostream& out, string nameCat, string nameTest)
{
	for (auto& x : testUnFinished)
		if (x.getName() == nameTest && x.getCategory() == nameCat)
			out << fio << "  ���������� ���������� ��������: " << x.getKolQFinished() << "   ���������� �������: " << x.getPer() 
			<< " %" << "���������� ��������� ������: " << x.getBalTest() << endl;
}

User::User(const User& us)
{
	this->login = us.login;
	this->password = us.password;
	this->fio = us.fio;
	this->email = us.email;
	this->tel = us.tel;
}

User User::operator=(const User& us)
{
	this->login = us.login;
	this->password = us.password;
	this->fio = us.fio;
	this->email = us.email;
	this->tel = us.tel;
	return *this;
}

void User::setLogin(string log)
{
	login = log;
}

void User::setPas(string pas)
{
	password = pas;
}

void User::setFIO(string fi)
{
	fio = fi;
}

void User::setEmail(string em)
{
	email=em;
}

void User::setTel(string t)
{
	tel = t;
}

string User::getLogin()
{
	return login;
}

string User::getPassword()
{
	return password;
}

string User::getFIO()
{
	return fio;
}

string User::getEmail()
{
	return email;
}

string User::getTel()
{
	return tel;
}

void User::editProfile()
{
	cout << "�������, ���, ��������: " << fio << "   ��������?  1 - ��, 2 - ���"<<endl;
	char vibor = getValue12();
	if (vibor == '1')
	{
		string f,i,o;
		cout << "�������: ";
		cin>> f;
		cout << "���: ";
		cin >> i;
		cout << "��������: ";
		cin >> o;
		fio = f + " "+i+" " + o;
	}
	cout << "E-mail: " << email << "   ��������?  1 - ��, 2 - ���" << endl;
	char vibor1 = getValue12();
	if (vibor1 == '1')
	{	
		string em;
		do {
			cout << "������� ����� e-mail: ";
			cin>> em;
			if (!isSymbol(em, '@'))
				cout << "e-mail ������ ����� ��� name_your@name_service" << endl;
		} while (!isSymbol(em, '@'));
		email = em;		
	}
	cout << "�������: " << tel << "   ��������?  1 - ��, 2 - ���" << endl;
	vibor = getValue12();
	if (vibor == '1')
	{
		bool flag = true;
		do {
			cout << "������� ����� �������: ";
			string t;
			cin>> t;
			for (size_t i = 0; i < t.length(); i++)
			{
				if (!(t[i] == 40 || t[i] == 41 | t[i] == 43 || t[i] == 45
					|| t[i] >= 48 && t[i] <= 57))
				{
					flag = false;
					cout << "����� �������� ����� ��������� ������ ����� � ������� ( ) + -" << endl;
					break;
				}
			}
		} while (!flag);
		
	}
	cout <<" �������� ������ ?  1 - ��, 2 - ���" << endl;
	vibor= getValue12();
	if (vibor == '1')
	{
		cout << "������� ����������� ������: ";
		string oldpas;
		cin>> oldpas;
		hash<string>encrypt;
		oldpas = to_string(encrypt(oldpas));
		if (oldpas == password)
		{
			cout << "������� ����� ������ (����� �������, ����� �������): ";
			string pas;
			cin>>pas ;
			pas = to_string(encrypt(pas));
			password = pas;
		}
		else cout << "�������� ������!" << endl;
	}

}

TestFinished::TestFinished(string nam, string cat, int k, int p, int b, int m)
{
	name = nam;
	category = cat;
	kolPrav = k;
	percent = p;
	bal = b;
	mark = m;
}

TestFinished::TestFinished(const TestFinished& tf)
{
	this->name = tf.name;
	this->category = tf.category;
	this->kolPrav = tf.kolPrav;
	this->percent = tf.percent;
	this->bal = tf.bal;
	this->mark = tf.mark;
}

TestFinished TestFinished::operator=(const TestFinished& tf)
{
	this->name = tf.name;
	this->category = tf.category;
	this->kolPrav = tf.kolPrav;
	this->percent = tf.percent;
	this->bal = tf.bal;
	this->mark = tf.mark;
	return *this;
}

void TestFinished::print(ostream& out)
{	
	out << name << "   ( ���������: " << category <<" )   ������: " << mark << endl;
	out << "���������� �������: " << kolPrav << ", ��� ����������: " << percent << " %   ���������� ��������� ������: " << bal << endl;
}

TestUnFinished::TestUnFinished(string nam, string cat, int k, int p, int b, int kQ)
{
	name = nam;
	category = cat;
	kolPrav = k;
	percent = p;
	bal = b;
	kolQFinished = kQ;
}

TestUnFinished::TestUnFinished(const TestUnFinished& tf)
{
	this->name = tf.name;
	this->category = tf.category;
	this->kolPrav = tf.kolPrav;
	this->percent = tf.percent;
	this->bal = tf.bal;
	this->kolQFinished = tf.kolQFinished;	
}

TestUnFinished TestUnFinished::operator=(const TestUnFinished& tf)
{
	this->name = tf.name;
	this->category = tf.category;
	this->kolPrav = tf.kolPrav;
	this->percent = tf.percent;
	this->bal = tf.bal;
	this->kolQFinished = tf.kolQFinished;
	return *this;
}

void TestUnFinished::print(ostream& out)
{
	out << name << "   ( ���������: " << category << " )  ���������� ���������� ��������: " << kolQFinished << endl;
	out << "���������� �������: " << kolPrav << ", ��� ����������: " << percent << " %   ���������� ��������� ������: " << bal<< endl;
}

istream& operator>>(istream& in, User& us)
{
	string pas, fio, em, t;
	
	do {
		cout << "������: ";
		getline(in, pas);
		if (!pas.length() || isSymbol(pas, ' '))
			cout << "������ ������ ��������� ����� �������, ����� �������" << endl;
	} while (isSymbol(pas, ' '));
	cout << "�������, ���, ��������: ";
	getline(in, fio);
	do {
		cout << "e-mail: ";
		getline(in, em);
		if (!isSymbol(em, '@'))
			cout << "e-mail ������ ����� ��� name_your@name_service" << endl;
	} while (!isSymbol(em, '@'));
	/*bool flag = true;
	do {
		cout << "�������: ";		
		getline(in, t);
		for (size_t i = 0; i < t.length(); i++)
		{
			if (!(t[i] == 40 || t[i] == 41 | t[i] == 43 || t[i] == 45|| (t[i] >= 48 && t[i] <= 57)))
			{
				flag = false;
				cout << "����� �������� ����� ��������� ������ ����� � ������� ( ) + -" << endl;				
				break;
			}
		}
	} while (!flag);*/
	cout << "�������: ";
	getline(in, t);
	hash<string> encrypt;
	us.password = to_string(encrypt(pas));
	us.fio = fio;
	us.email = em;
	us.tel = t;
	return in;
}

ostream& operator<<(ostream& out, const User& us)
{
	out << us.login << endl;
	out << us.password << endl;
	out << us.fio << endl;
	out << us.email << endl;
	out << us.tel << endl;
	return out;
}

ostream& operator<<(ostream& out, const TestFinished& t)
{
	out << t.name << endl;
	out << t.category << endl;
	out << t.kolPrav << endl;
	out << t.percent << endl;
	out << t.bal << endl;
	out << t.mark << endl;
	return out;
}

ostream& operator<<(ostream& out, const TestUnFinished& t)
{
	out << t.name << endl;
	out << t.category << endl;
	out << t.kolPrav << endl;
	out << t.percent << endl;
	out << t.bal << endl;
	out << t.kolQFinished << endl;
	return out;
}

ostream& operator<<(ostream& out, const Student& us)
{
	out << us.login << endl;
	out << us.password<< endl;	
	out << us.fio << endl;
	out << us.email << endl;
	out << us.tel << endl;
	out << us.testFinished.size() << endl;
	if (us.testFinished.size() != 0)
	{
		for (auto& x : us.testFinished)
			out << x;
	}
		out << us.testUnFinished.size() << endl;
	
	if (us.testUnFinished.size() != 0)
	{
		for (auto& x : us.testUnFinished)
			out << x;
	}
	return out;
}
