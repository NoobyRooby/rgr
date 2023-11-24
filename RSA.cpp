#include "Header.h"

void generateRSAKeys(int& publicKey, int& privateKey, int& n) { //��������� ������ RSA
	// ���������� ��������� ������� ����� p � q
	int p, q;

	do {
		p = rand() % 100 + 1;
	} while (!isPrime(p));

	do {
		q = rand() % 100 + 1;
	} while (!isPrime(q));

	n = p * q;
	int phi = (p - 1) * (q - 1);// ��������� �������� ������� ������ �� n
	// ���������� �������� ����
	do {
		publicKey = rand() % (phi - 1) + 2;
	} while (gcd(publicKey, phi) != 1);

	privateKey = modInverse(publicKey, phi);// ��������� �������� ����
}

void handleRSAEncryptCipher(const wstring& inputTextFile) {
	wifstream inputFile(inputTextFile);
	wofstream publicKeyFile("public_key.txt");
	wofstream privateKeyFile("private_key.txt");
	wofstream nFile("n.txt");

	if (!inputFile || !publicKeyFile || !privateKeyFile || !nFile) {
		cerr << "������ ��� �������� ������." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}

	int publicKey, privateKey, n;
	generateRSAKeys(publicKey, privateKey, n);

	publicKeyFile << publicKey;
	privateKeyFile << privateKey;
	nFile << n;

	wstring plaintext = readTextFromFile(inputTextFile);
	wstring resultText = rsaEncrypt(plaintext, publicKey, n);

	writeTextToFile("result.txt", resultText);
	wcout << L"�������� ������� ���������." << endl;
	system("PAUSE");
	system("CLS");
}

void handleRSADecryptCipher(const wstring& inputTextFile, const wstring& privateKeyFilePath, const wstring& nFilePath) {
	wifstream inputFile(inputTextFile);
	wifstream privateKeyFile(privateKeyFilePath);
	wifstream nFile(nFilePath);

	if (!inputFile || !privateKeyFile || !nFile) {
		cerr << "������ ��� �������� ������." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}

	int privateKey, n;

	if (!(privateKeyFile >> privateKey) || !(nFile >> n)) {
		cerr << "������ ��� ���������� ������." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}

	if (privateKey <= 0 || n <= 0) {
		cerr << "������������ �������� ������." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}

	wstring plaintext = readTextFromFile(inputTextFile);
	wstring resultText = rsaDecrypt(plaintext, privateKey, n);

	if (resultText.empty()) {
		cerr << "�������������� ����� ����." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}

	writeTextToFile("result.txt", resultText);
	wcout << L"�������� ������� ���������." << endl;
	system("PAUSE");
	system("CLS");
}

wstring rsaEncrypt(const wstring& plaintext, int publicKey, int n) {
	wstring ciphertext;

	for (wchar_t ch : plaintext) {
		int num = static_cast<int>(ch);//����������� ������� ������ ch � ����� num

		long long encryptedNum = 1;
		for (int i = 0; i < publicKey; i++) {//��������� ������������� ����� encryptedNum ��� num � ������� publicKey �� ������ n
			encryptedNum = (encryptedNum * num) % n;
		}

		ciphertext += to_wstring(encryptedNum) + L" ";//����������� ������������� ����� � ������ � ��������� ��� � �������������� ������
	}

	return ciphertext;
}

wstring rsaDecrypt(const wstring& ciphertext, int privateKey, int n) {
	wstring plaintext;
	wstring numStr;

	for (wchar_t ch : ciphertext) {
		if (ch == L' ') {//���� ������� ������ ch �������� ��������, �� ������� ������ numStr �������� ������������� �����
			int encryptedNum = stoi(numStr);
			long long decryptedNum = 1;

			for (int i = 0; i < privateKey; i++) {//��������� �������������� ����� decryptedNum ��� encryptedNum � ������� privateKey �� ������ n
				decryptedNum = (decryptedNum * encryptedNum) % n;
			}

			wchar_t numChar = static_cast<wchar_t>(decryptedNum);//����������� �������������� ����� � ������ � ��������� ��� � �������������� ������ plaintext
			plaintext += numChar;
			numStr = L"";
		}
		else {
			numStr += ch;//������� ������
		}
	}

	return plaintext;
}