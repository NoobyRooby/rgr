#include "Header.h"

bool checkPassword(wstring pass) {  //�������� ������ �� ������������
	wstring actual_password = readTextFromFile(L"password.txt");
	if (pass == actual_password)
		return true;
	else
		return false;
}

void getPassword() { //������ ������
	wstring password;
	cout << "������� ������: ";
	getline(wcin, password);
	if (checkPassword(password) == false) {
		cout << "�������� ������! ���������� ��� ���." << endl;
		getPassword();
	}
	else cout << "������ ������ �����!" << endl;
}

wstring getPath(wstring header) {//������ ���� � �����
	wstring inputTextFile;
	wcout << header;
	wcin >> inputTextFile;
	return inputTextFile;
}

bool getEncryption() { //����� ��������
	string operation;
	cout << "�������� ��������:" << endl << "1 - �����������"<<endl<<"2 - ������������"<<endl<<"����� �������������� ��� ����� ����� �������� � ���� 'result.txt'." << endl;
	cin >> operation;
	if (operation != "1" && operation!= "2") {
		cerr << "������������ ��������." << endl;
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
		cout << "�������� ����:" << endl << "1 - �������" << endl << "2 - ����������" << endl << "3 - RSA" << endl << "4 - �����" << endl;
		cin >> choice;

		if (choice == "1") {
			bool encrypt = getEncryption();

			wstring inputTextFile = getPath(L"������� ���� � ����� � �������: ");
			wstring keyFile = getPath(L"������� ���� � ����� � ������: ");

			handleVigenereCipher(inputTextFile, keyFile, encrypt);
		}
		else if (choice == "2") {
			bool encrypt = getEncryption();

			wstring inputTextFile = getPath(L"������� ���� � ����� � �������: ");
			wstring keyFile = getPath(L"������� ���� � ����� � ������: ");

			handleGronsfeldCipher(inputTextFile, keyFile, encrypt);
		}
		else if (choice == "3") {
			bool encrypt = getEncryption();

			wstring inputTextFile = getPath(L"������� ���� � ����� � �������: ");

			if (encrypt) {
				handleRSAEncryptCipher(inputTextFile);
			}
			else {
				wstring privateKeyFile = getPath(L"������� ���� � ����� � ��������� ������: ");

				wstring nFile = getPath(L"������� ���� � ����� � �������: ");

				handleRSADecryptCipher(inputTextFile, privateKeyFile, nFile);
			}
		}
		else if (choice == "4") {
			return;
		}
		else {
			cerr << "������������ ��������." << endl;
			system("PAUSE");
			system("CLS");
			listen();
			
		}
	}
}

bool isPrime(int n) { //�������� �� ��������
	if (n <= 1)
		return false;
	if (n <= 3)
		return true;

	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			return false;

	return true;
}

int gcd(int a, int b) { //���
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int modInverse(int a, int m) {  //�������� �������� a �� ������ m
	for (int x = 1; x < m; x++) {
		if ((a * x) % m == 1)
			return x;
	}
	return -1;
}

wstring readTextFromFile(const wstring& filename) {  //���������� ������ �� �����
	wifstream file(filename);

	if (!file.is_open()) {
		throw exception("Error opening file");
	}
	file.imbue(locale(file.getloc(), new codecvt_utf8_utf16<wchar_t>)); //������� ������������� ������ � ������ �����, ����� ��������� ������������ ������� � ��������� UTF-8
	wstring content((istreambuf_iterator<wchar_t>(file)), istreambuf_iterator<wchar_t>());

	file.close();
	return content;
}

bool writeTextToFile(const string& filename, const wstring& text) {  //������ ������ � ����
	wofstream file(filename);
	if (!file.is_open()) {
		throw exception("Error opening file");
	}

	file.imbue(locale(file.getloc(), new codecvt_utf8_utf16<wchar_t>));
	file << text;//������� ���������� ���������� ������ text � ���� � ������� ��������� <<
	file.close();
	return true;
}
