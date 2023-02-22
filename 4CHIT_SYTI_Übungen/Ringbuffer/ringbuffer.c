/*
 * ringbuffer.c
 *
 */
#include <stdint.h>
#include "ringbuffer.h"


/* Structure for ring buffer */
typedef struct {
	uint8_t bufarry[RIBUSIZE]; /* char array for data                    */
	uint8_t * head;            /* head pointer to save next data item    */
	uint8_t * tail;            /* tail pointer to read oldest data item  */
	uint32_t state;            /* ring buffer state                      */
}ribu;

static ribu myribuf;

/* Initialize the ring buffer */
void ringbufferInit(void)
{
	ringbufferFlush();
	return;
}

/* Flush the ring buffer
 * Set head and tail pointer to the array start
 * Set the flags to OK and EMPTY
 * reset all data in the buffer
 * */
void ringbufferFlush(void) {
	int i;
	myribuf.head = myribuf.bufarry;
	myribuf.tail = myribuf.bufarry;
	myribuf.state = (1 << RIBU_OK);
	myribuf.state |= (1 << RIBU_EMPTY);
	for (i=0;i<RIBUSIZE;i++){
		//myribuf.bufarry[i] = 0;
		myribuf.bufarry[i] = 48 + i;
	}
	return;

}
/* Get the next free ring buffer entry
 * May be used for head and tail!
 * if the end of the buffer is reached, start with the beginning
 * */
static void ringbufferGetNext(uint8_t ** pt){

	/* TODO: increment pointer */
	// wenn der Pointer groeßer als der Puffer ist,
	// nimm das 1.Element
	(*pt)++;
	if((myribuf.bufarry + RIBUSIZE) < *pt)
	{
		*pt=myribuf.bufarry;
	}
	/* TODO: if pointer exceeds array set it to the beginning */
}
/* Put a character to the ring buffer
 * Set RIBU_DATALOST if ring buffer was already full
 * Clear RIBU_EMPTY and RIBU_NODATA */
uint32_t ringbufferPut(uint8_t chvar)
{
	if(myribuf.state & (1 << RIBU_FULL))
   	{
		/* if ring buffer is full the tail has to be shifted as well! */
		/*TODO: shift tail pointer here using "ringbufferGetNext()"*/
		myribuf.state |= (1 << RIBU_DATALOST);
	}
	/* Get next free buffer entry */
	/* TODO: shift head pointer here using "ringbufferGetNext()" */
	if (myribuf.head == myribuf.tail) {
		/* if head pointer == tail pointer the ring buffer is full! */
		myribuf.state |= (1 << RIBU_FULL);
	}
	/* Set states */
	myribuf.state &= (uint32_t)(~(1 << RIBU_EMPTY));
	myribuf.state &= (uint32_t)(~(1 << RIBU_NODATA));
	/* Save character to buffer */
	/* TODO: save value to array */
	/* return actual state */
	return myribuf.state;
}

/* Get a character from the ring buffer
 * When buffer is empty return state RIBU_NODATA
 * when ring buffer is not empty return a value
 * when tail pointer == head pointer the buffer is empty
 * Clear RIBU_NODATA and RIBU_DATALOST flags */
uint32_t ringbufferGet(uint8_t *chvar)
{
	/* Get a value when ring buffer is not empty */
	if(!(myribuf.state & (1 << RIBU_EMPTY))) {
		/* Get new value from tail pointer */
		/* TODO: shift tail pointer here using "ringbufferGetNext()" */
		ringbufferGetNext(&(myribuf.tail));
		/* Assign value to parameter */
		/* TODO: save value from array to chvar */
		*chvar = *myribuf.tail;
		/* now the ring buffer is not full, for sure */
		myribuf.state &= (uint32_t)(~(1 << RIBU_FULL));
		if (myribuf.head == myribuf.tail) {
			/* if tail pointer == head pointer the ring buffer is empty */
			myribuf.state |= (1 << RIBU_EMPTY);
		}
		/* clear RIBU_DATALOST and  RIBU_NODATA*/
		myribuf.state &= (uint32_t)(~(1 << RIBU_DATALOST));
		myribuf.state &= (uint32_t)(~(1 << RIBU_NODATA));
	} else {
		/* if the buffer was empty set the RIBU_NODATA flag */
		myribuf.state |= (1 << RIBU_NODATA);
	}
	/* return actual state */
	return myribuf.state;
}
/* Get status of the ring buffer */
uint32_t ringbufferGetState(void)
{
	return myribuf.state;
}
