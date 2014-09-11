/*
 * =====================================================================================
 *
 *       Filename:  malloc.c
 *
 *    Description:  堆的管理，关于堆的申请，释放以及堆管理器的算法，使用的隐式空闲链表
 *
 *        Version:  1.0
 *        Created:  2014年09月02日 11时37分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include "malloc.h"

/*概述：指向了空闲区域的序言块;
 *
 */
static char *  heap_list;

#define WSIZE 4 		//一个字的大小和头部和尾部的大小
#define DSIZE 8 		//一个双字的大小
#define CHUNKSIZE (1<<12) 	//扩展堆使用的大小

#define MAX(x, y) \
	((x)>(y)?(x):(y))

//将空闲区的大小和已分配位结合在一起生成一个值（头部或者尾部）
#define PACK(size, alloc) \
	((size) | (alloc))

//获得p引用的字,这里的强制类型转化是至关重要的，参数p是一个典型的void *,不能进行间接的引用
#define GET(p) 	\
	(*(unsigned int *)p)

//将p引用的字进行赋值运算
#define PUT(p, val) 	\
	(*(unsigned int *)p = (val))

//从头部或者尾部获得大小
#define GET_SIZE(p) 	\
	(GET(p) & ~0x7) 
//从头部或者尾部获得已分配的位
#define GET_ALLOC(p) 	\
	(GET(p) & 0x1)
 
//获取头部的地址
#define HDRP(bp) 	\
	((char *)(bp) - WSIZE)
//获取尾部的地址
#define FTRP(bp) 	\
	((char *)(bp) +GET_SIZE(HDRP(bp)) - DSIZE)
//获取后面的块的块指针,bp是块指针
#define NEXT_BLKP(bp) 	\
	((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
//获取前面的块的块指针
#define PREV_BLKP(bp) 	\
	((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/*
 *概述：回收堆中的空闲地址
 *
 *
 */
static void *coalesce(void *bp)
{
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
	size_t size = GET_SIZE(HDRP(bp));

	//前面的块和后面的块都是已分配的
	if (prev_alloc && next_alloc)  {
		return bp;
	} else if (prev_alloc && !next_alloc) {
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	} else if (!prev_alloc && next_alloc ) {
		size += GET_SIZE(HDRP(PREV_BLKP(bp)));
		PUT(FTRP(bp), PACK(size, 0));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
	} else {
		size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
	}
	
	return bp;
}

/*
 *扩展堆的大小
 *
 */

static void *extend_heap(size_t words)
{
	char *bp;
	size_t size;

	//判断是奇数或者偶数
	size = (words % 2) ? (words + 1) * WSIZE : words *WSIZE;
	if ((long)(bp = brk(size)) == -1) {
		return NULL;
	}

	PUT(HDRP(bp), PACK(size, 0));  		//初始化头部
	PUT(FTRP(bp), PACK(size, 0)); 		//初始化尾部
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); 	//初始化尾部

	return coalesce(bp);
}



/*
 *概述：heap的初始化
 *返回值：返回0,正确初始化，返回1,不能正确的初始化环境
 *
 */
int mm_init(void)
{
	if ((heap_list = brk(4*WSIZE)) == (void *) -1) {
		return -1;
	}

	PUT(heap_list, 0); 				//PUT是初始化
	PUT(heap_list + (1*WSIZE), PACK(DSIZE, 1));  	//头部的	
	PUT(heap_list + (2*WSIZE), PACK(DSIZE, 1));  	//尾部的
	PUT(heap_list + (3*WSIZE), PACK(0, 1)); 	//尾部的
	heap_list += (2*WSIZE);

	if (extend_heap(CHUNKSIZE/WSIZE) == NULL)  {
		return -1;
	}

	return  0;
}


/*
 *概述：释放内存
 *返回值：无
 */
void free(void *ptr)
{
	size_t size = GET_SIZE(HDRP(bp));
	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	
	coalesce(bp);
}

static void * find_fit(unsigned size) 
{
	char * block;
	char *heap_listp = heap_list;
	unsigned block_size = GET_SIZE(heap_listp);
	int block_flag = GET_ALLOC(heap_listp);
	
	for (; block_size != 0 && block_flag == 0; ;) {
		if (block_size >= size) {
			return heap_listp;
		} else {
			heap_listp = NEXT_BLKP(bp);
			block_size = GET_SIZE(heap_listp);
			block_flag = GET_ALLOC(heap_listp);
		}
	}

	return NULL;
}


static void place(char *bp, unsigned size)
{
	unsigned block_size = GET_SISE(bp);
	
	if (block_size == size) {
		return ;
	} else {
		
	}
}

/*
 *概述：申请内存
 *返回值：返回申请内存的首地址
 */
void *malloc(unsigned  size)
{
	size_t asize;
	size_t extendsize;
	char *bp;

	if (size == 0) {
		return NULL;
	}

	if (size <= DSIZE) {
		asize = 2 * DSIZE;
	} else {
		asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);
	}

	if ((bp = find_fit(asize)) != NULL) {
		place(bp, asize);
		returm bp;
	}

	extendsize = MAX(asize, CHUNKSIZE);
	if ((bp = extend_heap(extendsize / WSIZE)) == NULL) {
		return NULL;
	}

	place(bp, asize);

	return bp;
}
