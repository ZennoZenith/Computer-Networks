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

  cout << "\n\n\n";
  cout << "Matrix length : " << MATRIX_LEN << endl;
  return 0;
}