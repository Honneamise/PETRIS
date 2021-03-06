/***********/
/* INCLUDE */
/***********/
#define _CRT_SECURE_NO_WARNINGS

//assert
#include "assert.h"

//std
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"

//pixie
#include "pixie_base.h"

/***********/
/* DEFINES */
/***********/
//endianness
#define P_BIG_ENDIAN        0
#define P_LITTLE_ENDIAN     1

//array
#define PARRAY_DEFAULT_SIZE 32

/*******************/
/* ENDIANNESS UTIL */
/*******************/
static int32_t PEndianness()
{
    volatile uint32_t i=0x01234567;
    
    return (*((uint8_t *)(&i))) == 0x67;
}

/********/
/* MATH */
/********/
void PSwap(int32_t *a, int32_t *b)
{
	assert(a!=NULL && b!=NULL);

    int32_t t = *a;
    *a = *b;
    *b = t;
}

/**********/
void PSwapf(float *a, float *b)
{
	assert(a!=NULL && b!=NULL);

    float t = *a;
    *a = *b;
    *b = t;
}

/**********/
int32_t PMin(int32_t a, int32_t b)
{
	return a <= b ? a : b;
}

/**********/
float PMinf(float a, float b)
{
	return a <= b ? a : b;
}

/**********/
int32_t PMax(int32_t a, int32_t b)
{
	return a >= b ? a : b;
}

/**********/
float PMaxf(float a, float b)
{
	return a >= b ? a : b;
}

/**********/
int32_t PRand(int32_t min, int32_t max)
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

/**********/
float PRandf(float min, float max)
{
	float f = rand() / ((float)(RAND_MAX)+1);

	if (min > max)
		return f * (min - max) + max;
	else
		return f * (max - min) + min;
}

/**********/
int32_t PMap(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**********/
float PMapf(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**********/
int32_t PClamp(int32_t x, int32_t min, int32_t max)
{
	int32_t t = x < min ? min : x;
	return t > max ? max : t;
}

/**********/
float PClampf(float x, float min, float max)
{
	float t = x < min ? min : x;
	return t > max ? max : t;
}

/**********/
float PRadiansf(float degrees)
{
	return (float)(degrees * (float)M_PI / 180.0f);
}

/**********/
float PDegreesf(float radians)
{
	return (float)(radians * 180.0f / (float)M_PI);
}

/**********/
/* MEMORY */
/**********/
void *PAlloc(size_t count, size_t size)
{
	assert(count>0 && size>0);

	void *p = calloc(count, size);

	if (p == NULL) { assert(p!=NULL); };

	return p;
}

/**********/
void *PRealloc(void* ptr, size_t size)
{
	assert(ptr!=NULL && size>0);

	void* p = realloc(ptr, size);

	if (p == NULL) { assert(p!=NULL); };

	return p;
}

/**********/
void PFree(void *p)
{
	if (p != NULL) { free(p); };
}

/*********/
/* ARRAY */
/*********/
void PArrayInit(PArray *array)
{
	assert(array!=NULL);

	array->size = PARRAY_DEFAULT_SIZE;
	array->elems_count = 0;
	array->elems = PAlloc(array->size,sizeof(void*));
}

/**********/
void PArrayClose(PArray *array, Performer func )
{
	assert(array!=NULL);

	if(func!=NULL)
	{
		for(int32_t i=0;i<array->elems_count;i++)
		{
			func(array->elems[i]);
		}
	}

	array->size = 0;
	array->elems_count = 0;
	PFree(array->elems);
	array->elems = NULL;
}

/***********/
void PArrayAdd(PArray *array, void *el)
{
	assert(array!=NULL);

	if(array->elems_count== array->size)
	{
		array->size *= 2;
		array->elems = PRealloc(array->elems,array->size*sizeof(void*));
	}

	array->elems[array->elems_count] = el;

	array->elems_count++;
}

/*********/
void *PArrayRemove(PArray* array, int32_t index)
{
	assert(array!=NULL);

	assert(index>=0 && index<array->elems_count);
	
	void *item = array->elems[index];

	for (int32_t i = index; i < array->elems_count-1; i++)
	{
		array->elems[i] = array->elems[i + 1];
	}

	array->elems_count--;

	return item;
}

/***********/
void *PArrayGet(PArray *array, int32_t index)
{
	assert(array!=NULL);

	assert(index>=0 && index<array->elems_count);

	return array->elems[index];
}

/**********/
void PArrayPerform(PArray *array, Performer func)
{
	assert(array!=NULL);

	if(func!=NULL)
	{
		for(int32_t i=0;i<array->elems_count;i++)
		{
			func(array->elems[i]);
		}
	}
}

/***********/
void PArraySort(PArray *array, Sorter func)
{
	assert(array!=NULL);

	assert(func!=NULL);

	qsort(array->elems, array->elems_count, sizeof(void*), (int32_t (*)(const void *, const void *))func);
}

/*********/
/* STACK */
/*********/
void PStackInit(PStack *stack)
{
	assert(stack!=NULL);

	PArrayInit(stack);
}

/**********/
void PStackClose(PStack *stack, void(*func)(void *elem) )
{
	assert(stack!=NULL);

	PArrayClose(stack,func);
}

/**********/
void PStackPush(PStack *stack, void *elem)
{
	assert(stack!=NULL);

	PArrayAdd(stack, elem);
}

/**********/
void *PStackPop(PStack *stack)
{
	assert(stack!=NULL);

	assert(stack->elems_count>0);

	return PArrayRemove(stack, stack->elems_count-1);
}

/**********/
void *PStackPeek(PStack *stack)
{
	assert(stack!=NULL);

	assert(stack->elems_count>0);

	return PArrayGet(stack, stack->elems_count-1);
}

/*********/
/* QUEUE */
/*********/
void PQueueInit(PQueue *queue)
{
	assert(queue!=NULL);

	PArrayInit(queue);
}

/**********/
void PQueueClose(PQueue *queue, void(*func)(void *elem) )
{
	assert(queue!=NULL);

	PArrayClose(queue,func);
}

/**********/
void PQueueEnq(PQueue *queue, void *elem)
{
	assert(queue!=NULL);

	PArrayAdd(queue, elem);
}

/**********/
void *PQueueDeq(PQueue *queue)
{
	assert(queue!=NULL);

	assert(queue->elems_count>0);

	return PArrayRemove(queue,0);
}

/**********/
void *PQueuePeek(PQueue *queue)
{
	assert(queue!=NULL);
	
	assert(queue->elems_count>0);

	return PArrayGet(queue, 0);
}

/***********/
/* BUFFERS */
/***********/
void PBufferLoad(char *file, uint8_t **buffer, int32_t *size)
{
	assert(file!=NULL);

	size_t _size = 0;

	FILE *fp = fopen(file, "rb");

	if (fp == NULL) { assert(fp!=NULL); } 
	else
	{
		assert(fseek(fp, 0, SEEK_END)==0);

		_size = ftell(fp);

		*buffer = PAlloc( _size, sizeof(uint8_t));

		assert(fseek(fp, 0, SEEK_SET)==0);

		size_t check = fread(*buffer, _size, 1, fp);

		assert(check==1);

		fclose(fp);
	}

	if(size!=NULL){ *size = (int32_t)_size; }
}

/**********/
uint8_t PBufferReadByte(uint8_t **buffer)
{
	assert(buffer!=NULL);

	assert(*buffer!=NULL);

    uint8_t *buf = &(**buffer);

    uint8_t val = buf[0];

    *buffer += 1;

    return val;
} 

/**********/
int16_t PBufferReadShort(uint8_t **buffer)
{
	assert(buffer!=NULL);

	assert(*buffer!=NULL);

    uint8_t *buf = &(**buffer);

    int16_t val = 0x00;

    if(PEndianness()==P_BIG_ENDIAN)
    {
        val = (buf[0]<<8) | buf[1];
    }
    else
    {
        val = (buf[1]<<8) | buf[0];
    }

    *buffer += 2;

    return val;
} 

/**********/
int32_t PBufferReadInt(uint8_t **buffer)
{
	assert(buffer!=NULL);

	assert(*buffer!=NULL);

    uint8_t *buf = &(**buffer);

    int32_t val = 0x00;
    
    if(PEndianness()==P_BIG_ENDIAN)
    {
        val = (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | buf[3];
        
    }
    else
    {
        val = (buf[3]<<24) | (buf[2]<<16) | (buf[1]<<8) | buf[0];
    }

    *buffer += 4;

    return val;
}

/**********/
float PBufferReadFloat(uint8_t **buffer)
{
	assert(buffer!=NULL);

	assert(*buffer!=NULL);
	
    uint8_t *buf = &(**buffer);

    float output = 0.0f;

	if(PEndianness()==P_BIG_ENDIAN)
    {
		*((uint8_t*)(&output) + 3) = buf[0];
		*((uint8_t*)(&output) + 2) = buf[1];
		*((uint8_t*)(&output) + 1) = buf[2];
		*((uint8_t*)(&output) + 0) = buf[3];
	}
	else
	{
		*((uint8_t*)(&output) + 3) = buf[3];
		*((uint8_t*)(&output) + 2) = buf[2];
		*((uint8_t*)(&output) + 1) = buf[1];
		*((uint8_t*)(&output) + 0) = buf[0];
	}

    *buffer += 4;

    return output;
}


