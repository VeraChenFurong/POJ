#include <stdio.h>

typedef struct Node{
	int x;
	int y;
} Node;

char map[10 + 1][15 + 1];
int book[10 + 1][15 + 1];
int MaxConnectedArea;
int MaxX, MaxY;
int RemoveX, RemoveY;
int LeftX, LeftY;

int STEP;
int FinalScore;
int LeftBalls;
int direction[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }, };

void printmap()
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void initBook()
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			book[i][j] = 0;
		}
	}
}

void getLeft(int x, int y)
{
	if (y < RemoveY)
	{
		RemoveY = y;
		RemoveX = x;
	}
	else if (y == RemoveY)
	{
		if (x < RemoveX)
		{
			RemoveX = x;
		}
	}
}

int BFS(int x, int y)
{
	Node queue[151];
	int head = 0;
	int tail = 0;

	char color;

	color = map[x][y];
	queue[tail].x = x;
	queue[tail].y = y;
	tail++;
	book[x][y] = 1;

	RemoveX = x;
	RemoveY = y;

	while (head < tail)
	{
		for (int k = 0; k < 4; k++)
		{
			int newx = queue[head].x + direction[k][0];
			int newy = queue[head].y + direction[k][1];

			if (newx < 1 || newx > 10 || newy < 1 || newy >15)
				continue;

			if (map[newx][newy] == color && book[newx][newy] == 0)
			{
				queue[tail].x = newx;
				queue[tail].y = newy;
				tail++;
				book[newx][newy] = 1;
				getLeft(newx, newy);
			}
		}
		head++;
	}

	return tail;
}

void Remove()
{
	//RemoveX = MaxX;
	//RemoveY = MaxY;

	Node queue[151];
	int head = 0;
	int tail = 0;
	int score;
	char color;

	STEP++;

	color = map[MaxX][MaxY];
	queue[tail].x = MaxX;
	queue[tail].y = MaxY;
	tail++;
	map[MaxX][MaxY] = ' ';

	while (head < tail)
	{
		for (int k = 0; k < 4; k++)
		{
			int newx = queue[head].x + direction[k][0];
			int newy = queue[head].y + direction[k][1];

			if (newx < 1 || newx > 10 || newy < 1 || newy >15)
				continue;

			if (map[newx][newy] == color)
			{
				queue[tail].x = newx;
				queue[tail].y = newy;
				tail++;
				map[newx][newy] = ' ';
				//getLeft(newx, newy);
			}
		}

		head++;
	}

	score = (tail - 2)*(tail - 2);
	FinalScore += score;
	LeftBalls -= tail;
	//Move 1 at(4, 1) : removed 32 balls of color B, got 900 points.
	printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points. \n", STEP, LeftX, LeftY, tail, color, score);
}

void Update()
{
	int eFlag[15 + 1];
	for (int j = 1; j <= 15; j++)
	{
		int firstEmpty = -1;
		int i = 1;
		int flag = 0;
		while (i <= 10)
		{
			char color = map[i][j];

			if (color != ' ')
			{
				flag = 1;//不是全空的列
			}

			if (color != ' ' && firstEmpty != -1)
			{
				map[firstEmpty][j] = map[i][j];
				map[i][j] = ' ';
				i = firstEmpty + 1;
				firstEmpty = -1;
				continue;
			}

			if (firstEmpty == -1 && color == ' ')
			{
				firstEmpty = i;
			}

			i++;
		}

		if (flag == 0)
		{
			eFlag[j] = 1;
		}
		else
		{
			eFlag[j] = 0;
		}
	}

	for (int j = 1; j <= 15; j++)
	{
		if (eFlag[j]) //
		{
			for (int k = j + 1; k <= 15; k++)
			{
				if (!eFlag[k])
				{
					for (int i = 1; i <= 10; i++)
					{
						map[i][j] = map[i][k];
						map[i][k] = ' ';
					}
					eFlag[k] = 1;
					break;
				}
			}
		}
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		//1. 读取数据
		for (int i = 10; i >= 1; i--)
		{
			char input[15 + 1];
			scanf("%s", input);
			for (int j = 1; j <= 15; j++)
			{
				map[i][j] = input[j - 1];
			}
		}

		//2. 初始化
		STEP = 0;
		FinalScore = 0;
		LeftBalls = 150;
		printf("Game %d: \n", t);
		printf("\n");

		//
		while (true)
		{
			MaxConnectedArea = 1;
			initBook();

			for (int i = 10; i >= 1; i--)
			{
				for (int j = 1; j <= 15; j++)
				{
					if (book[i][j] == 0 && map[i][j] != ' ')
					{
						//printf("%d    %d", i, j);
						int sum = BFS(i, j);
						//printf("     %d\n", sum);
						if (sum > MaxConnectedArea)
						{
							MaxConnectedArea = sum;
							MaxX = i;
							MaxY = j;
							LeftX = RemoveX;
							LeftY = RemoveY;
						}
						else if (sum == MaxConnectedArea)
						{
							if (RemoveY < LeftY || (RemoveY == LeftY && RemoveX < LeftX))
							{
								MaxX = i;
								MaxY = j;
								LeftX = RemoveX;
								LeftY = RemoveY;
								MaxConnectedArea = sum;
							}
						}
					}
				}
			}

			//找完最大为1，证明结束了, 终止条件
			if (MaxConnectedArea == 1)
			{
				break;
			}

			//
			Remove();
			Update();
		}

		//Final score : 4920, with 0 balls remaining.
		if (LeftBalls == 0)
			FinalScore += 1000;
		//Game 1: 

		printf("Final score: %d, with %d balls remaining.\n", FinalScore, LeftBalls);
		printf("\n");
	}

	return 0;
}