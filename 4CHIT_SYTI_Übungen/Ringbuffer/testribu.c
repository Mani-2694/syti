/*
 * testribu.c
 *
 */
#include <stdint.h>
#include <stdio.h>
#include "ringbuffer.h"
#include "testribu.h"

/* For testing use ring buffer with 5 entries */
#if RIBUSIZE != 5
#error Please set RIBUSIZE to 5 for testing
#endif

/* Testcase 1 */
/* Test if Ring buffer is empty after Initialization */
static int testribuReadEmpty(void)
{
	uint8_t ch = 0;
	uint32_t state;
	ringbufferInit();
	state = ringbufferGet(&ch);

	if (!(state & (1<< RIBU_EMPTY))) {
		printf("TestCase 1: init State not empty! \n");
		return -1;
	}
	if (!(state & (1<< RIBU_NODATA))) {
		printf("TestCase 1: init State no data bit ! \n");
		return -1;
	}

    return 0;
}

/* Testcase 2
 * Put a value
 * get the value
 * ringbuffer must be empty !
 * values must match
 * */
static int testribuWriteReadOne(void)
{
	uint8_t chin = 'a';
	uint8_t chout ;
	uint32_t state;
	ringbufferInit();
	state = ringbufferPut(chin);
	if (state & (1<< RIBU_EMPTY)) {
		printf("TestCase 2: Error - RIBU still empty! \n");
		return -1;
	}
	if (state & (1<< RIBU_FULL)) {
		printf("TestCase 2: Error - RIBU full! \n");
		return -1;
	}
	if (state & (1<< RIBU_DATALOST)) {
		printf("TestCase 2: Error - Data lost! \n");
		return -1;
	}
	if (state & (1<< RIBU_NODATA)) {
		printf("TestCase 2: Error - State no data bit ! \n");
		return -1;
	}

	state = ringbufferGet(&chout);

	if (!(state & (1<< RIBU_EMPTY))) {
		printf("TestCase 2: Error - State not empty! \n");
		return -1;
	}
	if (state & (1<< RIBU_FULL)) {
		printf("TestCase 2: Error - RIBU full! \n");
		return -1;
	}
	if (state & (1<< RIBU_DATALOST)) {
		printf("TestCase 2: Error - Data lost! \n");
		return -1;
	}
	if (chin != chout) {
		printf("TestCase 2: Error - data do not match! \n");
		return -1;
	}
	if (state & (1<< RIBU_NODATA)) {
		printf("TestCase 2: Error - State no data bit ! \n");
		return -1;
	}
    return 0;
}

/* TestCase 3
 * Write 5 values
 * Read 5 values
 * compare values
 * check ringbufferstate
 * */
static int testribuWrite5Read5(void)
{
	uint8_t chin[5] = {'a','b','c','d','e'};
	uint8_t chout[5];
	uint32_t state;
	int i = 0;
	ringbufferInit();

	/* write the 5 values to the buffer */
	for (i=0;i<5;i++) {
		state = ringbufferPut(chin[i]);
		if (state & (1<< RIBU_EMPTY)) {
			printf("TestCase 3: Error Put - RIBU still empty (i=%d)! \n",i);
			return -1;
		}
		if (i != 4) {
			/* Ribu must not be full for the first 4 values */
			if (state & (1<< RIBU_FULL)) {
				printf("TestCase 3: Error Put - RIBU full (i=%d)! \n",i);
				return -1;
			}
		} else {
			if (!(state & (1<< RIBU_FULL))) {
				printf("TestCase 3: Error Put - RIBU NOT full (i=%d)! \n",i);
				return -1;
			}
		}
		if (state & (1<< RIBU_DATALOST)) {
			printf("TestCase 3: Error Put - Data lost (i=%d)! \n",i);
			return -1;
		}
		if (state & (1<< RIBU_NODATA)) {
			printf("TestCase 3: Error Put - no data bit ! \n");
			return -1;
		}
	}
	/* read the 5 values from the buffer */
	for (i=0;i<5;i++) {
		state = ringbufferGet(&(chout[i]));

		/* The buffer must not be empty for the first 4 values */
		if (i != 4) {
			if (state & (1<< RIBU_EMPTY)) {
				printf("TestCase 3: Error Get - RIBU empty (i=%d)! \n",i);
				return -1;
			}
		} else {
            /* The ring buffer must be empty at the last value */
			if (!(state & (1<< RIBU_EMPTY))) {
				printf("TestCase 3: Error Get - RIBU NOT empty (i=%d)! \n",i);
				return -1;
			}
		}
		if (state & (1<< RIBU_FULL)) {
			printf("TestCase 3: Error Get - RIBU full (i=%d)! \n",i);
			return -1;
		}
		if (state & (1<< RIBU_DATALOST)) {
			printf("TestCase 3: Error Get - Data lost (i=%d)! \n",i);
			return -1;
		}
		if (state & (1<< RIBU_NODATA)) {
			printf("TestCase 3: Error Get - no data bit ! \n");
			return -1;
		}
	}
	/* compare values */
	for (i=0;i<5;i++) {
		if(chin[i] != chout[i]) {
			printf("TestCase 3: Error - Values do not match! \n");
			return -1;
		}
	}
	return 0;
}
/* TestCase 4
 * Write 7 values
 * Read 6 values
 * compare values
 * check ringbufferstate
 * */
static int testribuWrite7Read6(void)
{
	uint8_t chin[7] = {'a','b','c','d','e','f','g'};
	uint8_t chout[5];
	uint32_t state;
	int i = 0;
	ringbufferInit();

	/* write the 5 values to the buffer */
	for (i=0;i<5;i++) {
		state = ringbufferPut(chin[i]);
		if (state & (1<< RIBU_EMPTY)) {
			printf("TestCase 4: Error Put - RIBU still empty (i=%d)! \n",i);
			return -1;
		}
		if (i != 4) {
			/* Ribu must not be full for the first 4 values */
			if (state & (1<< RIBU_FULL)) {
				printf("TestCase 4: Error Put - RIBU full (i=%d)! \n",i);
				return -1;
			}
		} else {
			if (!(state & (1<< RIBU_FULL))) {
				printf("TestCase 4: Error Put - RIBU NOT full (i=%d)! \n",i);
				return -1;
			}
		}
		if (state & (1<< RIBU_DATALOST)) {
			printf("TestCase 4: Error Put - Data lost (i=%d)! \n",i);
			return -1;
		}
	}
	/* write 6th value */
	state = ringbufferPut(chin[i++]);
	if (state & (1<< RIBU_EMPTY)) {
		printf("TestCase 4: Error Put - RIBU still empty (i=%d)! \n",i);
		return -1;
	}
	if (!(state & (1<< RIBU_FULL))) {
		printf("TestCase 4: Error Put - RIBU NOT full (i=%d)! \n",i);
		return -1;
	}
	if (!(state & (1<< RIBU_DATALOST))) {
		printf("TestCase 4: Error Put - Data NOT lost (i=%d)! \n",i);
		return -1;
	}
	/* write 7th value */
	state = ringbufferPut(chin[i++]);
	if (state & (1<< RIBU_EMPTY)) {
		printf("TestCase 4: Error Put - RIBU still empty (i=%d)! \n",i);
		return -1;
	}
	if (!(state & (1<< RIBU_FULL))) {
		printf("TestCase 4: Error Put - RIBU NOT full (i=%d)! \n",i);
		return -1;
	}
	if (!(state & (1<< RIBU_DATALOST))) {
		printf("TestCase 4: Error Put - Data NOT lost (i=%d)! \n",i);
		return -1;
	}

	/* read the 5 values from the buffer */
	for (i=0;i<5;i++) {
		state = ringbufferGet(&(chout[i]));

		/* The buffer must not be empty for the first 4 values */
		if (i != 4) {
			if (state & (1<< RIBU_EMPTY)) {
				printf("TestCase 4: Error Get - RIBU empty (i=%d)! \n",i);
				return -1;
			}
		} else {
            /* The ring buffer must be empty at the last value */
			if (!(state & (1<< RIBU_EMPTY))) {
				printf("TestCase 4: Error Get - RIBU NOT empty (i=%d)! \n",i);
				return -1;
			}
		}
		if (state & (1<< RIBU_FULL)) {
			printf("TestCase 4: Error Get - RIBU full (i=%d)! \n",i);
			return -1;
		}
		if (state & (1<< RIBU_DATALOST)) {
			printf("TestCase 4: Error Get - Data lost (i=%d)! \n",i);
			return -1;
		}
	}
	/* compare values */
	for (i=0;i<5;i++) {
		if(chin[i+2] != chout[i]) {
			printf("TestCase 4: Error - Values do not match! \n");
			return -1;
		}
	}
	return 0;

}


static void testribuPrintStatus(uint32_t state)
{
	if (state & (1 << RIBU_OK)){
		printf("The RIBU_OK flag is set \n");
	}
	if (state & (1 << RIBU_FULL)){
		printf("The RIBU_FULL flag is set \n");
	}
	if (state & (1 << RIBU_EMPTY)){
		printf("The RIBU_EMPTY flag is set \n");
	}
	if (state & (1 << RIBU_NODATA)){
		printf("The RIBU_NODATA flag is set \n");
	}
	if (state & (1 << RIBU_DATALOST)){
		printf("The RIBU_DATALOST flag is set \n");
	}
	return;
}
static int testribuDoAnything(void)
{
	char inp;
	uint32_t state = 0;
	printf("What to do?\n");
	printf("1 .. print status\n");
	printf("2 .. put value\n");
	printf("3 .. get value\n");
	printf("4 .. flush buffer\n");
	printf("X .. eXit\n");
	scanf(" %c",&inp);
	switch(inp)
	{
	case 'X':
		return -1;
		break;
	case '1':
		state = ringbufferGetState();
		testribuPrintStatus(state);
		break;
	case '2':
		printf("give value: ");
		scanf(" %c",&inp);
		state = ringbufferPut((uint8_t)inp);
		break;
	case '3':
		state = ringbufferGet((uint8_t*)(&inp));
		printf("Value from ribu: %c \n",inp);
		break;
	case '4':
		ringbufferFlush();
		break;

	default:
		printf("Try again!\n");
		break;
	}

	return 0;
}

int testribuManualTest(void) {


	ringbufferFlush();
	while (testribuDoAnything() != -1);

	return 0;
}

int testribuDoTests(void){


	if (testribuReadEmpty() != 0) {
		return -1;
	}
	if (testribuWriteReadOne() != 0) {
		return -1;
	}
	if (testribuWrite5Read5() != 0) {
		return -1;
	}
	if (testribuWrite7Read6() != 0) {
		return -1;
	}
	return 0;
}
