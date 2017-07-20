/*
根据前序遍历和中序遍历的结果输出后续遍历的结果
*/
#include <stdio.h>
#include <string.h>

char preOrderStr[27];
char inOrderStr[27];
char postOrderStr[27];
int postOrderIndex = 0;

int getInOrderRootIndex(char root, char *inStr)
{
	int result = 0;
	while (*inStr != root)
	{
		inStr++;
		result++;
	}

	return result;
}

void OutputPostOrder(char *preStr, char *inStr)
{
	postOrderStr[postOrderIndex] = preStr[0];
	postOrderIndex++;

	int len = strlen(inStr);
	if (len == 1)
	{
		return;
	}

	int inOrderRootIndex = getInOrderRootIndex(preStr[0], inStr);
	
	char subPreStr[27];
	char subInStr[27];
	int i = 0;
	int j = 0;
	
	//处理右子树
	i = inOrderRootIndex + 1;
	j = 0;
	for (; i < len; i++,j++)
	{
		subInStr[j] = inStr[i];
		subPreStr[j] = preStr[i];
	}

	subInStr[j] = '\0';
	subPreStr[j] = '\0';

	if (inOrderRootIndex+1 < len)
	{
		OutputPostOrder(subPreStr, subInStr);
	}

	//处理左子数
	j = 0;
	for (j = 0; j < inOrderRootIndex; j++)
	{
		subInStr[j] = inStr[j];
		subPreStr[j] = preStr[j + 1];
	}
	subInStr[j] = '\0';
	subPreStr[j] = '\0';

	if (inOrderRootIndex > 0)
	{
		OutputPostOrder(subPreStr, subInStr);
	}

}

int main()
{
	while (scanf("%s %s", preOrderStr, inOrderStr) != EOF)
	{
		postOrderIndex = 0;
		OutputPostOrder(preOrderStr, inOrderStr);
		while (postOrderIndex > 0)
		{
			printf("%c", postOrderStr[postOrderIndex - 1]);
			postOrderIndex--;
		}
		printf("\n");
	}

	return 0;
}