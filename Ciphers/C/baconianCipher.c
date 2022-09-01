#include <stdio.h>
#define STR_LEN 500

#define ZERO_CHAR 'a'
#define ONE_CHAR 'b'

char SMALL[STR_LEN] = "abcdefghijklmnopqrstuvwxyz";
char CAPITAL[STR_LEN] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int key = 3;
char plainText[STR_LEN] = "HelloWorld";
char encryptedText[STR_LEN] = "grEETinGs frOm THe ReAL uNIVeRsE TodAY Is The dAy I wILl fiNA";
char carrierText[STR_LEN] = "Greetings from the real universe Today is the day I will finally know what brick tastes like";
char ignoreChar[STR_LEN] = " ";

void ConvertNumberToCharacterList(int number, char tempCh[])
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

int ConvertCharacterListToNumber(char tempCh[])
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

char ToUpperChar(char ch)
{
    int j;
    for (j = 0; j < 26; j++)
    {
        if (SMALL[j] == ch)
            return CAPITAL[j];
    }
    return ch;
}

char ToLowerChar(char ch)
{
    int j;
    for (j = 0; j < 26; j++)
    {
        if (CAPITAL[j] == ch)
            return SMALL[j];
    }
    return ch;
}

int IsUpperChar(char ch)
{
    int j;
    for (j = 0; j < 26; j++)
    {
        if (CAPITAL[j] == ch)
            return 1;
    }
    return 0;
}

int IsLowerChar(char ch)
{
    int j;
    for (j = 0; j < 26; j++)
    {
        if (SMALL[j] == ch)
            return 1;
    }
    return 0;
}

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
    int i, j, k, l = 0;
    char tempCh[5];
    char intermediateText[STR_LEN];
    // encryptedText.resize(plainTextLen);

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
        if (k != len2)
            continue;

        for (j = 0; j < len; j++)
        {
            if (SMALL[j] == plainText[i])
                break;
            if (CAPITAL[j] == plainText[i])
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

    j = 0;
    for (i = 0; i < intermediateTextLength; i++)
    {
        while (carrierText[j] == ' ')
        {
            encryptedText[j] = carrierText[j];
            j++;
        }

        if (intermediateText[i] == ZERO_CHAR)
            encryptedText[j] = ToLowerChar(carrierText[j]);
        else
            encryptedText[j] = ToUpperChar(carrierText[j]);
        j++;
    }
    encryptedText[j] = '\0';

    /*For debugging
    cout << "\n                 ";
    j = 0;
    for (int gg = 0; gg < StrLen(encryptedText); gg++)
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

char *decrypt()
{
    int len = StrLen(SMALL);
    int len2 = StrLen(ignoreChar);
    int encryptedTextLen = StrLen(encryptedText);
    int i, j, k, l = 0;

    char tempCh[5];
    char intermediateText[STR_LEN];

    // Number of spaces in carrier text
    int numberOfspaces = 0;
    for (i = 0; i < encryptedTextLen; i++)
    {
        if (encryptedText[i] == ' ')
            numberOfspaces++;
    }

    int intermediateTextLength = encryptedTextLen - numberOfspaces;

    for (i = 0, j = 0; i < encryptedTextLen; i++)
    {
        while (encryptedText[i] == ' ')
            i++;
        if (IsUpperChar(encryptedText[i]))
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

    j = 0;
    for (i = 0; i < intermediateTextLength; i += 5)
    {
        tempCh[0] = intermediateText[i];
        tempCh[1] = intermediateText[i + 1];
        tempCh[2] = intermediateText[i + 2];
        tempCh[3] = intermediateText[i + 3];
        tempCh[4] = intermediateText[i + 4];
        int index = ConvertCharacterListToNumber(tempCh);
        plainText[j] = SMALL[index];
        j++;
    }
    plainText[j] = '\0';

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
        printf("4. Set carrier text.\n");
        printf("5. Exit.\n");
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
            printf("Plain text : %s\n", decrypt());
            break;
        case 3:
            printf("Enter ignore character list : ");
            // fgets(ignoreChar, STR_LEN, stdin);
            scanf("%[^\n]%*c", ignoreChar);
            break;
        case 4:
            printf("Enter carrier text : ");
            // fgets(carrierText, STR_LEN, stdin);
            scanf("%[^\n]%*c", carrierText);
            flag = sanitiseText(carrierText);
            if (flag == 1)
                printf("String contains special character(s).\n");
            break;
        case 5:
            printf("Exiting...");
            getchar();
            getchar();
            break;
        default:
            printf("Wrong choice try again..\n");
            break;
        }
    } while (choice != 5);

    return 0;
}