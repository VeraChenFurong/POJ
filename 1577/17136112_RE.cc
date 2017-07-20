/**
*POJ1577 二叉树
*本题关键语句：The letters on a line will be listed in increasing alphabetical order.
*参考： http://www.cnblogs.com/yueshuqiao/archive/2012/04/03/2430711.html
*/
#include <stdio.h>

typedef struct Node
{
	char value;
	int left;
	int right;
}Node;

Node tree[30];

char data[27][28];
int readrow;
int treeindex;

void init()
{
	readrow = 0;
	treeindex = 1;

	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 28; j++)
			data[i][j] = 0;

	for (int j = 0; j < 30; j++)
	{
		tree[j].value = 0;
		tree[j].left = 0;
		tree[j].right = 0;
	}
}

void insertTree(int parent, char ch)
{
	if (ch < tree[parent].value)
	{
		if (tree[parent].left == 0)
		{
			tree[treeindex].value = ch;
			tree[parent].left = treeindex++;
			return;
		}
		else
		{
			insertTree(tree[parent].left, ch);
		}
	}
	else
	{
		if (tree[parent].right == 0)
		{
			tree[treeindex].value = ch;
			tree[parent].right = treeindex++;
			return;
		}
		else
		{
			insertTree(tree[parent].right, ch);
		}
	}

	return;
}

void printTree(int index)
{
	printf("%c", tree[index].value);
	if (tree[index].left > 0)
		printTree(tree[index].left);
	if (tree[index].right > 0)
		printTree(tree[index].right);
}
void process()
{
	tree[0].value = data[readrow - 1][0];
	tree[0].left = 0;
	tree[0].right = 0;
	for (int i = readrow-2; i >= 0; i--)
	{
		int j = 0;
		while (data[i][j] != 0)
		{
			insertTree(0, data[i][j]);
			j++;
		}
	}

	printTree(0);
	printf("\n");
}

int main()
{
	freopen("input.txt", "r", stdin);

	init();
	while (true)
	{
		scanf("%s", data[readrow]);

		if (data[readrow][0] == '$')
		{
			process();
			break;
		}
		
		if (data[readrow][0] == '*')
		{
			process();
			init();
			continue;
		}

		readrow++;
	}

	return 0;
}