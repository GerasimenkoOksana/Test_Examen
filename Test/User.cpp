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
	out << "                           Результаты тестирования: " <<fio<< endl;
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
		out << "нет пройденных тестов" << endl;
		out << "-------------------------------------------------------------------------------------------------" << endl;
    }
	out << "                                  Незавершенные тесты: " << endl;
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
		out << "нет незавершенных тестов" << endl;
		out << "-------------------------------------------------------------------------------------------------" << endl;
	}
}

void Student::printTestResultStat(ostream& out)
{
	if (testFinished.size() || testUnFinished.size())
	{
		out << "-------------------------------------------------------------------------------------------------" << endl;
		out << "                           Результаты тестирования: " << fio << endl;
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
			out << "                                  Незавершенные тесты: " << endl;
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
			 out<<fio<< "  Оценка: " << x.getMark() << "   Правильных ответов: " << x.getPer() 
			 << " %" << "Количество набранных баллов: " << x.getBalTest() << endl;
}

void Student::printStatTUF(ostream& out, string nameCat, string nameTest)
{
	for (auto& x : testUnFinished)
		if (x.getName() == nameTest && x.getCategory() == nameCat)
			out << fio << "  Количество пройденных вопросов: " << x.getKolQFinished() << "   Правильных ответов: " << x.getPer() 
			<< " %" << "Количество набранных баллов: " << x.getBalTest() << endl;
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
	cout << "Фамилия, имя, отчество: " << fio << "   Изменить?  1 - да, 2 - нет"<<endl;
	char vibor = getValue12();
	if (vibor == '1')
	{
		string f,i,o;
		cout << "Фамилия: ";
		cin>> f;
		cout << "Имя: ";
		cin >> i;
		cout << "Отчество: ";
		cin >> o;
		fio = f + " "+i+" " + o;
	}
	cout << "E-mail: " << email << "   Изменить?  1 - да, 2 - нет" << endl;
	char vibor1 = getValue12();
	if (vibor1 == '1')
	{	
		string em;
		do {
			cout << "Введите новый e-mail: ";
			cin>> em;
			if (!isSymbol(em, '@'))
				cout << "e-mail должен иметь вид name_your@name_service" << endl;
		} while (!isSymbol(em, '@'));
		email = em;		
	}
	cout << "Телефон: " << tel << "   Изменить?  1 - да, 2 - нет" << endl;
	vibor = getValue12();
	if (vibor == '1')
	{
		bool flag = true;
		do {
			cout << "Введите новый телефон: ";
			string t;
			cin>> t;
			for (size_t i = 0; i < t.length(); i++)
			{
				if (!(t[i] == 40 || t[i] == 41 | t[i] == 43 || t[i] == 45
					|| t[i] >= 48 && t[i] <= 57))
				{
					flag = false;
					cout << "Номер телефона может содержать только цифры и символы ( ) + -" << endl;
					break;
				}
			}
		} while (!flag);
		
	}
	cout <<" Изменить пароль ?  1 - да, 2 - нет" << endl;
	vibor= getValue12();
	if (vibor == '1')
	{
		cout << "Введите действующий пароль: ";
		string oldpas;
		cin>> oldpas;
		hash<string>encrypt;
		oldpas = to_string(encrypt(oldpas));
		if (oldpas == password)
		{
			cout << "Введите новый пароль (любые символы, кроме пробела): ";
			string pas;
			cin>>pas ;
			pas = to_string(encrypt(pas));
			password = pas;
		}
		else cout << "Неверный пароль!" << endl;
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
	out << name << "   ( Категория: " << category <<" )   Оценка: " << mark << endl;
	out << "Правильных ответов: " << kolPrav << ", что составляет: " << percent << " %   Количество набранных баллов: " << bal << endl;
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
	out << name << "   ( Категория: " << category << " )  Количество пройденных вопросов: " << kolQFinished << endl;
	out << "Правильных ответов: " << kolPrav << ", что составляет: " << percent << " %   Количество набранных баллов: " << bal<< endl;
}

istream& operator>>(istream& in, User& us)
{
	string pas, fio, em, t;
	
	do {
		cout << "Пароль: ";
		getline(in, pas);
		if (!pas.length() || isSymbol(pas, ' '))
			cout << "Пароль должен содержать любые символы, кроме пробела" << endl;
	} while (isSymbol(pas, ' '));
	cout << "Фамилия, имя, отчество: ";
	getline(in, fio);
	do {
		cout << "e-mail: ";
		getline(in, em);
		if (!isSymbol(em, '@'))
			cout << "e-mail должен иметь вид name_your@name_service" << endl;
	} while (!isSymbol(em, '@'));
	/*bool flag = true;
	do {
		cout << "телефон: ";		
		getline(in, t);
		for (size_t i = 0; i < t.length(); i++)
		{
			if (!(t[i] == 40 || t[i] == 41 | t[i] == 43 || t[i] == 45|| (t[i] >= 48 && t[i] <= 57)))
			{
				flag = false;
				cout << "Номер телефона может содержать только цифры и символы ( ) + -" << endl;				
				break;
			}
		}
	} while (!flag);*/
	cout << "телефон: ";
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
