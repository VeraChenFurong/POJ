#include <stdio.h>

char X[1100];
char Y[1100];
int RESULT[1100][1100];

int x_len;
int y_len;

int str_len(const char *str)
{
	int len = 0;
	while (*str++ != '\0')
		len++;

	return len;
}

int mymax(int x, int y)
{
	int result;
	result = x >= y ? x : y;

	return result;
}

int main()
{
	//freopen("input.txt", "r", stdin);

	while (scanf("%s %s", X, Y) != EOF)
	{
		x_len = str_len(X);
		y_len = str_len(Y);

		for (int i = 1; i <= x_len; i++)
		{
			for (int j = 1; j <= y_len; j++)
			{
				if (X[i - 1] == Y[j - 1])
				{
					RESULT[i][j] = RESULT[i - 1][j - 1] + 1;
				}
				else
				{
					RESULT[i][j] = mymax(RESULT[i - 1][j], RESULT[i][j - 1]);
				}
			}
		}

		printf("%d\n", RESULT[x_len][y_len]);
	}

	return 0;
}