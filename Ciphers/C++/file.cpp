#include <iostream>
#include "cryptography.h"

#define MATRIX_LEN 1024

using namespace std;

int main()
{
  Cryptography c;

  string plainText;
  string encryptedText;
  int key = 1;

  int flag;
  int choice = 1, choice2 = 1;
  while (1)
  {
    cout << "1. BACONIAN_CYPHER.\n";
    cout << "2. SUBSTITUTION_CYPHER.\n";
    cout << "3. TRANSPOSITION_CYPHER.\n";
    cout << "4. RAILFENCE_CYPHER.\n";
    cout << "5. VIGENERE_CIPHER.\n";
    cout << "6. PLAYFAIR_CIPHER.\n";
    cout << "7. Exit.\n";
    cout << "Enter your choice : ";
    cin >> choice;
    if (choice == 7)
      exit(0);
    if (choice < 1 || choice2 > 7)
      continue;

    while (1)
    {
      cout << "1. Encrypt.\n";
      cout << "2. Decrypt.\n";
      cout << "3. Set ignore character list.\n";
      cout << "4. Exit.\n";
      cout << "Enter your choice : ";
      cin >> choice2;
      if (choice2 == 4)
        exit(0);
      else if (choice2 < 1 || choice2 > 4)
        continue;
      else
        break;
    }
    
    switch (choice2)
    {
    case 1:
      cout << "Enter plain text : ";
      cin.ignore();
      getline(cin, plainText, '\n');
      flag = c.setPlainText(plainText);
      if (flag == 1)
        cout << "String contains special character(s).\n";
      cout << "Enter key : ";
      cin >> key;
      c.setKey(key);

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
    switch (choice)
    {
    case 1:
      cout break;

    default:
      break;
    }
  }

  c.setKey(3);
  c.setCarrierText("Ducimus quidem et eligendi. Quam odio et architecto exercitationem. Aut est sint odit. Nostrum minima perferendis repellat in aut explicabo aperiam labore. Quo ut sint et debitis. Consequuntur quos non fuga error quia culpa quaerat rerum.");

  c.setPlainText("defend the east wall");
  cout << "\nEncryption Algoorithm : BACONIAN_CYPHER" << endl;
  cout << "Plain text            : " << c.getPlainText() << endl;
  cout << "Encrypted text        : " << c.encrypt(BACONIAN_CYPHER) << endl;
  cout << "Decrypted text        : " << c.decrypt(BACONIAN_CYPHER) << endl;

  c.setPlainText("defend the east wall");
  cout << "\nEncryption Algoorithm : SUBSTITUTION_CYPHER" << endl;
  cout << "Plain text            : " << c.getPlainText() << endl;
  cout << "Encrypted text        : " << c.encrypt(SUBSTITUTION_CYPHER) << endl;
  cout << "Decrypted text        : " << c.decrypt(SUBSTITUTION_CYPHER) << endl;

  c.setPlainText("defend the east wall");
  cout << "\nEncryption Algoorithm : TRANSPOSITION_CYPHER" << endl;
  cout << "Plain text            : " << c.getPlainText() << endl;
  cout << "Encrypted text        : " << c.encrypt(TRANSPOSITION_CYPHER) << endl;
  cout << "Decrypted text        : " << c.decrypt(TRANSPOSITION_CYPHER, c.getEncryptedText().length()) << endl;

  c.setPlainText("defend the east wall");
  cout << "\nEncryption Algoorithm : RAILFENCE_CYPHER" << endl;
  cout << "Plain text            : " << c.getPlainText() << endl;
  cout << "Encrypted text        : " << c.encrypt(RAILFENCE_CYPHER) << endl;
  cout << "Decrypted text        : " << c.decrypt(RAILFENCE_CYPHER) << endl;

  c.setPlainText("defend the east wall");
  c.setPlainText("GEEKSFORGEEKS");
  cout << "\nEncryption Algoorithm : VIGENERE_CIPHER" << endl;
  cout << "Plain text            : " << c.getPlainText() << endl;
  c.setKeyText("AYUSH");
  cout << "Encrypted text        : " << c.encrypt(VIGENERE_CIPHER) << endl;
  cout << "Decrypted text        : " << c.decrypt(VIGENERE_CIPHER) << endl;

  c.setPlainText("instruments");
  cout << "\nEncryption Algoorithm : PLAYFAIR_CIPHER" << endl;
  cout << "Plain text            : " << c.getPlainText() << endl;
  c.setKeyText("MONARCHY");
  cout << "Encrypted text        : " << c.encrypt(PLAYFAIR_CIPHER) << endl;
  cout << "Decrypted text        : " << c.decrypt(PLAYFAIR_CIPHER) << endl;

  return 0;
}