#include "Header.h"

bool checkPassword(wstring pass) {  //проверка пароля на правильность
	wstring actual_password = readTextFromFile(L"password.txt");
	if (pass == actual_password)
		return true;
	else
		return false;
}

void getPassword() { //запрос пароля
	wstring password;
	cout << "Введите пароль: ";
	getline(wcin, password);
	if (checkPassword(password) == false) {
		cout << "Неверный пароль! Попробуйте еще раз." << endl;
		getPassword();
	}
	else cout << "Пароль введен верно!" << endl;
}

wstring getPath(wstring header) {//запрос пути к файлу
	wstring inputTextFile;
	wcout << header;
	wcin >> inputTextFile;
	return inputTextFile;
}

bool getEncryption() { //выбор операции
	string operation;
	cout << "Выберите операцию:" << endl << "1 - Зашифровать"<<endl<<"2 - Расшифровать"<<endl<<"После преобразования ваш текст будет сохранен в файл 'result.txt'." << endl;
	cin >> operation;
	if (operation != "1" && operation!= "2") {
		cerr << "Некорректное значение." << endl;
		system("PAUSE");
		system("CLS");
		listen();
	}
	else
	return (operation == "1");
}

void listen() {

	while (true) {
		string choice;
		cout << "Выберите шифр:" << endl << "1 - Вижинер" << endl << "2 - Гронсфельд" << endl << "3 - RSA" << endl << "4 - выход" << endl;
		cin >> choice;

		if (choice == "1") {
			bool encrypt = getEncryption();

			wstring inputTextFile = getPath(L"Введите путь к файлу с текстом: ");
			wstring keyFile = getPath(L"Введите путь к файлу с ключом: ");

			handleVigenereCipher(inputTextFile, keyFile, encrypt);
		}
		else if (choice == "2") {
			bool encrypt = getEncryption();

			wstring inputTextFile = getPath(L"Введите путь к файлу с текстом: ");
			wstring keyFile = getPath(L"Введите путь к файлу с ключом: ");

			handleGronsfeldCipher(inputTextFile, keyFile, encrypt);
		}
		else if (choice == "3") {
			bool encrypt = getEncryption();

			wstring inputTextFile = getPath(L"Введите путь к файлу с текстом: ");

			if (encrypt) {
				handleRSAEncryptCipher(inputTextFile);
			}
			else {
				wstring privateKeyFile = getPath(L"Введите путь к файлу с приватным ключом: ");

				wstring nFile = getPath(L"Введите путь к файлу с модулем: ");

				handleRSADecryptCipher(inputTextFile, privateKeyFile, nFile);
			}
		}
		else if (choice == "4") {
			return;
		}
		else {
			cerr << "Некорректное значение." << endl;
			system("PAUSE");
			system("CLS");
			listen();
			
		}
	}
}

bool isPrime(int n) { //проверка на простоту
	if (n <= 1)
		return false;
	if (n <= 3)
		return true;

	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			return false;

	return true;
}

int gcd(int a, int b) { //нод
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int modInverse(int a, int m) {  //обратное значение a по модулю m
	for (int x = 1; x < m; x++) {
		if ((a * x) % m == 1)
			return x;
	}
	return -1;
}

wstring readTextFromFile(const wstring& filename) {  //считывание текста из файла
	wifstream file(filename);

	if (!file.is_open()) {
		throw exception("Error opening file");
	}
	file.imbue(locale(file.getloc(), new codecvt_utf8_utf16<wchar_t>)); //функция устанавливает локаль в потоке файла, чтобы корректно обрабатывать символы в кодировке UTF-8
	wstring content((istreambuf_iterator<wchar_t>(file)), istreambuf_iterator<wchar_t>());

	file.close();
	return content;
}

bool writeTextToFile(const string& filename, const wstring& text) {  //запись текста в файл
	wofstream file(filename);
	if (!file.is_open()) {
		throw exception("Error opening file");
	}

	file.imbue(locale(file.getloc(), new codecvt_utf8_utf16<wchar_t>));
	file << text;//функция записывает содержимое строки text в файл с помощью оператора <<
	file.close();
	return true;
}
