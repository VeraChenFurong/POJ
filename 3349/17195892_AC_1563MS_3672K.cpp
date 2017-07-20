/*
http://blog.csdn.net/lyy289065406/article/details/6647351

设i为A、B的第i片叶子，j为B当前顺时针转过的格数
那么  A（i） ---> B（ (i+j)%6 ）
设i为A、B的第i片叶子，j为B当前逆时针转过的格数
那么  A（i） ---> B（ (5-i-j+6)%6 ）
*/
#include <stdio.h>

#define PRIME 99983 //100000内最大的素数

typedef struct Leaf
{
	int len[6];
}Leaf;

typedef struct HashTable{
	int index;
	struct HashTable *next;
}HashTable;

HashTable hash[PRIME + 1];
HashTable *hashPtr[PRIME + 1];
int hashindex = 0;
Leaf snow[100001];

int N;

bool findflag = false;

//计算key值
int compute_key(int k)
{
	int key = 0;
	for (int i = 0; i < 6; i++)
	{
		key += (snow[k].len[i]) % PRIME;
		key %= PRIME;
	}

	return ++key;
}

bool clockwise(HashTable* p, int k)
{
	for (int i = 0; i < 6; i++)
	{
		bool flag = true;

		for (int j = 0; j < 6; j++)
		{
			if (snow[k].len[j] != snow[p->index].len[(i + j) % 6])
			{
				flag = false;
				break;
			}
		}

		if (flag == true)
			return true;
	}

	return false;
}

bool counterclockwise(HashTable* p, int k)
{
	for (int i = 0; i < 6; i++)
	{
		bool flag = true;

		for (int j = 0; j < 6; j++)
		{
			if (snow[k].len[j] != snow[p->index].len[(5 - i - j + 6) % 6])
			{
				flag = false;
				break;
			}
		}

		if (flag == true)
			return true;
	}

	return false;
}

bool insert(int k)
{
	int key = compute_key(k);
	if (hashPtr[key] == NULL)	//证明之前没有保存过
	{
		hashPtr[key] = &hash[hashindex++];
		hashPtr[key]->index = k;
		hashPtr[key]->next = NULL;
	}
	else//key 冲突
	{
		HashTable *ptrTemp = hashPtr[key];

		//检查雪花是否相同
		if (clockwise(ptrTemp, k) || counterclockwise(ptrTemp, k))
			return true;

		//寻址
		while (ptrTemp->next != NULL)
		{
			ptrTemp = ptrTemp->next;

			//检查雪花是否相同
			if (clockwise(ptrTemp, k) || counterclockwise(ptrTemp, k))
				return true;

		}
		//申请空间保存新雪花
		ptrTemp->next = &hash[hashindex++];
		ptrTemp->next->index = k;
	}

	return false;
}

int main()
{
	scanf("%d", &N);
	for (int k = 1; k <= N; k++)
	{
		scanf("%d %d %d %d %d %d", &snow[k].len[0], &snow[k].len[1], &snow[k].len[2], &snow[k].len[3], &snow[k].len[4], &snow[k].len[5]);

		if (!findflag)
			findflag = insert(k);
		
	}

	if (findflag)
		printf("Twin snowflakes found.\n");
	else
		printf("No two snowflakes are alike.\n");

	return 0;
}