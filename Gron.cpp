#include "Header.h"

void handleGronsfeldCipher(const wstring& inputTextFile, const wstring& keyFile, bool encrypt) {
	wstring plaintext = readTextFromFile(inputTextFile);
	wstring key = readTextFromFile(keyFile);
	wstring resultText = gronsfeldEncrypt(plaintext, key, encrypt);

	writeTextToFile("result.txt", resultText);

	wcout << L"Операция успешно выполнена." << endl;
	system("PAUSE");
	system("CLS");
}

wstring gronsfeldEncrypt(const wstring& plaintext, const wstring& key, bool encrypt) {

	wstring ciphertext;// Создаем переменную для хранения зашифрованного/расшифрованного текста
	size_t keyLength = key.length();// Получаем длину ключа

	for (size_t i = 0; i < plaintext.length(); i++) {
		// Получаем текущий символ и символ ключа для текущей позиции
		wchar_t plainChar = plaintext[i];
		wchar_t keyChar = key[i % keyLength];
		wchar_t encryptedChar = encrypt ? (plainChar + keyChar) : (plainChar - keyChar);// Вычисляем зашифрованный/расшифрованный символ в соответствии с типом операции
		ciphertext += encryptedChar;// Добавляем зашифрованный/расшифрованный символ в переменную для хранения зашифрованного/расшифрованного текста
	}

	return ciphertext;// Возвращаем зашифрованный/расшифрованный текст
}