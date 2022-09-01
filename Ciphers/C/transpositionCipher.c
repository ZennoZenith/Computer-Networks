#include <stdio.h>
#include <math.h>

#define STR_LEN 500
#define MATRIX_LEN 100
#define RAND_CHAR 'M'

char SMALL[STR_LEN] = "abcdefghijklmnopqrstuvwxyz";
char CAPITAL[STR_LEN] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int key = 3;
int plainTextlen = 10;
char matrix[MATRIX_LEN][MATRIX_LEN];
char plainText[STR_LEN] = "HelloWorld";
char encryptedText[STR_LEN] = "HlodeorMlWlM";
char ignoreChar[STR_LEN] = "";

int StrLen(char text[])
{
	int i = 0;
	while (text[i] != '\0')
		i++;
	return i;
}
void showMatrix(int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%c", matrix[i][j]);
		}
		printf("\n");
	}
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
	int i, j, k = 0, len;
	len = StrLen(plainText);
	plainTextlen = len;
	int numberOfRows = ceil((float)len / key);

	for (i = 0; i < numberOfRows; i++)
	{
		for (j = 0; j < key; j++)
		{
			if (k < len)
				matrix[i][j] = plainText[k];
			else
				matrix[i][j] = RAND_CHAR;
			k++;
		}
	}
	showMatrix(numberOfRows, key);

	k = 0;
	for (j = 0; j < key; j++)
	{
		for (i = 0; i < numberOfRows; i++)
		{
			encryptedText[k] = matrix[i][j];
			k++;
		}
	}
	encryptedText[k] = '\0';
	return encryptedText;
}

char *decrypt()
{
	int i, j, k = 0;
	int len = StrLen(encryptedText);
	int numberOfRows = ceil((float)len / key);

	for (j = 0; j < key; j++)
	{
		for (i = 0; i < numberOfRows; i++)
		{
			if (encryptedText[k] != '\0')
				matrix[i][j] = encryptedText[k];
			else
				matrix[i][j] = RAND_CHAR;
			k++;
		}
	}
	showMatrix(numberOfRows, key);

	k = 0;
	for (i = 0; i < numberOfRows; i++)
	{
		for (j = 0; j < key; j++)
		{
			plainText[k] = matrix[i][j];
			k++;
			if (k == plainTextlen)
				break;
		}
	}
	plainText[k] = '\0';
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
			// getchar();
			printf("Enter string len : ");
			scanf("%d", &plainTextlen);
			// getchar();
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