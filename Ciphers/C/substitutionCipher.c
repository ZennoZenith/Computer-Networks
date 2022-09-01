#include <stdio.h>
#define STR_LEN 500

char SMALL[STR_LEN] = "abcdefghijklmnopqrstuvwxyz";
char CAPITAL[STR_LEN] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int key = 3;
char plainText[STR_LEN] = "HelloWorld";
char encryptedText[STR_LEN] = "KhoorQhzZruog";
char ignoreChar[STR_LEN] = "";

int StrLen(char text[])
{
  int i = 0;
  while (text[i] != '\0')
    i++;
  return i;
}

int sanitiseText(char text[])
{
  int i = 0, j = 0, k = 0, len = 0, len2 = 0, flag = 0;
  len = StrLen(SMALL);
  len2 = StrLen(ignoreChar);

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
  return flag;
}

char *encrypt()
{
  int len = StrLen(SMALL);
  int len2 = StrLen(ignoreChar);
  int plainTextLen = StrLen(plainText);
  int i, k;

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

char *decrypt()
{
  int len = StrLen(SMALL);
  int len2 = StrLen(ignoreChar);
  int encryptedTextLen = StrLen(encryptedText);
  int i, k;

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
      int index = (k - key);
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
  int choice;
  char flag;
  do
  {
    printf("1. Encrypt.\n");
    printf("2. Decrypt.\n");
    printf("3. Set ignore character list.\n");
    printf("4. Exit.\n");
    printf("Enter your choice : ");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
      printf("Enter plain text : ");
      // fgets(plainText, STR_LEN, stdin);
      scanf("%[^\n]%*c", plainText);
      flag = sanitiseText(plainText);

      if (flag == 1)
        printf("String contains special character(s).\n");
      printf("Enter key : ");
      scanf("%d", &key);
      getchar();

      printf("Encrypted text : %s\n", encrypt());
      printf("Do you want to decrypt (y/n) : ");
      scanf("%c", &flag);
      if (flag == 'y' || flag == 'Y')
        printf("Plain text : %s\n", decrypt());
      break;
    case 2:
      printf("Enter encrypted text : ");
      // fgets(encryptedText, STR_LEN, stdin);
      scanf("%[^\n]%*c", encryptedText);
      flag = sanitiseText(encryptedText);
      if (flag == 1)
        printf("String contains special character(s).\n");
      printf("Enter key : ");
      scanf("%d", &key);
      printf("Plain text : %s\n", decrypt());
      break;
    case 3:
      printf("Enter ignore character list : ");
      // fgets(ignoreChar, STR_LEN, stdin);
      scanf("%[^\n]%*c", ignoreChar);
      break;
    case 4:
      printf("Exiting...");
      getchar();
      getchar();
      break;
    default:
      printf("Wrong choice try again..\n");
      break;
    }
  } while (choice != 4);

  return 0;
}