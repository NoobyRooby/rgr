#include "Header.h"

void handleVigenereCipher(const wstring& inputTextFile, const wstring& keyFile, bool encrypt) {
	wstring plaintext = readTextFromFile(inputTextFile);
	wstring key = readTextFromFile(keyFile);
	wstring resultText = vigenereEncrypt(plaintext, key, encrypt);

	writeTextToFile("result.txt", resultText);

	wcout << L"�������� ������� ���������." << endl;
	system("PAUSE");
	system("CLS");
}

wstring vigenereEncrypt(const wstring& text, const wstring& key, bool encrypt) {
	wstring transformedText;// ������� ���������� ��� �������� ���������������� ������

	for (size_t i = 0; i < text.length(); ++i) {
		// �������� ������� ������ � ������ ����� ��� ������� �������
		wchar_t currentChar = text[i];
		wchar_t keyChar = key[i % key.length()];
		// ��������� ����� �� �����
		int shift = static_cast<int>(keyChar);
		// ����������� ������� ������ � ������������ � ����� ��������
		wchar_t transformedChar = currentChar;

		if (encrypt) {
			transformedChar += shift;
		}
		else {
			transformedChar -= shift;
		}
		// ��������� ��������������� ������ � ���������� ��� �������� ���������������� ������
		transformedText += transformedChar;
	}

	return transformedText;// ���������� ��������������� �����
}