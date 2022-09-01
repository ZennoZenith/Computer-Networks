#include <iostream>
#include <string.h>

using namespace std;

class Message
{
  string plainText;
  string encryptedText;
  string ignoreChar;
  int key;
  const string SMALL = "abcdefghijklmnopqrstuvwxyz";
  const string CAPITAL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int sanitiseText(string *);

public:
  Message();
  int setPlainText(string);
  int setEncryptedText(string);
  void setKey(int);
  void setIgnoreChar(string);
  string getPlainText();
  string getEncryptedText();
  string encrypt();
  string decrypt();
};

Message::Message()
{
  plainText = "HelloWorld";
  encryptedText = "KhoorZruog";
  ignoreChar = "";
  key = 3;
  sanitiseText(&this->plainText);
}

void Message::setKey(int key)
{
  this->key = key;
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
  int len = SMALL.length();
  int len2 = ignoreChar.length();
  int plainTextLen = plainText.length();
  int i, k;

  encryptedText.resize(plainTextLen);
  for (i = 0; i < plainTextLen; i++)
  {
    for (k = 0; k < len2; k++)
    {
      if (plainText[i] == ignoreChar[k])
      {
        encryptedText[i] = plainText[i];
        break;
      }
    }
    for (k = 0; k < len; k++)
    {
      int index = k + key;
      while (index >= len)
        index -= len;
      while (index < 0)
        index += len;
      if (plainText[i] == SMALL[k])
        encryptedText[i] = SMALL[index];
      else if (plainText[i] == CAPITAL[k])
        encryptedText[i] = CAPITAL[index];
    }
  }
  encryptedText[i] = '\0';
  return encryptedText;
}

string Message::decrypt()
{
  int len = SMALL.length();
  int len2 = ignoreChar.length();
  int encryptedTextLen = encryptedText.length();
  int i, k;

  plainText.resize(encryptedTextLen);
  for (i = 0; i < encryptedTextLen; i++)
  {
    for (k = 0; k < len2; k++)
    {
      if (encryptedText[i] == ignoreChar[k])
      {
        plainText[i] = encryptedText[i];
        break;
      }
    }
    for (k = 0; k < len; k++)
    {
      int index = k - key;
      while (index >= len)
        index -= len;
      while (index < 0)
        index += len;

      if (encryptedText[i] == SMALL[k])
        plainText[i] = SMALL[index];
      else if (encryptedText[i] == CAPITAL[k])
        plainText[i] = CAPITAL[index];
    }
  }
  plainText[i] = '\0';
  return plainText;
}

int main()
{
  Message m;
  int choice, key;
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