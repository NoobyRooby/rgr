#include "Header.h"

int main() {
	try {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "rus");
		getPassword();
		system("PAUSE");
		system("CLS");
		listen();//вывод меню 
	}
	catch (exception e) {
		cout << "Произошла ошибка: " << e.what();
	}
	return 0;
}