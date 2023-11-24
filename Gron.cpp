#include "Header.h"

void handleGronsfeldCipher(const wstring& inputTextFile, const wstring& keyFile, bool encrypt) {
	wstring plaintext = readTextFromFile(inputTextFile);
	wstring key = readTextFromFile(keyFile);
	wstring resultText = gronsfeldEncrypt(plaintext, key, encrypt);

	writeTextToFile("result.txt", resultText);

	wcout << L"�������� ������� ���������." << endl;
	system("PAUSE");
	system("CLS");
}

wstring gronsfeldEncrypt(const wstring& plaintext, const wstring& key, bool encrypt) {

	wstring ciphertext;// ������� ���������� ��� �������� ��������������/��������������� ������
	size_t keyLength = key.length();// �������� ����� �����

	for (size_t i = 0; i < plaintext.length(); i++) {
		// �������� ������� ������ � ������ ����� ��� ������� �������
		wchar_t plainChar = plaintext[i];
		wchar_t keyChar = key[i % keyLength];
		wchar_t encryptedChar = encrypt ? (plainChar + keyChar) : (plainChar - keyChar);// ��������� �������������/�������������� ������ � ������������ � ����� ��������
		ciphertext += encryptedChar;// ��������� �������������/�������������� ������ � ���������� ��� �������� ��������������/��������������� ������
	}

	return ciphertext;// ���������� �������������/�������������� �����
}