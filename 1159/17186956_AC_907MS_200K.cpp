/*
*思路：LCS，求序列与逆序列的最长子序列，然后使用Len减去最长子序列的长度
*LCS：受空间限制，需要使用滚动数组http://www.nocow.cn/index.php/%E6%BB%9A%E5%8A%A8%E6%95%B0%E7%BB%84
*/
#include <stdio.h>

char INPUT[5000 + 1];
int LEN;
char INPUT_REVERSE[5000 + 1];
int RESULT[2][5000 + 1];

void get_reverse_str(char *src, char *dest, int len)
{
	for (int i = 0; i < len; i++)
	{
		*dest++ = *(src + (len - 1 - i));
	}

	*dest = '\0';
}

int my_max(int x, int y)
{
	int result;

	result = x >= y ? x : y;
	return result;
}
int main()
{
	while (scanf("%d", &LEN) != EOF)
	{
		scanf("%s", INPUT);

		get_reverse_str(INPUT, INPUT_REVERSE, LEN);

		for (int i = 1; i <= LEN; i++)
		{
			for (int j = 1; j <= LEN; j++)
			{
				if (i % 2 == 0)
				{
					if (INPUT[i - 1] == INPUT_REVERSE[j - 1])
					{
						RESULT[0][j] = RESULT[1][j - 1] + 1;
					}
					else
					{
						RESULT[0][j] = my_max(RESULT[0][j - 1], RESULT[1][j]);
					}
				}
				else
				{
					if (INPUT[i - 1] == INPUT_REVERSE[j - 1])
					{
						RESULT[1][j] = RESULT[0][j - 1] + 1;
					}
					else
					{
						RESULT[1][j] = my_max(RESULT[1][j - 1], RESULT[0][j]);
					}
				}
			}
		}

		printf("%d\n", LEN - RESULT[LEN % 2][LEN]);
	}

	return 0;
}