#ifndef CRYPTOGRAPHY
#define CRYPTOGRAPHY

// #include <stdio.h>
#include <string>
#include <math.h>

#define MATRIX_LEN 1024

#define BACONIAN_CYPHER 0
#define SUBSTITUTION_CYPHER 1
#define TRANSPOSITION_CYPHER 2
#define RAILFENCE_CYPHER 3

using std::string;

class Helper
{
public:
  static int sanitiseText(string &, string);
  static char ToUpperChar(char);
  static char ToLowerChar(char);
  static int IsUpperChar(char);
  static int IsLowerChar(char);
  static char matrix[MATRIX_LEN][MATRIX_LEN];
  static void showMatrix(char matrix[MATRIX_LEN][MATRIX_LEN], int, int);

  static const string SMALL;
  static const string CAPITAL;
};

const string Helper::SMALL = "abcdefghijklmnopqrstuvwxyz";
const string Helper::CAPITAL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char Helper::matrix[MATRIX_LEN][MATRIX_LEN] = {};

char Helper::ToUpperChar(char ch)
{
  int j;
  for (j = 0; j < 26; j++)
  {
    if (SMALL[j] == ch)
      return CAPITAL[j];
  }
  return ch;
}

char Helper::ToLowerChar(char ch)
{
  int j;
  for (j = 0; j < 26; j++)
  {
    if (CAPITAL[j] == ch)
      return SMALL[j];
  }
  return ch;
}

int Helper::IsUpperChar(char ch)
{
  int j;
  for (j = 0; j < 26; j++)
  {
    if (CAPITAL[j] == ch)
      return 1;
  }
  return 0;
}

int Helper::IsLowerChar(char ch)
{
  int j;
  for (j = 0; j < 26; j++)
  {
    if (SMALL[j] == ch)
      return 1;
  }
  return 0;
}

int Helper::sanitiseText(string &text, string ignoreChar = "")
{
  int i = 0, j = 0, k = 0, len = 0, len2 = 0, flag = 0;
  len = SMALL.length();
  len2 = ignoreChar.length();
  while (text[i] != '\0')
  {
    for (k = 0; k < len2; k++)
    {
      if (text[i] == ignoreChar[k])
        break;
    }
    if (k != len2)
    {
      text[j] = text[i];
      j++;
      i++;
      continue;
    }

    for (k = 0; k < len; k++)
    {
      if (text[i] == SMALL[k])
        break;
      else if (text[i] == CAPITAL[k])
        break;
    }
    if (k != len)
    {
      text[j] = text[i];
      j++;
    }
    else
      flag = 1;
    i++;
  }
  text[j] = '\0';
  text.resize(j);
  return flag;
}

void Helper::showMatrix(char matrix[MATRIX_LEN][MATRIX_LEN], int m, int n)
{
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (matrix[i][j] == 0)
        printf(" ");
      else
        printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

class BaconianCypher
{
private:
  static const char ZERO_CHAR;
  static const char ONE_CHAR;
  static void ConvertNumberToCharacterList(int, char[]);
  static int ConvertCharacterListToNumber(char[]);

public:
  static string encrypt(string &, string &, string &);
  static string decrypt(string &, string &, string &);
};

const char BaconianCypher::ZERO_CHAR = 'a';
const char BaconianCypher::ONE_CHAR = 'b';

void BaconianCypher::ConvertNumberToCharacterList(int number, char tempCh[])
{
  int i;
  for (i = 4; i > -1; i--)
  {
    if (number % 2 == 0)
      tempCh[i] = ZERO_CHAR;
    else
      tempCh[i] = ONE_CHAR;
    number /= 2;
  }
}
int BaconianCypher::ConvertCharacterListToNumber(char tempCh[])
{
  int i;
  int number = 0;
  int temp = 1;
  for (i = 4; i > -1; i--)
  {
    if (tempCh[i] == ONE_CHAR)
    {
      number += temp;
    }
    temp *= 2;
  }
  return number;
}

string BaconianCypher::encrypt(string &plainText, string &carrierText, string &ignoreChar)
{
  int len = Helper::SMALL.length();
  int len2 = ignoreChar.length();
  int plainTextLen = plainText.length();
  int i, j, k, l = 0;
  char tempCh[5];
  string encryptedText;
  string intermediateText;
  intermediateText.resize(plainTextLen * 5);
  // encryptedText.resize(plainTextLen);

  for (i = 0; i < plainTextLen; i++)
  {
    for (k = 0; k < len2; k++)
    {
      if (plainText[i] == ignoreChar[k])
        break;
    }
    if (k != len2)
      continue;

    for (j = 0; j < len; j++)
    {
      if (Helper::SMALL[j] == plainText[i])
        break;
      if (Helper::CAPITAL[j] == plainText[i])
        break;
    }
    ConvertNumberToCharacterList(j, tempCh);
    for (k = 0; k < 5; k++)
    {
      intermediateText[l] = tempCh[k];
      l++;
    }
  }
  intermediateText[l] = '\0';
  int intermediateTextLength = l;

  /*For debugging

  //* Print intermediate text for debuging
  cout << "Intermediate text  : ";
  for (i = 0; i < intermediateTextLength; i++)
  {
      cout << intermediateText[i];
      if ((i + 1) % 5 == 0)
          cout << " ";
  }
  cout << endl;
  */

  // Number of spaces in carrier text
  int numberOfspaces = 0;
  for (i = 0, j = 0; i < intermediateTextLength; i++)
  {
    while (carrierText[j] == ' ')
    {
      numberOfspaces++;
      j++;
    }
    j++;
  }
  encryptedText.resize(intermediateTextLength + numberOfspaces);
  j = 0;
  for (i = 0; i < intermediateTextLength; i++)
  {
    while (carrierText[j] == ' ')
    {
      encryptedText[j] = carrierText[j];
      j++;
    }

    if (intermediateText[i] == ZERO_CHAR)
      encryptedText[j] = Helper::ToLowerChar(carrierText[j]);
    else
      encryptedText[j] = Helper::ToUpperChar(carrierText[j]);
    j++;
  }

  encryptedText[j] = '\0';

  /*For debugging
  cout << "\n                 ";
  j = 0;
  for (int gg = 0; gg < encryptedText.length(); gg++)
  {
      if (encryptedText[gg] == ' ')
          cout << " ";
      else
      {
          cout << intermediateText[j];
          j++;
      }
  }
  cout << "\n";
  */

  return encryptedText;
}
string BaconianCypher::decrypt(string &encryptedText, string &carrierText, string &ignoreChar)
{
  int len = Helper::SMALL.length();
  int len2 = ignoreChar.length();
  int encryptedTextLen = encryptedText.length();
  int i, j, k, l = 0;

  char tempCh[5];
  string intermediateText;
  string plainText;

  // Number of spaces in carrier text
  int numberOfspaces = 0;
  for (i = 0; i < encryptedTextLen; i++)
  {
    if (encryptedText[i] == ' ')
      numberOfspaces++;
  }

  int intermediateTextLength = encryptedTextLen - numberOfspaces;
  intermediateText.resize(intermediateTextLength);

  for (i = 0, j = 0; i < encryptedTextLen; i++)
  {
    while (encryptedText[i] == ' ')
      i++;
    if (Helper::IsUpperChar(encryptedText[i]))
      intermediateText[j] = ONE_CHAR;
    else
      intermediateText[j] = ZERO_CHAR;
    j++;
  }

  /*For debugging
  //* Print intermediate text for debuging
  cout << "Intermediate text  : ";
  for (i = 0; i < encryptedTextLen - numberOfspaces; i++)
  {
      cout << intermediateText[i];
      if ((i + 1) % 5 == 0)
          cout << " ";
  }
  cout << endl;
  */

  plainText.resize(intermediateTextLength / 5);

  j = 0;
  for (i = 0; i < intermediateTextLength; i += 5)
  {
    tempCh[0] = intermediateText[i];
    tempCh[1] = intermediateText[i + 1];
    tempCh[2] = intermediateText[i + 2];
    tempCh[3] = intermediateText[i + 3];
    tempCh[4] = intermediateText[i + 4];
    int index = ConvertCharacterListToNumber(tempCh);
    plainText[j] = Helper::SMALL[index];
    j++;
  }
  plainText[j] = '\0';

  return plainText;
}

class SubstitutionCypher
{
public:
  static string encrypt(string &, int, string &);
  static string decrypt(string &, int, string &);
};

string SubstitutionCypher::encrypt(string &plainText, int key, string &ignoreChar)
{
  int len = Helper::SMALL.length();
  int len2 = ignoreChar.length();
  int plainTextLen = plainText.length();
  int i, k;

  string encryptedText;
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
      if (plainText[i] == Helper::SMALL[k])
        encryptedText[i] = Helper::SMALL[index];
      else if (plainText[i] == Helper::CAPITAL[k])
        encryptedText[i] = Helper::CAPITAL[index];
    }
  }
  encryptedText[i] = '\0';
  return encryptedText;
}
string SubstitutionCypher::decrypt(string &encryptedText, int key, string &ignoreChar)
{
  int len = Helper::SMALL.length();
  int len2 = ignoreChar.length();
  int encryptedTextLen = encryptedText.length();
  int i, k;

  string plainText;
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

      if (encryptedText[i] == Helper::SMALL[k])
        plainText[i] = Helper::SMALL[index];
      else if (encryptedText[i] == Helper::CAPITAL[k])
        plainText[i] = Helper::CAPITAL[index];
    }
  }
  plainText[i] = '\0';
  return plainText;
}

class TranspositionCypher
{
  static char matrix[MATRIX_LEN][MATRIX_LEN];
  static char RAND_CHAR;

public:
  static string encrypt(string &, int, string &);
  static string decrypt(string &, int, int, string &);
};
char TranspositionCypher::RAND_CHAR = 'M';

string TranspositionCypher::encrypt(string &plainText, int key, string &ignoreChar)
{
  int i, j, k = 0, len;
  len = plainText.length();
  int plainTextlen = len;
  int numberOfRows = ceil((float)len / key);
  string encryptedText;
  encryptedText.resize(numberOfRows * key);

  for (i = 0; i < numberOfRows; i++)
  {
    for (j = 0; j < key; j++)
    {
      if (k < len)
        Helper::matrix[i][j] = plainText[k];
      else
        Helper::matrix[i][j] = TranspositionCypher::RAND_CHAR;
      k++;
    }
  }
  // Helper::showMatrix(Helper::matrix, numberOfRows, key);

  k = 0;
  for (j = 0; j < key; j++)
  {
    for (i = 0; i < numberOfRows; i++)
    {
      encryptedText[k] = Helper::matrix[i][j];
      k++;
    }
  }
  encryptedText[k] = '\0';
  return encryptedText;
}
string TranspositionCypher::decrypt(string &encryptedText, int key, int plainTextlen, string &ignoreChar)
{
  int i, j, k = 0;
  int len = encryptedText.length();
  int numberOfRows = ceil((float)len / key);

  string plainText;
  plainText.resize(plainTextlen);

  for (j = 0; j < key; j++)
  {
    for (i = 0; i < numberOfRows; i++)
    {
      if (encryptedText[k] != '\0')
        Helper::matrix[i][j] = encryptedText[k];
      else
        Helper::matrix[i][j] = RAND_CHAR;
      k++;
    }
  }
  // Helper::showMatrix(Helper::matrix, numberOfRows, key);

  k = 0;
  for (i = 0; i < numberOfRows; i++)
  {
    for (j = 0; j < key; j++)
    {
      plainText[k] = Helper::matrix[i][j];
      k++;
      if (k == plainTextlen)
        break;
    }
  }
  plainText[k] = '\0';
  return plainText;
}

class RailFenceCypher
{
public:
  static string encrypt(string &, int, string &);
  static string decrypt(string &, int, string &);
};

string RailFenceCypher::encrypt(string &plainText, int key, string &ignoreChar)
{
  string encryptedText;
  int i, j, k = 0, len;
  len = plainText.length();
  encryptedText.resize(len + 1);
  int plainTextlen = len;
  int numberOfRows = key;
  i = j = k = 0;
  int flag = 0;

  for (i = 0; i < MATRIX_LEN; i++)
  {
    for (j = 0; j < MATRIX_LEN; j++)
    {
      Helper::matrix[i][j] = 0;
    }
  }

  i = j = k = 0;
  flag = 0;
  for (k = 0; plainText[k] != '\0'; k++)
  {
    Helper::matrix[i][j] = plainText[k];
    // printf("matrix[%d][%d] = %c\n", i, j, matrix[i][j]);
    j++;
    if (i + 1 >= key)
    {
      flag = 1;
      i--;
      continue;
    }
    if (i <= 0)
    {
      flag = 0;
      i++;
      continue;
    }
    if (flag == 0)
      i++;
    else
      i--;
  }
  // Helper::showMatrix(Helper::matrix, key, plainTextlen);

  k = 0;
  for (i = 0; i < key; i++)
  {
    for (j = 0; j < plainTextlen; j++)
    {
      if (Helper::matrix[i][j] != '\0')
      {
        encryptedText[k] = Helper::matrix[i][j];
        k++;
      }
    }
  }
  encryptedText[k] = '\0';
  return encryptedText;
}
string RailFenceCypher::decrypt(string &encryptedText, int key, string &ignoreChar)
{
  int i, j, k = 0;
  int len = encryptedText.length();
  int numberOfRows = key;
  string plainText;
  plainText.resize(len + 1);
  i = j = k = 0;
  int flag = 0;
  for (i = 0; i < MATRIX_LEN; i++)
  {
    for (j = 0; j < MATRIX_LEN; j++)
    {
      Helper::matrix[i][j] = 0;
    }
  }

  i = j = k = 0;
  flag = 0;
  for (k = 0; encryptedText[k] != '\0'; k++)
  {

    Helper::matrix[i][j] = '!';

    // printf("matrix[%d][%d] = %c\n", i, j, matrix[i][j]);
    j++;
    if (i + 1 >= key)
    {
      flag = 1;
      i--;
      continue;
    }
    if (i <= 0)
    {
      flag = 0;
      i++;
      continue;
    }
    if (flag == 0)
      i++;
    else
      i--;
  }

  k = 0;
  for (i = 0; i < key; i++)
  {
    for (j = 0; j < len; j++)
    {
      if (Helper::matrix[i][j] == '!')
      {
        Helper::matrix[i][j] = encryptedText[k];
        k++;
      }
    }
  }
  // Helper::showMatrix(Helper::matrix, key, len);

  k = 0;
  for (j = 0; j < len; j++)
  {
    for (i = 0; i < key; i++)
    {
      if (Helper::matrix[i][j] != '\0')
      {
        plainText[k] = Helper::matrix[i][j];
        k++;
      }
    }
  }
  plainText[k] = '\0';
  return plainText;
}

class Cryptography
{
private:
protected:
  string plainText;
  string encryptedText;
  string ignoreChar;
  string carrierText;
  // char matrix[MATRIX_LEN][MATRIX_LEN];
  int key;

public:
  Cryptography()
  {
    plainText = "HelloWorld";
    encryptedText = "HelloWorld";
    ignoreChar = "";
    carrierText = "Ducimus quidem et eligendi. Quam odio et architecto exercitationem. Aut est sint odit. Nostrum minima perferendis repellat in aut explicabo aperiam labore. Quo ut sint et debitis. Consequuntur quos non fuga error quia culpa quaerat rerum.";
    key = 0;
  }
  void setKey(int k)
  {
    key = k;
  }
  string getPlainText();
  string getEncryptedText();
  int setPlainText(string);
  int setEncryptedText(string);
  int setCarrierText(string);
  void setIgnoreChar(string);
  string encrypt(int);
  string decrypt(int, int);
};

int Cryptography::setPlainText(string plainText)
{
  this->plainText = plainText;
  return Helper::sanitiseText(this->plainText, ignoreChar);
}
int Cryptography::setEncryptedText(string encryptedText)
{
  this->encryptedText = encryptedText;
  return Helper::sanitiseText(this->encryptedText, ignoreChar);
}
int Cryptography::setCarrierText(string carrierText)
{
  this->carrierText = carrierText;
  // return Helper::sanitiseText(this->carrierText);
  return 0;
}
void Cryptography::setIgnoreChar(string s)
{
  ignoreChar = s;
}

string Cryptography::getPlainText()
{
  return plainText;
}
string Cryptography::getEncryptedText()
{
  return encryptedText;
}

string Cryptography::encrypt(int encryptAlg)
{

  switch (encryptAlg)
  {
  case BACONIAN_CYPHER:
    encryptedText = BaconianCypher::encrypt(plainText, carrierText, ignoreChar);
    break;
  case SUBSTITUTION_CYPHER:
    encryptedText = SubstitutionCypher::encrypt(plainText, key, ignoreChar);
    break;
  case TRANSPOSITION_CYPHER:
    encryptedText = TranspositionCypher::encrypt(plainText, key, ignoreChar);
    break;
  case RAILFENCE_CYPHER:
    encryptedText = RailFenceCypher::encrypt(plainText, key, ignoreChar);
    break;

  default:
    encryptedText = plainText;

    break;
  }
  return encryptedText;
}
string Cryptography::decrypt(int decryptAlg, int extra = 0)
{
  switch (decryptAlg)
  {
  case BACONIAN_CYPHER:
    plainText = BaconianCypher::decrypt(encryptedText, carrierText, ignoreChar);
    break;
  case SUBSTITUTION_CYPHER:
    plainText = SubstitutionCypher::decrypt(encryptedText, key, ignoreChar);
    break;
  case TRANSPOSITION_CYPHER:
    plainText = TranspositionCypher::decrypt(encryptedText, key, extra, ignoreChar);
    break;
  case RAILFENCE_CYPHER:
    plainText = RailFenceCypher::decrypt(encryptedText, key, ignoreChar);
    break;
  default:
    plainText = encryptedText;
    break;
  }
  return plainText;
}

#endif
