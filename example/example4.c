/*
   This is a second simple example for Dynamic Creator library.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "dc.h"
void print_mt_struct(mt_struct *mts);

int main(int argc, char *argv[])
{
    int i;
    mt_struct *mts;
    int bit;
    int mexp;
    int start_id;
    int end_id;
    int seed = 4172;

    if (argc < 5) {
	printf("%s bit mexp start_id end_id [seed]\n", argv[0]);
	return 1;
    }
    bit = (int)strtol(argv[1], NULL, 10);
    if (errno != 0) {
	printf("bit format error\n");
	return 1;
    }
    if (bit != 32 && bit != 31) {
	printf("bit is 32 or 31\n");
	return 1;
    }
    mexp = (int)strtol(argv[2], NULL, 10);
    if (errno != 0) {
	printf("mexp format error\n");
	return 1;
    }
    switch (mexp) {
    case 521:
    case 607:
    case 1279:
    case 2203:
    case 2281:
    case 3217:
    case 4253:
    case 4423:
    case 9689:
    case 9941:
    case 11213:
    case 19937:
    case 21701:
    case 23209:
    case 44497:
	break;
    default:
	printf("mexp error\n");
	return -1;
    }
    start_id = (int)strtol(argv[3], NULL, 10);
    if (errno) {
	printf("start_id format error\n");
	return -1;
    }
    end_id = (int)strtol(argv[4], NULL, 10);
    if (errno) {
	printf("end_id format error\n");
	return -1;
    }
    if ((start_id < 0) || (end_id > 65535) || (start_id > end_id)) {
	printf("id should be: 0 <= start_id <= end_id <= 65535\n");
	return -1;
    }
    if (argc > 5) {
	seed = (int)strtol(argv[5], NULL, 10);
	if (errno != 0) {
	    printf("seed format error\n");
	    return -1;
	}
    }
    init_dc(seed);

    for (i = start_id; i <= end_id; i++) {
	mts = get_mt_parameter_id(bit,mexp,i);
	if (mts == NULL) {
	    printf ("# can't find parameter for id = %d skipping...\n", id);
	    return 1;
	} else {
	    print_mt_struct(mts);
	    free_mt_struct(mts);
	}
    }
    return 0;
}

void print_mt_struct(mt_struct *mts) {
    static int first = 1;

    if (first) {
	printf("#aaa,mm,nn,rr,ww,wmask,umask,lmask,"
	       "shift0,shift1,shiftB,shiftC,maskB,maskC\n");
	first = 0;
    }
    printf("%08"PRIx32", ", mts->aaa);
    printf("%"PRId32", ", mts->mm);
    printf("%"PRId32", ", mts->nn);
    printf("%"PRId32", ", mts->rr);
    printf("%"PRId32", ", mts->ww);
    printf("%08"PRIx32", ", mts->wmask);
    printf("%08"PRIx32", ", mts->umask);
    printf("%08"PRIx32", ", mts->lmask);
    printf("%"PRId32", ", mts->shift0);
    printf("%"PRId32", ", mts->shift1);
    printf("%"PRId32", ", mts->shiftB);
    printf("%"PRId32", ", mts->shiftC);
    printf("%08"PRIx32", ", mts->maskB);
    printf("%08"PRIx32"\n", mts->maskC);
}
