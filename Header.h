#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <filesystem>
#include <Windows.h>
#include <codecvt>
#include <ctype.h>
#include <stdio.h>
using namespace std;

wstring readTextFromFile(const wstring& filename);

bool writeTextToFile(const string& filename, const wstring& text);

bool isPrime(int n);

int gcd(int a, int b);

int modInverse(int a, int m);

void generateRSAKeys(int& publicKey, int& privateKey, int& n);

wstring rsaEncrypt(const wstring& plaintext, int publicKey, int n);

wstring rsaDecrypt(const wstring& ciphertext, int privateKey, int n);

wstring vigenereEncrypt(const wstring& text, const wstring& key, bool encrypt);

wstring gronsfeldEncrypt(const wstring& plaintext, const wstring& key, bool encrypt);

bool checkPassword(wstring password);

void getPassword();

void handleVigenereCipher(const wstring& inputTextFile, const wstring& keyFile, bool encrypt);

void handleGronsfeldCipher(const wstring& inputTextFile, const wstring& keyFile, bool encrypt);

void handleRSADecryptCipher(const wstring& inputTextFile, const wstring& privateKeyFilePath, const wstring& nFilePath);

void handleRSAEncryptCipher(const wstring& inputTextFile);

bool getEncryption();

void listen();

wstring getPath(wstring header);
