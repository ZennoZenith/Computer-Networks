#include <iostream>
#include <math.h>
#include <string.h>
#define MATRIX_LEN 100
#define RAND_CHAR 'M'
using namespace std;

class Message
{
	string plainText;
	string encryptedText;
	string ignoreChar;
	char matrix[MATRIX_LEN][MATRIX_LEN];
	int key;
	int plainTextlen;
	const string SMALL = "abcdefghijklmnopqrstuvwxyz";
	const string CAPITAL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int sanitiseText(string *);
	void showMatrix(int, int);

public:
	Message();
	int setPlainText(string);
	int setEncryptedText(string);
	void setKey(int);
	void setPlainTextLen(int);
	void setIgnoreChar(string);
	string getPlainText();
	string getEncryptedText();
	string encrypt();
	string decrypt();
};

Message::Message()
{
	plainText = "HelloWorld";
	encryptedText = "HlodeorMlWlM";
	ignoreChar = "";
	key = 3;
	plainTextlen = 10;
	sanitiseText(&this->plainText);
}

void Message::showMatrix(int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j];
		}
		cout << endl;
	}
}

void Message::setKey(int key)
{
	this->key = key;
}

void Message::setPlainTextLen(int plainTextlen)
{
	this->plainTextlen = plainTextlen;
}

void Message::setIgnoreChar(string text)
{
	ignoreChar.swap(text);
}

int Message::setPlainText(string plainText)
{
	this->plainText.swap(plainText);
	return sanitiseText(&this->plainText);
}

string Message::getPlainText()
{
	return plainText;
}

int Message::setEncryptedText(string encryptedText)
{
	this->encryptedText.swap(encryptedText);
	return sanitiseText(&this->encryptedText);
}

string Message::getEncryptedText()
{
	return encryptedText;
}

int Message::sanitiseText(string *text)
{
	int i = 0, j = 0, k = 0, len = 0, len2 = 0, flag = 0;
	len = SMALL.length();
	len2 = ignoreChar.length();
	while ((*text)[i] != '\0')
	{
		for (k = 0; k < len2; k++)
		{
			if ((*text)[i] == ignoreChar[k])
				break;
		}
		if (k != len2)
		{
			(*text)[j] = (*text)[i];
			j++;
			i++;
			continue;
		}

		for (k = 0; k < len; k++)
		{
			if ((*text)[i] == SMALL[k])
				break;
			else if ((*text)[i] == CAPITAL[k])
				break;
		}
		if (k != len)
		{
			(*text)[j] = (*text)[i];
			j++;
		}
		else
			flag = 1;
		i++;
	}
	(*text)[j] = '\0';
	(*text).resize(j);
	return flag;
}

string Message::encrypt()
{
	int i, j, k = 0, len;
	len = plainText.length();
	plainTextlen = len;
	int numberOfRows = ceil((float)len / key);
	encryptedText.resize(numberOfRows * key);

	for (i = 0; i < numberOfRows; i++)
	{
		for (j = 0; j < key; j++)
		{
			if (k < len)
				matrix[i][j] = plainText[k];
			else
				matrix[i][j] = RAND_CHAR;
			k++;
		}
	}
	showMatrix(numberOfRows, key);

	k = 0;
	for (j = 0; j < key; j++)
	{
		for (i = 0; i < numberOfRows; i++)
		{
			encryptedText[k] = matrix[i][j];
			k++;
		}
	}
	encryptedText[k] = '\0';
	return encryptedText;
}

string Message::decrypt()
{
	int i, j, k = 0;
	int len = encryptedText.length();
	int numberOfRows = ceil((float)len / key);
	plainText.resize(plainTextlen);

	for (j = 0; j < key; j++)
	{
		for (i = 0; i < numberOfRows; i++)
		{
			if (encryptedText[k] != '\0')
				matrix[i][j] = encryptedText[k];
			else
				matrix[i][j] = RAND_CHAR;
			k++;
		}
	}
	showMatrix(numberOfRows, key);

	k = 0;
	for (i = 0; i < numberOfRows; i++)
	{
		for (j = 0; j < key; j++)
		{
			plainText[k] = matrix[i][j];
			k++;
			if (k == plainTextlen)
				break;
		}
	}
	plainText[k] = '\0';
	return plainText;
}

int main()
{
	Message m;
	int choice, key, len;
	char flag;
	string text;
	do
	{
		cout << "1. Encrypt.\n";
		cout << "2. Decrypt.\n";
		cout << "3. Set ignore character list.\n";
		cout << "4. Exit.\n";
		cout << "Enter your choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter plain text : ";
			cin.ignore();
			getline(cin, text, '\n');
			flag = m.setPlainText(text);
			if (flag == 1)
				cout << "String contains special character(s).\n";
			cout << "Enter key : ";
			cin >> key;
			m.setKey(key);

			cout << "Encrypted text : " << m.encrypt() << endl;
			cout << "Do you want to decrypt (y/n) : ";
			cin >> flag;
			if (flag == 'y' || flag == 'Y')
				cout << "Plain text : " << m.decrypt() << endl;
			break;
		case 2:
			cout << "Enter encrypted text : ";
			cin.ignore();
			getline(cin, text, '\n');
			flag = m.setEncryptedText(text);
			if (flag == 1)
				cout << "String contains special character(s).\n";
			cout << "Enter key : ";
			cin >> key;
			cout << "Enter string len : ";
			cin >> len;
			m.setPlainTextLen(len);
			cout << "Plain text : " << m.decrypt() << endl;
			break;
		case 3:
			cout << "Enter ignore character list : ";
			cin.ignore();
			getline(cin, text, '\n');
			m.setIgnoreChar(text);
			break;
		case 4:
			cout << "Exiting...";
			getchar();
			getchar();
			break;
		default:
			cout << "Wrong choice try again.." << endl;
			break;
		}
	} while (choice != 4);

	return 0;
}