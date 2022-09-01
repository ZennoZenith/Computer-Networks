#include <iostream>
#include <string.h>

#define ZERO_CHAR 'a'
#define ONE_CHAR 'b'

using namespace std;

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

class Message
{
    string plainText;
    string encryptedText;
    string ignoreChar;
    string carrierText;
    int key;
    const string SMALL = "abcdefghijklmnopqrstuvwxyz";
    const string CAPITAL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int sanitiseText(string *);
    char ToUpperChar(char);
    char ToLowerChar(char);
    int IsUpperChar(char);
    int IsLowerChar(char);

public:
    Message();
    int setPlainText(string);
    int setEncryptedText(string);
    int setCarrierText(string);
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
    encryptedText = "grEETinGs frOm THe ReAL uNIVeRsE TodAY Is The dAy I wILl fiNA";
    ignoreChar = " ";
    carrierText = "Greetings from the real universe Today is the day I will finally know what brick tastes like";
    key = 3;
    sanitiseText(&this->plainText);
}

char Message::ToUpperChar(char ch)
{
    int j;
    for (j = 0; j < 26; j++)
    {
        if (SMALL[j] == ch)
            return CAPITAL[j];
    }
    return ch;
}

char Message::ToLowerChar(char ch)
{
    int j;
    for (j = 0; j < 26; j++)
    {
        if (CAPITAL[j] == ch)
            return SMALL[j];
    }
    return ch;
}

int Message::IsUpperChar(char ch)
{
    int j;
    for (j = 0; j < 26; j++)
    {
        if (CAPITAL[j] == ch)
            return 1;
    }
    return 0;
}

int Message::IsLowerChar(char ch)
{
    int j;
    for (j = 0; j < 26; j++)
    {
        if (SMALL[j] == ch)
            return 1;
    }
    return 0;
}

void Message::setKey(int key)
{
    this->key = key;
}

void Message::setIgnoreChar(string text)
{
    ignoreChar.swap(text);
}

int Message::setCarrierText(string carrierText)
{
    this->carrierText.swap(carrierText);
    return sanitiseText(&this->carrierText);
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
    int i, j, k, l = 0;
    char tempCh[5];
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
            encryptedText[j] = ToLowerChar(carrierText[j]);
        else
            encryptedText[j] = ToUpperChar(carrierText[j]);
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

string Message::decrypt()
{
    int len = SMALL.length();
    int len2 = ignoreChar.length();
    int encryptedTextLen = encryptedText.length();
    int i, j, k, l = 0;

    char tempCh[5];
    string intermediateText;

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
        plainText[j] = SMALL[index];
        j++;
    }
    plainText[j] = '\0';

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
        cout << "4. Set carrier text.\n";
        cout << "5. Exit.\n";
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
            // cout << "Enter key : ";
            // cin >> key;
            // m.setKey(key);
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
            // cout << "Enter key : ";
            // cin >> key;
            cout << "Plain text : " << m.decrypt() << endl;
            break;
        case 3:
            cout << "Enter ignore character list : ";
            cin.ignore();
            getline(cin, text, '\n');
            m.setIgnoreChar(text);
            break;
        case 4:
            cout << "Enter carrier text : ";
            cin.ignore();
            getline(cin, text, '\n');
            flag = m.setCarrierText(text);
            if (flag == 1)
                cout << "String contains special character(s).\n";
            break;
        case 5:
            cout << "Exiting...";
            getchar();
            getchar();
            break;
        default:
            cout << "Wrong choice try again.." << endl;
            break;
        }
    } while (choice != 5);

    return 0;
}