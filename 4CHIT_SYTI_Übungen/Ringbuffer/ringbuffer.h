/*
 * ringbuffer.h
 *
 */

#ifndef __RINGBUFFER_H_
#define __RINGBUFFER_H_
#include <stdint.h>

#define RIBUSIZE 5

typedef enum {
RIBU_OK,
RIBU_FULL,
RIBU_EMPTY,
RIBU_NODATA,
RIBU_DATALOST
}ribu_states;

void ringbufferInit(void);
void ringbufferFlush(void);
uint32_t ringbufferPut(uint8_t chvar);
uint32_t ringbufferGet(uint8_t *chvar);
uint32_t ringbufferGetState(void);

#endif /* RINGBUFFER_H_ */
