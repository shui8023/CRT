/*
 * =====================================================================================
 *
 *       Filename:  malloc.h
 *
 *    Description:  对于堆的管理的操作
 *
 *        Version:  1.0
 *        Created:  2014年09月02日 11时10分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef MALLOC_H
#define MALLOC_H


#include "string.h"
#include "stdio.h"

typedef 
struct _heap_header  {
	enum {
		HEAP_BLOCK_FREE = 0xABABABAB,
		HEAP_BLOCK_USED = 0xCDCDCDCD,
	}type;
	unsigned size;
	struct _heap_header *next;
	struct _heap_header *prev;
}heap_header;

#define ADDR_ADD(a, o) 	\
	(((char *)(a)) + o)
#define HEADER_SIZE  	\
	(sizeof(heap_header))

/*
 *概述：释放内存
 *返回值：无
 */
void free(void *ptr);

/*
 *概述：申请内存
 *返回值：返回申请内存的首地址
 */
void *malloc(unsigned  size);

/*
 *
 *
 */
int mm_init(void);


#endif //MALLOC_H
