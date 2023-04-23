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
