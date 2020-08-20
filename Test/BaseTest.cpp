#include "BaseTest.h"



void BaseTest::menu()
{
	load();
	do {
		system("cls");
		cout << "---------------------------------------------------------------------------------------------------------------" << endl;
		cout << setw(110) << "Здравствуйте, Гость" << endl;
		cout << "                             Добро пожаловать в систему тестирования BASETEST!!!" << endl;
		cout << "---------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - Вход" << endl;
		cout << "2 - Регистрация" << endl;
		cout << "3 - Просмотр тестов" << endl;
		cout << "0 - Закрыть программу" << endl;
		char vibor = getValue0123();
		switch (vibor)
		{
		case '1': vhod(); break;
		case '2': registr(); break;
		case '3': print(); break;
		case '0': exit(0); break;
		}
	} while (true);
}

void BaseTest::vhod()
{
	string log, pas;
	cout << "Логин: ";
	cin >> log;
	hash<string>encrypt;
	log = to_string(encrypt(log));
	if (admin.getLogin() == log)
	{
		cout << "Пароль: ";
		cin >> pas;
		pas = to_string(encrypt(pas));
		if (admin.getPassword() == pas)
			vhodAdmin();
		else {
			cout << "Неверный пароль! " << endl;
			system("pause");
		}
	}
	else {
		if (stud.count(log))
		{
			cout << "Пароль: ";
			cin >> pas;
			pas = to_string(encrypt(pas));
			if (stud[log].getPassword() == pas)
				vhod(log);
			else {
				cout << "Неверный пароль! " << endl;
				system("pause");
			}
		}
		else {
			cout << "Пользователь с таким логином не найден" << endl;
			system("pause");
		}
	}

}

void BaseTest::vhod(string log)
{
	do
	{
		system("cls");
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
		cout << setw(65) << " Вы вошли в режиме <Студент> под именем  ";
		SetColor(10, 0);
		cout << stud[log].getFIO() << endl;
		SetColor(15, 0);
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "1. Редактировать профиль" << endl;
		cout << "2. Статистика: пройденные и незавершенные тесты" << endl;
		cout << "3. Пройти тест" << endl;
		cout << "0. Выход" << endl;
		char vibor = getValue0123();
		switch (vibor)
		{
		case '1': editStudProfile(log); break;
		case '2': system("cls"); stud[log].printTestResult(cout); system("pause"); break;
		case '3': goTest(log); break;
		case '0': return;
		default: break;
		}
	} while (true);
}

void BaseTest::vhodAdmin()
{
	do
	{
		system("cls");
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
		cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
		SetColor(10, 0);
		cout << admin.getFIO() << endl;
		SetColor(15, 0);
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "1. Редактировать профиль" << endl;
		cout << "2. Статистика" << endl;
		cout << "3. Управление студентами" << endl;
		cout << "4. Работа с тестами" << endl;
		cout << "5. Работа с категориями" << endl;
		cout << "0. Выход" << endl;
		char vibor = getValue();
		switch (vibor)
		{
		case '1': editAdminProfile(); break;
		case '2': getStat(); break;
		case '3': editStud(); break;
		case '4': t.workTest(); break;
		case '5': t.workCategory(); break;
		case '0': return;
		default: break;
		}
	} while (true);
}

void BaseTest::print()
{
	if (t.getSize())
		t.printCategoryWithNameTest(cout);
	else cout << "Нет сохраненных тестов" << endl;
	system("pause");
}

void BaseTest::registr()
{
	system("cls");
	cout << "------------------------------------------------------------------" << endl;
	cout << "                       Регистрация нового пользователя " << endl;
	cout << "------------------------------------------------------------------" << endl;
	if (admin.getLogin() != "" && admin.getPassword() != "")
	{
		cout << "                       Регистрация нового студента " << endl;
		cout << "------------------------------------------------------------------" << endl;
		Student st;
		string log,log1;
		cin.ignore();
		do {
			cout << "Логин: ";			
			getline(cin, log);
			if (!log.length() || isSymbol(log, ' '))
				cout << "Логин должен содержать любые символы, кроме пробела" << endl;
			hash<string> encrypt;
			log1 = to_string(encrypt(log));
			if (stud.count(log1))
				cout << "Такой логин занят. Выберите другой"<<endl;
		} while (isSymbol(log, ' ') || stud.count(log1));		
		st.setLogin(log1);
		cin >> st;		
		stud.insert(make_pair(st.getLogin(), st));
		saveUser();
		vhod(st.getLogin());
	}
	else {
		cout << "В системе нет администратора, вы можете зарегистрироваться как админ и создать свою базу тестов" << endl;
		cout << "Продолжить?  1 - да  2 - нет" << endl;
		char vibor = getValue12();
		if (vibor == '1')
		{
			cout << "                       Регистрация администратора " << endl;
			cout << "------------------------------------------------------------------" << endl;
			string log;
			do {
				cout << "Логин: ";
				getline(cin, log);
				if (!log.length() || isSymbol(log, ' '))
					cout << "Логин должен содержать любые символы, кроме пробела" << endl;				
			} while (isSymbol(log, ' '));
			hash<string> encrypt;
			admin.setLogin(to_string(encrypt(log)));
			cin >> admin;
			saveUser();
			vhodAdmin();
		}
		else return;
	}
	system("pause");
}

void BaseTest::load()
{
	ifstream fin("user.txt");
	if (fin.is_open())
	{
		t.load();
		string log, pas, fi, em, t;
		getline(fin, log);
		getline(fin, pas);
		getline(fin, fi);
		getline(fin, em);
		getline(fin, t);
		admin.setLogin(log);
		admin.setPas(pas);
		admin.setFIO(fi);
		admin.setEmail(em);
		admin.setTel(t);
		int kolStud;
		fin >> kolStud;
		for (size_t i = 0; i < kolStud; i++)
		{
			fin.get();
			Student st;
			getline(fin, log);
			getline(fin, pas);
			getline(fin, fi);
			getline(fin, em);
			getline(fin, t);
			st.setLogin(log);
			st.setPas(pas);
			st.setEmail(em);
			st.setFIO(fi);
			st.setTel(t);
			int kolFin;
			fin >> kolFin;
			if (kolFin)
			{
				string nam, cat;
				int kP, p, b, m;
				for (size_t i = 0; i < kolFin; i++)
				{
					fin.get();
					getline(fin, nam);
					getline(fin, cat);
					fin >> kP;
					fin >> p;
					fin >> b;
					fin >> m;
					TestFinished tf(nam, cat, kP, p, b, m);
					st.pushTF(tf);
				}
			}
			fin >> kolFin;
			if (kolFin)
			{
				string nam, cat;
				int kP, p, b, kQ;
				for (size_t i = 0; i < kolFin; i++)
				{
					fin.get();
					getline(fin, nam);
					getline(fin, cat);
					fin >> kP;
					fin >> p;
					fin >> b;
					fin >> kQ;
					TestUnFinished tuf(nam, cat, kP, p, b, kQ);
					st.pushTUF(tuf);
				}
			}
			stud.insert(make_pair(log, st));
		}
	}
	fin.close();
}

void BaseTest::saveAll()
{
	t.save();
	saveUser();
}

void BaseTest::saveUser()
{
	ofstream fout("user.txt");
	fout << admin;
	fout << stud.size() << endl;
	for (auto& x : stud)
		fout << x.second;
	fout.close();
}

void BaseTest::goTest(string login)
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
	cout << setw(65) << " Вы вошли в режиме <Студент> под именем  ";
	SetColor(10, 0);
	cout << stud[login].getFIO() << endl;
	SetColor(15, 0);
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "                                        Тестирование" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	if (stud[login].getKolUnFinished())
	{
		cout << "У вас есть незавершенные тесты:" << endl;
		stud[login].printUnFinished();
		cout << "Желаете завершить?  1 - да 2 - нет" << endl;
		char vibor = getValue12();
		if (vibor == '1')
		{
			cout << "Введите номер теста, который хотите продолжить: " << endl;
			int nom = getValue() - 48;
			if (nom > 0 && nom <= stud[login].getKolUnFinished())
				goOldTest(login, nom);
			else {
				cout << "Неверный номер" << endl;
				system("pause");
			}
		}
		else goNewTest(login);
	}
	else goNewTest(login);
}

void BaseTest::goNewTest(string login)
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "                                        Тестирование" << endl;
	bool uspeh;
	Test test;
	int kolQFinished, kolPrav, balTest;
	t.getTest(test, uspeh);
	if (uspeh)
	{
		if (test.getActive())
		{
			test.go(kolQFinished, kolPrav, balTest);
			int p = round(kolPrav * 100. / test.getKolQ());
			if (kolQFinished == test.getKolQ())
			{
				int m = round(12. * balTest / test.getBal());
				TestFinished tf(test.getName(), test.getCategory(), kolPrav, p, balTest, m);
				stud[login].pushTF(tf);
				cout << "Тестирование закончено. Количество правильных ответов: " << kolPrav << "  Процент правильных ответов: " << p << " Оценка: " << m << endl;
			}
			else {
				TestUnFinished tuf(test.getName(), test.getCategory(), kolPrav, p, balTest, kolQFinished);
				stud[login].pushTUF(tuf);
				cout << "Тестирование прервано. Количество правильных ответов: " << kolPrav << "  Процент правильных ответов: " << p << endl;
				cout << "Вы можете продолжить в любое удобное для вас время" << endl;
			}
			saveUser();
			system("pause");
		}
		else {
			cout << "Данный тест неактивен. Выберите другой тест для прохождения." << endl;
			system("pause");
		}
	}
}

void BaseTest::goOldTest(string login, int nomTUF)
{
	TestUnFinished tuf;
	stud[login].getTUF(nomTUF, tuf);
	string nameTest = tuf.getName();
	string nameCat = tuf.getCategory();
	Test test;
	bool uspeh = false;
	t.getOldTest(nameTest, nameCat, test, uspeh);
	if (uspeh == true && test.getActive())
	{
		int kolFin1 = tuf.getKolQFinished();
		int kolPrav1 = tuf.getKolPrav();
		int b1 = tuf.getBalTest();
		int kolFin2, kolPrav2, b2;
		test.goOld(kolFin1, kolPrav1, b1, kolFin2, kolPrav2, b2);
		int p = round(kolPrav2 * 100. / test.getKolQ());
		if (kolFin2 == test.getKolQ())
		{
			int m = round(12. * b2 / test.getBal());
			TestFinished tf(test.getName(), test.getCategory(), kolPrav2, p, b2, m);
			stud[login].pushTF(tf);
			stud[login].delTUF(nomTUF);
			cout << "Тестирование закончено. Количество правильных ответов: " << kolPrav2 << "  Процент правильных ответов: " << p << " Оценка: " << m << endl;
		}
		else {
			TestUnFinished tuf(test.getName(), test.getCategory(), kolPrav2, p, b2, kolFin2);
			stud[login].delTUF(nomTUF);
			stud[login].pushTUF(tuf);
			cout << "Тестирование прервано. Количество правильных ответов: " << kolPrav2 << "  Процент правильных ответов: " << p << endl;
			cout << "Вы можете продолжить в любое удобное для вас время" << endl;
		}
		saveUser();
		system("pause");
	}
	else {
		cout << "Данный тест не найден в списке активных тестов, возможно он удален или перемещен в архив. Обратитесь к администратору" << endl;
		system("pause");
	}

}

void BaseTest::editStudProfile(string login)
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << setw(65) << " Вы вошли в режиме <Студент> под именем  ";
	SetColor(10, 0);
	cout << stud[login].getFIO() << endl;
	SetColor(15, 0);
	cout << "\n" << setw(55) << "Редактирование профиля" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << endl << "Внимание! Вы можете изменить любые данные, кроме логина. Для изменения логина обратитесь к администратору " << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	stud[login].editProfile();
	saveUser();
	cout << "Изменения сохранены!" << endl;
	system("pause");
}

void BaseTest::editAdminProfile()
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
	cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
	SetColor(10, 0);
	cout << admin.getFIO() << endl;
	SetColor(15, 0);
	cout << "\n" << setw(55) << "Редактирование профиля" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	admin.editProfile();
	cout << " Изменить  логин?  1 - да, 2 - нет" << endl;
	char vibor = getValue12();
	if (vibor == '1')
	{
		cout << "Введите новый логин (любые символы, кроме пробела): ";
		string log;
		cin >> log;
		hash<string>encrypt;
		log = to_string(encrypt(log));
		admin.setLogin(log);
	}
	saveUser();
	cout << "Изменения сохранены!" << endl;
	system("pause");
}

void BaseTest::getStat()
{
	do
	{
		system("cls");
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
		cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
		SetColor(10, 0);
		cout << admin.getFIO() << endl;
		SetColor(15, 0);
		cout << "\n" << setw(55) << "Статистика" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "1. Результаты тестирования всех студентов" << endl;
		cout << "2. Выбрать категорию/тест" << endl;
		cout << "3. Выбрать студента" << endl;
		cout << "0. Выход" << endl;
		char vibor = getValue0123();
		switch (vibor)
		{
		case '1': printStatAll(); break;
		case '2': printStatCatTest(); break;
		case '3': printStatStud(); break;
		case '0': return;
		}
	} while (true);
}

void BaseTest::editStud()
{
	do
	{
		system("cls");
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
		cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
		SetColor(10, 0);
		cout << admin.getFIO() << endl;
		SetColor(15, 0);
		cout << "\n" << setw(55) << "Управление студентами" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "1. Печать на экран" << endl;
		cout << "2. Удалить студента" << endl;
		cout << "3. Добавить студента" << endl;
		cout << "4. Редактировать профиль студента" << endl;
		cout << "0. Выход" << endl;
		char vibor = getValue();
		switch (vibor)
		{
		case '1': printAllStudent(); break;
		case '2': delStud(); break;
		case '3': addStud(); break;
		case '4': editStudProfileAdmin(); break;
		case '0': return;
		default: break;
		}
	} while (true);
}

void BaseTest::printAllStudent()
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
	cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
	SetColor(10, 0);
	cout << admin.getFIO() << endl;
	SetColor(15, 0);
	cout << "\n" << setw(55) << "Список всех студентов" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << " № |    Логин    |                    ФИО                |      E-mail       |    Телефон        |" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	int n = 1;
	for (auto& x : stud)
		cout << setw(3) << n++ << setw(14) << x.first << setw(30) << x.second.getFIO() << setw(25) << x.second.getEmail() << setw(25) << x.second.getTel() << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	system("pause");
}

void BaseTest::delStud()
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
	cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
	SetColor(10, 0);
	cout << admin.getFIO() << endl;
	SetColor(15, 0);
	cout << "\n" << setw(55) << "Удаление студента" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	int n = 1;
	for (auto& x : stud)
		cout << setw(3) << n++ << ". " << x.second.getFIO() << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "Выберите номер студента: ";
	int nomUd;
	cin >> nomUd;
	if (nomUd > 0 && nomUd <= stud.size())
	{
		auto it = stud.begin();
		advance(it, nomUd - 1);
		cout << "Вы уверены, что хотите удалить студента: " << it->second.getFIO() << " ?   1 - да   2 - отмена" << endl;
		char vib = getValue12();
		if (vib == '1')
		{
			stud.erase(it);
			saveUser();
			cout << "Студент удален из базы!" << endl;
		}
		else cout << "Удаление отменено!" << endl;
	}
	else cout << "Неверный номер" << endl;
	system("pause");
}

void BaseTest::addStud()
{
	system("cls");
	cout << "------------------------------------------------------------------" << endl;
	cout << "                       Регистрация нового студента " << endl;
	cout << "------------------------------------------------------------------" << endl;
	Student st;
	string log, log1;
	cin.ignore();
	do {
		cout << "Логин: ";
		getline(cin, log);
		if (!log.length() || isSymbol(log, ' '))
			cout << "Логин должен содержать любые символы, кроме пробела" << endl;
		hash<string> encrypt;
		log1 = to_string(encrypt(log));
		if (stud.count(log1) || admin.getLogin()==log1)
			cout << "Такой логин занят. Выберите другой" << endl;
	} while (isSymbol(log, ' ') || stud.count(log1) || admin.getLogin() == log1);
	st.setLogin(log1);
	cin >> st;
	stud.insert(make_pair(st.getLogin(), st));
	saveUser();
	cout << "Студент добавлен в базу!" << endl;
	system("pause");
}

void BaseTest::editStudProfileAdmin()
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
	cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
	SetColor(10, 0);
	cout << admin.getFIO() << endl;
	SetColor(15, 0);
	cout << "\n" << setw(55) << "Редактирование профиля студента" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	int n = 1;
	for (auto& x : stud)
		cout << setw(3) << n++ << ". " << x.second.getFIO() << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "Выберите номер студента: ";
	int nomUd;
	cin >> nomUd;
	if (nomUd > 0 && nomUd <= stud.size())
	{
		auto it = stud.begin();
		advance(it, nomUd - 1);
		cout << "Редактирование профиля: " << it->second.getFIO() << endl;
		it->second.editProfile();
		saveUser();
		cout << "Изменить логин?  1 - да  2- нет" << endl;
		char viborl = getValue12();
		if (viborl == '1')
		{
			string newlogin;
			do {
				cout << "Введите новый логин: ";				
				cin >> newlogin;
				hash<string>encrypt;
				newlogin = to_string(encrypt(newlogin));
				if (stud.count(newlogin) || admin.getLogin() == newlogin)
					cout << "Такой логин занят." << endl;
			} while (stud.count(newlogin) || admin.getLogin() == newlogin);
			Student st = it->second;
			st.setLogin(newlogin);
			stud.erase(it);
			stud.insert(make_pair(newlogin, st));
			saveUser();
			cout << "Логин изменен!" << endl;
		}
	}
	else cout << "Неверный номер" << endl;
	system("pause");
}

void BaseTest::printStatAll()
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
	cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
	SetColor(10, 0);
	cout << admin.getFIO() << endl;
	SetColor(15, 0);
	cout << "\n" << setw(55) << "Общие результаты тестирования " << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	int kolT = 0;
	for (auto& x : stud)
	{
		kolT = kolT + x.second.getKolFinished() + x.second.getKolUnFinished();
	}
	if (kolT)
	{
		for (auto& x : stud)
		{
			x.second.printTestResultStat(cout);
		}
	}
	else cout << "Ни один студент тестирование не прошел" << endl;
	cout << endl << endl;
	cout << "Сохранить в файл?  1 - да  2- выход" << endl;
	char vibor = getValue12();
	if (vibor == '1')
	{
		cin.ignore();
		string namef;
		do {
			cout << "Введите имя файла: ";
			getline(cin, namef);
			if (namef == "test.txt" || namef == "user.txt")
				cout << "Это зарезервированные имена, выберите другое имя файла" << endl;
		} while (namef == "test.txt" || namef == "user.txt");
		ofstream fout(namef);
		fout << "-------------------------------------------------------------------------------------------------" << endl;
		fout << "                                 Общие результаты тестирования " << endl;
		fout << "-------------------------------------------------------------------------------------------------" << endl;
		for (auto& x : stud)
		{
			x.second.printTestResultStat(fout);
		}
		fout.close();
		cout << "Данные сохранены в указанный файл" << endl;
		system("pause");
	}
}

void BaseTest::printStatCatTest()
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
	cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
	SetColor(10, 0);
	cout << admin.getFIO() << endl;
	SetColor(15, 0);
	cout << "\n" << setw(55) << "Результаты тестирования по категориям" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	int kolT = 0;
	for (auto& x : stud)
	{
		kolT = kolT + x.second.getKolFinished() + x.second.getKolUnFinished();
	}
	if (kolT)
	{
		t.printCategoryWithoutArc();
		cout << "Выберите номер категории:" << endl;
		int nomCat = getValue() - 48;
		if (nomCat > 0 && nomCat <= t.getSize())
		{
			string nameCat = t.getNameCatStat(nomCat);
			if (t.getKolTestCat(nameCat))
			{
				cout << "Категория " << nameCat << " содержит тесты: " << endl;
				t.printNameTestStat(nameCat);
				if (t.getKolTestCat(nameCat) == 1)
				{
					string nameTest = t.getNameTest(nameCat, 0);
					system("cls");
					printStat(cout, nameCat, nameTest);
					cout << endl << endl;
					cout << "Сохранить в файл?  1 - да  2- выход" << endl;
					char vibor = getValue12();
					if (vibor == '1')
					{
						string namef;
						do {
							cout << "Введите имя файла: ";
							cin.ignore();
							getline(cin, namef);
							if (namef == "test.txt" || namef == "user.txt")
								cout << "Это зарезервированное имя, выберите другое имя файла" << endl;
						} while (namef == "test.txt" || namef == "user.txt");
						ofstream fout(namef);
						printStat(fout, nameCat, nameTest);
						fout.close();
						cout << "Данные сохранены в указанный файл" << endl;
					}
				}
				else {
					cout << "1 - статистика по всей категории, 2 - выбрать тест" << endl;
					char vibor = getValue12();
					if (vibor == '1')
					{
						for (int i=0; i<t.getKolTestCat(nameCat);i++)
							printStat(cout, nameCat, t.getNameTest(nameCat,i));
						cout << endl << endl;
						cout << "Сохранить в файл?  1 - да  2- выход" << endl;
						char vibor = getValue12();
						if (vibor == '1')
						{
							string namef;
							do {
								cout << "Введите имя файла: ";
								getline(cin, namef);
								if (namef == "test.txt" || namef == "user.txt")
									cout << "Это зарезервированное имя, выберите другое имя файла" << endl;
							} while (namef == "test.txt" || namef == "user.txt");
							ofstream fout(namef);
							for (int i = 0; i < t.getKolTestCat(nameCat); i++)
								printStat(fout, nameCat, t.getNameTest(nameCat, i));
							fout.close();
							cout << "Данные сохранены в указанный файл" << endl;
						}
					}
					else {
						cout << "Выберите номер теста" << endl;
						int nomTest = getValue() - 48;
						if (nomTest > 0 && nomTest <= t.getKolTestCat(nameCat))
						{
							string nameTest = t.getNameTest(nameCat, nomTest - 1);
							printStat(cout, nameCat, nameTest);
							cout << endl << endl;
							cout << "Сохранить в файл?  1 - да  2- выход" << endl;
							char vibor = getValue12();
							if (vibor == '1')
							{
								string namef;
								do {
									cout << "Введите имя файла: ";
									getline(cin, namef);
									if (namef == "test.txt" || namef == "user.txt")
										cout << "Это зарезервированное имя, выберите другое имя файла" << endl;
								} while (namef == "test.txt" || namef == "user.txt");
								ofstream fout(namef);
								printStat(fout, nameCat, nameTest);
								fout.close();
								cout << "Данные сохранены в указанный файл" << endl;
							}
						}
						else cout << "Неверный номер теста" << endl;
					}
				}
			}
			else cout << "Данная категория не содержит ни одного теста" << endl;
		}
		else cout << "Неверный номер категории" << endl;
	}
	else cout << "Ни один студент тестирование не прошел" << endl;
	system("pause");
}

void BaseTest::printStatStud()
{
	system("cls");
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "\n" << setw(55) << "Добро пожаловать в систему TEST!" << endl;
	cout << setw(65) << " Вы вошли в режиме <Администратор> под именем  ";
	SetColor(10, 0);
	cout << admin.getFIO() << endl;
	SetColor(15, 0);
	cout << "\n" << setw(55) << "Результаты тестирования студента" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	int n = 1;
	for (auto& x : stud)
		cout << setw(3) << n++ << ". " << x.second.getFIO() << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "Выберите номер студента: ";
	int nomSt;
	cin >> nomSt;
	cin.ignore();
	if (nomSt > 0 && nomSt <= stud.size())
	{
		auto it = stud.begin();
		advance(it, nomSt - 1);
		it->second.printTestResult(cout);	
	    cout << endl << endl;
	    cout << "Сохранить в файл?  1 - да  2- выход" << endl;
	    char vibor = getValue12();
	    if (vibor == '1')
	    {		  
			string namef;
			do {
			  cout << "Введите имя файла: ";			
			  getline(cin, namef);
			  if (namef == "test.txt" || namef == "user.txt")
				  cout << "Это зарезервированные имена, выберите другое имя файла" << endl;
			} while (namef == "test.txt" || namef == "user.txt");
		  ofstream fout(namef);		
		  it->second.printTestResult(fout);
		  fout.close();
		  cout << "Данные сохранены в указанный файл" << endl;
		  system("pause");
		}	
	}
	else {
		cout << "Неверный номер" << endl;
		system("pause");
	}
}

void BaseTest::printStat(ostream& out, string nameCat, string nameTest)
{
	
	out << "-------------------------------------------------------------------------------------------------" << endl;
	out <<"       Результаты тестирования: тест "<<nameTest<<" из категории:" <<nameCat << endl;
	out << "-------------------------------------------------------------------------------------------------" << endl;
	for (auto& x : stud)
	{
		if (x.second.getKolFinished())
		{
			x.second.printStatTF(out, nameCat, nameTest);
			out << endl;
		}
	};
	out << "-------------------------------------------------------------------------------------------------" << endl;
	out << "                                      Незавершенные тесты  :" << endl;
	out << "-------------------------------------------------------------------------------------------------" << endl;
	for (auto& x : stud)
	{
		if (x.second.getKolUnFinished())
		{
			x.second.printStatTUF(out, nameCat, nameTest);
			out << endl;
		}
	};
	out << "-------------------------------------------------------------------------------------------------" << endl;

}





