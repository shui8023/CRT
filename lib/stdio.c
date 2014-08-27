/*
 * =====================================================================================
 *
 *       Filename:  stdio.c
 *
 *    Description:  输入输出函数的实现(关于文件)
 *
 *        Version:  1.0
 *        Created:  2014年08月27日 21时30分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include "stdio.h"


/*概述：打开一个文件
 *返回值：返回一个文件描述符
 */
static int open(const char *pathname, int flags, int mode)
{
	int fd = 0;

	asm ( "movl $5, %%eax \n\t"
	      "movl %1, %%ebx \n\t"
	      "movl %2, %%ecx \n\t"
	      "movl %3, %%edx \n\t"
	      "int $0x80      \n\t"
	      "movl %%eax, %0 \n\t":
	      "=m"(fd):"m"(pathname), "m"(flags), "m"(mode));
}

static int read(int fd, void *buffer, unsigned size)
{
	
}
