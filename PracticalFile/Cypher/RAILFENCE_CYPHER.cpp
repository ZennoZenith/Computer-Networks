#include <iostream>
#include "cryptography.h"

using namespace std;

int main()
{
  string plainText;
  string encryptedText;
  string ignoreCharacter = "";
  int key;
  int choice = 1;
  char flag;
  do
  {
    cout << "1. Encrypt.\n";
    cout << "2. Decrypt.\n";
    cout << "3. Set ignore character list.\n";
    cout << "4. Exit.\n";
    cout << "Enter your choice : ";
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1:
      cout << "Enter plain text : ";
      getline(cin, plainText, '\n');
      flag = Helper::sanitiseText(plainText);
      if (flag == 1)
        cout << "String contains special character(s).\n";
      cout << "Enter key : ";
      cin >> key;
      cin.ignore();
      encryptedText = RailFenceCypher::encrypt(plainText, key, ignoreCharacter);
      cout << "Encrypted text : " << encryptedText << endl;
      cout << "Do you want to decrypt (y/n) : ";
      cin >> flag;
      if (flag == 'y' || flag == 'Y')
        cout << "Plain text : " << RailFenceCypher::decrypt(encryptedText, key, ignoreCharacter) << "\n\n";
      break;
    case 2:
      cout << "Enter encrypted text : ";
      getline(cin, encryptedText, '\n');
      flag = Helper::sanitiseText(encryptedText);
      if (flag == 1)
        cout << "String contains special character(s).\n";
      cout << "Enter key : ";
      cin >> key;
      cin.ignore();

      cout << "Plain text : " << RailFenceCypher::decrypt(encryptedText, key, ignoreCharacter) << "\n\n";
      break;
    case 3:
      cout << "Enter ignore character list : ";
      getline(cin, ignoreCharacter, '\n');
      break;
    case 4:
      cout << "Exiting...";
      getchar();
      break;
    default:
      cout << "Wrong choice try again.." << endl;
      break;
    }
  } while (choice != 4);
  return 0;
}