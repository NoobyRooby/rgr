#include "Header.h"

void handleVigenereCipher(const wstring& inputTextFile, const wstring& keyFile, bool encrypt) {
	wstring plaintext = readTextFromFile(inputTextFile);
	wstring key = readTextFromFile(keyFile);
	wstring resultText = vigenereEncrypt(plaintext, key, encrypt);

	writeTextToFile("result.txt", resultText);

	wcout << L"Операция успешно выполнена." << endl;
	system("PAUSE");
	system("CLS");
}

wstring vigenereEncrypt(const wstring& text, const wstring& key, bool encrypt) {
	wstring transformedText;// Создаем переменную для хранения преобразованного текста

	for (size_t i = 0; i < text.length(); ++i) {
		// Получаем текущий символ и символ ключа для текущей позиции
		wchar_t currentChar = text[i];
		wchar_t keyChar = key[i % key.length()];
		// Вычисляем сдвиг по ключу
		int shift = static_cast<int>(keyChar);
		// Преобразуем текущий символ в соответствии с типом операции
		wchar_t transformedChar = currentChar;

		if (encrypt) {
			transformedChar += shift;
		}
		else {
			transformedChar -= shift;
		}
		// Добавляем преобразованный символ в переменную для хранения преобразованного текста
		transformedText += transformedChar;
	}

	return transformedText;// Возвращаем преобразованный текст
}