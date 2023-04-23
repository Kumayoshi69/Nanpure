// NanpureCPP.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "NanpureCPP.h"
#include "NanpureLib.h"

using namespace std;

int main()
{
	int res;
	cout << "Hello Nanpure." << endl;
	
	stNanpureData data = {{
		{1,0,0,0,0,0,0,0,0},
		{0,2,0,0,0,0,0,0,0},
		{0,0,3,0,0,0,0,0,0},
		{0,0,0,4,0,0,0,0,0},
		{0,0,0,0,5,0,0,0,0},
		{0,0,0,0,0,6,0,0,0},
		{0,0,0,0,0,0,7,0,0},
		{0,0,0,0,0,0,0,8,0},
		{0,0,0,0,0,0,0,0,9},
	}, EN_NANPURE_NO_CHECK };
	printNanpure(&data);
	res = checkNanpure(&data);
	switch (res)
	{
	case EN_NANPURE_NO_CHECK:
		cout << "This Nanpure is NO CHECK." << endl;
		break;
	case EN_NANPURE_NO_BAD:
		cout << "This Nanpure is NO BAD." << endl;
		break;
	case EN_NANPURE_COMPLETE:
		cout << "This Nanpure is COMPLETE." << endl;
		break;
	case EN_NANPURE_ERROR:
		cout << "This Nanpure is ERROR." << endl;
		break;
	default:
		cout << "This Nanpure is SYSTE ERROR." << endl;
		break;
	}
	calcNanpureAlgo1(&data, 1);
	return 0;

}
