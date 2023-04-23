#include "NanpureLib.h"


static int initOneLine(stOneLine* oneLine)
{
	int i;
	for (i = 0; i < NUM_MAX; i++)
	{
		oneLine->num[i] = 0;
	}
	return RET_OK;
}

static int setOneLine(stOneLine* oneLine, int x)
{
	int ret = RET_OK;

	if (x != NUM_NULL) {
		if (oneLine->num[x - NUM_MIN] == 1)
		{
			ret = RET_NG;
		}
		else
		{
			oneLine->num[x - NUM_MIN] = 1;
		}
	}
	return ret;
}

int printNanpure(stNanpureData* data)
{
	int ret = RET_OK;
	int x;
	int y;
	int one;

	for (y = 0; y < NUM_MAX; y++)
	{
		for (x = 0; x < NUM_MAX; x++)
		{
			one = data->num[y][x];
			if (one != NUM_NULL)
			{
				printf("[%1d]", one);
			}
			else {
				printf("[ ]", one);
			}
		}
		printf("\n");
	}
	return ret;
}

// 盤面全体がどういう状態かチェックする関数
enNanpureStatus checkNanpure(stNanpureData* data)
{
	enNanpureStatus ret = EN_NANPURE_NO_CHECK;
	int res;
	int x;
	int y;
	int ix;
	int iy;
	int one;
	int flag = 0;
	stOneLine one_line;

	/* 横方向の異常チェック */
	for (y = 0; y < NUM_MAX; y++)
	{
		initOneLine(&one_line);
		for (x = 0; x < NUM_MAX; x++)
		{
			one = data->num[y][x];
			if (one == NUM_NULL)
			{
				flag = 1;
			}
			res = setOneLine(&one_line, one);
			if (res == RET_NG)
			{
				ret = EN_NANPURE_ERROR;
				return ret;
			}
		}
	}

	/* 縦方向の異常チェック */
	for (x = 0; x < NUM_MAX; x++)
	{
		initOneLine(&one_line);
		for (y = 0; y < NUM_MAX; y++)
		{
			one = data->num[y][x];
			res = setOneLine(&one_line, one);
			if (res == RET_NG)
			{
				ret = EN_NANPURE_ERROR;
				return ret;
			}
		}
	}

	/* ボックスの異常チェック */
	for (y = 0; y < 3; y++)
	{
		for (x = 0; x < 3; x++)
		{
			initOneLine(&one_line);
			for (iy = 3 * y; iy < 3 * y + 3; iy++)
			{
				for (ix = 3 * x; ix < 3 * x + 3; ix++)
				{
					one = data->num[iy][ix];
					res = setOneLine(&one_line, one);
					if (res == RET_NG)
					{
						ret = EN_NANPURE_ERROR;
						return ret;
					}
				}
			}
		}
	}
	if (flag == 0)
	{
		ret = EN_NANPURE_COMPLETE;
	} else {
		ret = EN_NANPURE_NO_BAD;
	}
	return ret;
}

static int isCanSetLine(stNanpureData* data, int n, int y)
{
	for (int i = 0; i < SIZE_X; i++)
	{
		if (data->num[y][i] == n)
		{
			return 0;
		}
	}
	return 1;
}

static int isCanSetColumn(stNanpureData* data, int n, int x)
{
	for (int i = 0; i < SIZE_Y; i++)
	{
		if (data->num[i][x] == n)
		{
			return 0;
		}
	}
	return 1;
}

static int isCanSetBox(stNanpureData* data, int n, int x, int y)
{
	int x1 = (x / 3) * 3;
	int y1 = (y / 3) * 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (data->num[y1 + i][x1 + i] == n)
			{
				return 0;
			}
		}
	}
	return 1;
}

static int isCanSetTotal(stNanpureData* data, int n, int x, int y)
{
	return isCanSetLine(data, n, y) && isCanSetColumn(data, n, x) && isCanSetBox(data, n, x, y);
}

void calcNanpureAlgo1(stNanpureData* data, int n)
{
	static int s_ptn = 1;
	if (n == SIZE_X * SIZE_Y)
	{
		printf("PATTERN=%d\n", s_ptn++);
		printNanpure(data);
	}
	else
	{
		int x = n / SIZE_X;
		int y = n % SIZE_Y;
		if (data->num[y][x] != 0)
			calcNanpureAlgo1(data, n + 1);
		else {
			for (int i = 1; i <= NUM_MAX; i++) {
				if (isCanSetTotal(data, i, x, y)) {
					data->num[y][x] = i;
					calcNanpureAlgo1(data, n + 1);
					data->num[y][x] = 0;
				}
			}
		}
	}
	return;
}