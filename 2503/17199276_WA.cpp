/*
参考
http://www.cnblogs.com/Jason-Damon/archive/2012/04/02/2430232.html

ELFhash
http://blog.csdn.net/zhccl/article/details/7826137/
http://yiranwuqing.iteye.com/blog/1458407

本题考点：
1.怎样判定是否输入了空行
*/

#include <stdio.h>

#define MAX 100001

char dict[MAX][2][11];

typedef struct HashTable
{
	int id;
	HashTable *next;
}HashTable;

HashTable hashdata[MAX];
HashTable *hashPtr[MAX];
int hashindex;
int inputindex;

char s[30];

unsigned int ELFhash(char *str)
{
	unsigned int hashkey = 0;
	unsigned int x  = 0;

	

	while (*str != '\0')
	{
		hashkey = (hashkey << 4) + *(str++);
		if ((x = hashkey & 0xF0000000L) != 0)
		{
			hashkey ^= (x >> 24);
			//hashkey &= 0x0FFFFFFF;
			hashkey &= ~x;
		}
	}

	return (hashkey & 0x7FFFFFFF) % MAX;
}

bool StrCmp(char *s1, char *s2)
{
	for (; (*s1 == *s2) && (*s1 != '\0' || *s2 != '\0'); s1++, s2++);

	if (*s1 == '\0' && *s2 == '\0')
		return true;

	return false;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	inputindex = 0;
	hashindex = 0;

	unsigned int hashkey = 0;

	while (true)
	{
		gets(s);

		if (s[0] == '\0')
			break;

		sscanf(s, "%s %s", dict[inputindex][0], dict[inputindex][1]);

		hashkey = ELFhash(dict[inputindex][1]);
		if (hashPtr[hashkey] == NULL)
		{
			hashPtr[hashkey] = &hashdata[hashindex++];
			hashPtr[hashkey]->id = inputindex;
			hashPtr[hashkey]->next = NULL;
		}
		else
		{
			while (hashPtr[hashkey]->next != NULL)
			{
				hashPtr[hashkey] = hashPtr[hashkey]->next;
			}
			hashPtr[hashkey]->next = &hashdata[hashindex++];
			hashPtr[hashkey]->next->id = inputindex;
			hashPtr[hashkey]->next->next = NULL;
		}

		inputindex++;
	}

	while (gets(s))
	{
		//if (s[0] == '\0')
		//	break;

		hashkey = ELFhash(s);
		if (hashPtr[hashkey] == NULL)
		{
			printf("eh\n");
		}
		else
		{
			HashTable *ptr = hashPtr[hashkey];
			
			while (ptr != NULL)
			{
				if (StrCmp(dict[ptr->id][1], s))
				{
					printf("%s\n", dict[ptr->id][0]);
					break;
				}
				else
				{
					ptr = ptr->next;
				}
			}

			if (ptr == NULL)
			{
				printf("eh\n");
			}
		}
	}

	return 0;
}