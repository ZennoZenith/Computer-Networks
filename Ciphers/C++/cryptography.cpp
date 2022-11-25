#include <iostream>
#include "cryptography.h"

#define MATRIX_LEN 1024

using namespace std;

int main()
{
  Cryptography c;
  // c.setIgnoreChar(" ");
  // c.setPlainText("Hello World");
  c.setKey(3);
  c.setCarrierText("Ducimus quidem et eligendi Quam odio et architecto exercitationem Aut est sint odit Nostrum minima perferendis repellat in aut explicabo aperiam labore Quo ut sint et debitis Consequuntur quos non fuga error quia culpa quaerat rerum");

  c.setPlainText("Hello");
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
  c.setPlainText("Hello");
  cout << "\nEncryption Algoorithm : VIGENERE_CIPHER" << endl;
  cout << "Plain text            : " << c.getPlainText() << endl;
  c.setKeyText("AYUSH");
  c.setKeyText("Key");
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