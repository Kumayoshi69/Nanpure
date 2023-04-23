#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define RET_OK (0)
#define RET_NG (1)
#define SIZE_X (9)
#define SIZE_Y (9)
#define NUM_NULL (0)
#define NUM_MIN (1)
#define NUM_MAX (9)

typedef enum _tag_enNanpureStatus {
	EN_NANPURE_NO_CHECK,
	EN_NANPURE_NO_BAD,
	EN_NANPURE_ERROR,
	EN_NANPURE_COMPLETE
} enNanpureStatus;

typedef struct _tag_stOneLine {
	int num[NUM_MAX];
} stOneLine;

typedef struct _tag_stNanpureData {
	int num[SIZE_Y][SIZE_X];
	enNanpureStatus status;
} stNanpureData;

extern int printNanpure(stNanpureData* data);
extern int checkNanpure(stNanpureData* data);
extern void calcNanpureAlgo1(stNanpureData* data, int n);

#ifdef __cplusplus
}
#endif
