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
#define VIGENERE_CIPHER 4
#define PLAYFAIR_CIPHER 5

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

class VigenereCipher
{
public:
  static string encrypt(string &, string &, string &);
  static string decrypt(string &, string &, string &);
};

string VigenereCipher::encrypt(string &plainText, string &keyText, string &ignoreChar)
{
  string encryptedText;
  int i;
  int len = plainText.length();
  encryptedText.resize(len);

  int keyLen = keyText.length();
  for (i = 0; i < len; i++)
  {
    char temp = Helper::ToUpperChar(plainText[i]);
    encryptedText[i] = 'A' + (temp - 'A' + keyText[i % keyLen] - 'A') % 26;
  }
  return encryptedText;
}
string VigenereCipher::decrypt(string &encryptedText, string &keyText, string &ignoreChar)
{
  int i;
  string plainText;
  int encryptedTextLen = encryptedText.length();
  plainText.resize(encryptedTextLen);

  int keyLen = keyText.length();
  for (i = 0; i < encryptedTextLen; i++)
  {
    char temp = Helper::ToUpperChar(encryptedText[i]);
    plainText[i] = 'A' + (temp - 'A' - (keyText[i % keyLen] - 'A') + 26) % 26;
  }
  return plainText;
}

class PlayfairCypher
{
public:
  static string encrypt(string &, string &, string &);
  static string decrypt(string &, string &, string &);
};

string PlayfairCypher::encrypt(string &plainText, string &keyText, string &ignoreChar)
{
  string encryptedText;
  int i;
  int len = plainText.length();

  //** removing duplicate characters from key
  string tempKeyText;
  tempKeyText.resize(26);
  int j = 0, k = 0, l = 0;
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
  tempKeyText.resize(j);
  if (j > 25)
    tempKeyText.resize(25);
  // tempKeyText[j] = '\0';
  // tempKeyText[25] = '\0';
  keyText.swap(tempKeyText);

  //***********************************

  // std::cout << "Key text : " << keyText << std::endl;
  // std::cout << "Key text len : " << keyText.length() << std::endl;

  k = 0, l = 0;
  keyLen = keyText.length();
  //* Setting up matrix
  char tempStr[] = "abcdefghiklmnopqrstuvwxyz";
  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 5; j++)
    {
      if (k < keyLen)
      {
        Helper::matrix[i][j] = keyText[k];
        int replace = 0;
        for (int p = 0; p < 25; p++)
        {
          if (tempStr[p] == keyText[k])
            replace = 1;
          if (replace)
            tempStr[p] = tempStr[p + 1];
        }
      }
      else
      {
        Helper::matrix[i][j] = tempStr[l];
        l++;
      }
      k++;
    }
  }
  // Helper::showMatrix(Helper::matrix, 5, 5);

  //* setup plainText
  char newPlainText[1024] = "";
  if (plainText[0] == 'j')
    plainText[0] = 'i';
  newPlainText[0] = Helper::ToLowerChar(plainText[0]);
  k = 1;
  for (i = 1; i < len; i++)
  {
    if (plainText[i] == 'j')
      plainText[i] = 'i';
    if (plainText[i] == plainText[i - 1])
    {
      newPlainText[k] = 'x';
      k++;
    }
    newPlainText[k] = Helper::ToLowerChar(plainText[i]);
    k++;
  }
  if (k % 2 != 0)
    newPlainText[k] = 'z';
  k++;

  plainText = newPlainText;
  len = plainText.length();
  encryptedText.resize(len);

  //* Encrypting
  for (i = 0; i < len; i += 2)
  {
    int i1, j1, i2, j2;
    for (k = 0; k < 5; k++)
    {
      for (l = 0; l < 5; l++)
      {
        if (Helper::matrix[k][l] == plainText[i])
        {
          i1 = k;
          j1 = l;
        }
        if (Helper::matrix[k][l] == plainText[i + 1])
        {
          i2 = k;
          j2 = l;
        }
      }
    }

    if (j1 == j2)
    {
      encryptedText[i] = Helper::matrix[(i1 + 1) % 5][j1];
      encryptedText[i + 1] = Helper::matrix[(i2 + 1) % 5][j2];
    }
    else if (i1 == i2)
    {
      encryptedText[i] = Helper::matrix[i1][(j1 + 1) % 5];
      encryptedText[i + 1] = Helper::matrix[i2][(j2 + 1) % 5];
    }
    else
    {
      encryptedText[i] = Helper::matrix[i1][j2];
      encryptedText[i + 1] = Helper::matrix[i2][j1];
    }
  }
  return encryptedText;
}
string PlayfairCypher::decrypt(string &encryptedText, string &keyText, string &ignoreChar)
{
  int i;
  string plainText;
  int len = encryptedText.length();

  //** removing duplicate characters from key
  string tempKeyText;
  tempKeyText.resize(26);
  int j = 0, k = 0, l = 0;
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
  tempKeyText.resize(j);
  if (j > 25)
    tempKeyText.resize(25);
  // tempKeyText[j] = '\0';
  // tempKeyText[25] = '\0';
  keyText.swap(tempKeyText);

  //***********************************

  // std::cout << "Key text : " << keyText << std::endl;
  // std::cout << "Key text len : " << keyText.length() << std::endl;

  k = 0, l = 0;
  keyLen = keyText.length();
  //* Setting up matrix
  char tempStr[] = "abcdefghiklmnopqrstuvwxyz";
  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 5; j++)
    {
      if (k < keyLen)
      {
        Helper::matrix[i][j] = keyText[k];
        int replace = 0;
        for (int p = 0; p < 25; p++)
        {
          if (tempStr[p] == keyText[k])
            replace = 1;
          if (replace)
            tempStr[p] = tempStr[p + 1];
        }
      }
      else
      {
        Helper::matrix[i][j] = tempStr[l];
        l++;
      }
      k++;
    }
  }
  // Helper::showMatrix(Helper::matrix, 5, 5);
  plainText.resize(len);

  //* Decrypting
  for (i = 0; i < len; i += 2)
  {
    int i1, j1, i2, j2;
    for (k = 0; k < 5; k++)
    {
      for (l = 0; l < 5; l++)
      {
        if (Helper::matrix[k][l] == encryptedText[i])
        {
          i1 = k;
          j1 = l;
        }
        if (Helper::matrix[k][l] == encryptedText[i + 1])
        {
          i2 = k;
          j2 = l;
        }
      }
    }

    if (j1 == j2)
    {
      plainText[i] = Helper::matrix[(i1 - 1 + 5) % 5][j1];
      plainText[i + 1] = Helper::matrix[(i2 - 1 + 5) % 5][j2];
    }
    else if (i1 == i2)
    {
      plainText[i] = Helper::matrix[i1][(j1 - 1 + 5) % 5];
      plainText[i + 1] = Helper::matrix[i2][(j2 - 1 + 5) % 5];
    }
    else
    {
      plainText[i] = Helper::matrix[i1][j2];
      plainText[i + 1] = Helper::matrix[i2][j1];
    }
  }
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
  string keyText;
  // char matrix[MATRIX_LEN][MATRIX_LEN];
  int key;

public:
  Cryptography()
  {
    plainText = "HelloWorld";
    encryptedText = "HelloWorld";
    ignoreChar = "";
    carrierText = "Ducimus quidem et eligendi Quam odio et architecto exercitationem Aut est sint odit Nostrum minima perferendis repellat in aut explicabo aperiam labore Quo ut sint et debitis Consequuntur quos non fuga error quia culpa quaerat rerum";
    key = 0;
  }
  void setKey(int k)
  {
    key = k;
  }
  void setKeyText(string &keyText)
  {
    this->keyText.swap(keyText);
    int keyLen = keyText.length();
    for (int i = 0; i < keyLen; i++)
      this->keyText[i] = Helper::ToUpperChar(keyText[i]);
  }
  void setKeyText(const char *keyText)
  {
    this->keyText = keyText;
    int keyLen = this->keyText.length();
    for (int i = 0; i < keyLen; i++)
      this->keyText[i] = Helper::ToUpperChar(keyText[i]);
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
  case VIGENERE_CIPHER:
    encryptedText = VigenereCipher::encrypt(plainText, keyText, ignoreChar);
    break;
  case PLAYFAIR_CIPHER:
    encryptedText = PlayfairCypher::encrypt(plainText, keyText, ignoreChar);
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
  case VIGENERE_CIPHER:
    plainText = VigenereCipher::decrypt(encryptedText, keyText, ignoreChar);
    break;
  case PLAYFAIR_CIPHER:
    plainText = PlayfairCypher::decrypt(encryptedText, keyText, ignoreChar);
    break;
  default:
    plainText = encryptedText;
    break;
  }
  return plainText;
}

#endif
