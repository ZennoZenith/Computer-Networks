#include <iostream>
#include "cryptography.h"

using namespace std;

int main()
{
  string plainText;
  string encryptedText;
  string ignoreCharacter = " ";
  string carrierText = "Ducimus quidem et eligendi Quam odio et architecto exercitationem Aut est sint odit Nostrum minima perferendis repellat in aut explicabo aperiam labore Quo ut sint et debitis Consequuntur quos non fuga error quia culpa quaerat rerum";
  int choice = 1;
  char flag;
  do
  {
    cout << "1. Encrypt.\n";
    cout << "2. Decrypt.\n";
    cout << "3. Set ignore character list.\n";
    cout << "4. Set carrier text.\n";
    cout << "5. Exit.\n";
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
      encryptedText = BaconianCypher::encrypt(plainText, carrierText, ignoreCharacter);
      cout << "Encrypted text : " << encryptedText << endl;
      cout << "Do you want to decrypt (y/n) : ";
      cin >> flag;
      if (flag == 'y' || flag == 'Y')
        cout << "Plain text : " << BaconianCypher::decrypt(encryptedText, carrierText, ignoreCharacter) << "\n\n";
      break;
    case 2:
      cout << "Enter encrypted text : ";
      getline(cin, encryptedText, '\n');
      flag = Helper::sanitiseText(encryptedText);
      if (flag == 1)
        cout << "String contains special character(s).\n";
      cout << "Plain text : " << BaconianCypher::decrypt(encryptedText, carrierText, ignoreCharacter) << "\n\n";
      break;
    case 3:
      cout << "Enter ignore character list : ";
      getline(cin, ignoreCharacter, '\n');
      break;
    case 4:
      cout << "Enter carrier text : ";
      getline(cin, carrierText, '\n');
      break;
    case 5:
      cout << "Exiting...";
      getchar();
      break;
    default:
      cout << "Wrong choice try again.." << endl;
      break;
    }
  } while (choice != 5);
  return 0;
}