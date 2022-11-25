#include <iostream>
#include <math.h>
#include <string.h>

#include "cryptography.h"
// #define MATRIX_LEN 100
// #define RAND_CHAR 'M'
using namespace std;
class Message
{
  string plainText;
  string encryptedText;
  string ignoreChar;
  string keyText;
  int plainTextlen;
  const string SMALL = "abcdefghijklmnopqrstuvwxyz";
  const string CAPITAL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int sanitiseText(string *);

public:
  Message();
  int setPlainText(string);
  int setEncryptedText(string);
  void setKeyText(string);
  void setPlainTextLen(int);
  void setIgnoreChar(string);
  string getKeyText();
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
  keyText = "THISISKEY";
  plainTextlen = 10;
  sanitiseText(&this->plainText);
}

void Message::setKeyText(string keyText)
{
  // keyText.swap(keyText);
  string tempKeyText;
  tempKeyText.resize(26);
  int j = 0, k = 0;
  int keyLen = keyText.length();
  for (int i = 0; i < keyLen; i++)
  {
    keyText[i] = Helper::ToLowerChar(keyText[i]);
    if (keyText[i] == 'j')
    {
      keyText[i] = 'i';
    }

    for (k = 0; k < j; k++)
    {
      if (tempKeyText[k] == keyText[i])
        break;
    }
    if (j == k)
    {
      tempKeyText[j] = keyText[i];
      j++;
    }
  }
  tempKeyText[j] = '\0';
  tempKeyText[25] = '\0';
  tempKeyText.resize(26);
  this->keyText.swap(tempKeyText);
}

string Message::getKeyText()
{
  return keyText;
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
  int i, j, k = 0;
  plainTextlen = plainText.length();
  encryptedText.resize(plainTextlen);

  int keyLen = keyText.length();
  for (i = 0; i < plainTextlen; i++)
  {
    char temp = Helper::ToUpperChar(plainText[i]);
    encryptedText[i] = 'A' + (temp - 'A' + keyText[i % keyLen] - 'A') % 26;
  }
  return encryptedText;
}

string Message::decrypt()
{
  int i, j, k = 0;
  int encryptedTextLen = encryptedText.length();
  plainText.resize(encryptedTextLen);

  int keyLen = keyText.length();
  for (i = 0; i < encryptedTextLen; i++)
  {
    char temp = Helper::ToUpperChar(encryptedText[i]);
    plainText[i] = 'A' + (temp - 'A' - (keyText[i % keyLen] - 'A') + 26) % 26;
    cout << encryptedText[i] << " : " << plainText[i] << " " << (temp - 'A' - (keyText[i % keyLen] - 'A') + 26) << endl;
  }
  return plainText;
}

int main()
{
  Message m;
  int choice, len;
  string keyText;
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
      getline(cin, keyText, '\n');
      m.setKeyText(keyText);

      cout << "key text : " << m.getKeyText() << endl;
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
      getline(cin, keyText, '\n');
      m.setKeyText(keyText);
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