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

#include "../include/stdio.h"
#include "../include/string.h"


/*概述：打开一个文件
 *返回值：返回一个文件描述符
 */

/*输出部分可以由多个约束，每个约束以"="开头，接着用一个字母来表示操作数的类型
 *输入部分与输出部分相似，但是没有"="
 *
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
	return fd;
}

static int read(int fd, void *buffer, unsigned size)
{
	int ret = 0;
	asm ("movl $3, %%eax \n\t"
	     "movl %1, %%ebx \n\t"
	     "movl %2, %%ecx \n\t"
	     "movl %3, %%edx \n\t"
	     "int  $0x80 \n\t"
	     "movl %%eax, %0 \n\t":
	     "=m"(ret):"m"(fd),"m"(buffer),"m"(size) );

	return ret;
}

static int write(int fd, const void *buffer, unsigned size) 
{
	int ret = 0;
	asm("movl $4, %%eax \n\t"
	    "movl %1, %%ebx \n\t"
	    "movl %2, %%ecx \n\t"
	    "movl %3, %%edx \n\t"
	    "int $0x80 \n\t"
	    "movl %%eax, %0 \n\t":
	    "=m"(ret):"m"(fd), "m"(buffer), "m"(size));

	return ret;
}

static int close(int fd)
{
	int ret = 0;
	asm ("movl $6, %%eax \n\t"
	     "movl %1, %%ebx \n\t"
	     "int $0x80 \n\t"
	     "movl %%eax, %0 \n\t":
	     "=m"(ret):"m"(fd)
	     );

	return ret;
}

static int seek(int fd, int offset, int mode) 
{
	int ret = 0;
	asm ("movl $19, %%eax \n\t"
	     "movl %1, %%ebx \n\t"
	     "movl %2, %%ecx \n\t"
	     "movl %3, %%edx \n\t":
	     "=m"(ret):"m"(fd),"m"(offset),"m"(mode)
	     );

	return ret;
}


/*
 *概述：打开文件，参数为文件名，打开的方式和权限
 *返回值：返回一个文件指针
 */
FILE * fopen(const char *filename, const char *mode)
{
	int fd = -1;
	int flags = 0;
	int access = 00700;

#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR   02
#define O_CREAT  0100
#define O_TRUNC  01000
#define O_APPEND 02000

	if (strcmp(mode, "w") == 0) {
		flags |= O_WRONLY | O_CREAT | O_TRUNC;
	}

	if (strcmp(mode, "w+") == 0) {
		flags |= O_RDWR | O_CREAT | O_TRUNC;
	}

	if (strcmp(mode, "r") == 0) {
		flags |= O_RDONLY;
	}

	if (strcmp(mode, "r+") == 0) {
		flags |= O_RDWR | O_CREAT;
	}
	
	fd = open(filename, flags, access);

	return (FILE *)fd;
}

/*
 *概述：读取一个文件，
 *返回值：读取数据的字节数
 */

int fread(void *buffer, int size, int count, FILE *stream)
{
	return read((int)stream, buffer, size * count);
}



/*
 *概述：写入一个文件
 *返回值：返回写入数据的字节数
 */

int fwrite(const void *buffer, int size, int count, FILE *stream)
{
	return write((int)stream, buffer, size * count);
}



/*
 *概述：关闭一个文件
 *返回值：返回关闭文件的描述符
 */
int fclose(FILE *fd)
{
	return close((int)fd);
}


/*
 *概述：移动文件指针的位置
 */

int fseek(FILE *fp, int offset, int set)
{
	return seek((int)fp, offset, set);
}


int fputc(int c, FILE *stream)
{
	if (fwrite(&c, 1, 1, stream) != 1)  {
		return EOF;
	} else {
		return c;
	}
}

int fputs(const char *str, FILE *stream)
{
	int len = strlen(str);

	if (fwrite(str, 1, len, stream) != len) {
		return EOF;
	} else {
		return len;
	}
}

int 
printf(const char *format, ...)
{
	va_list arg_start;
	va_start(arg_start, format);

	return vfprintf(stdout, format, arg_start);

}

int  vfprintf(FILE *stream, const char *format, va_list arg_start)
{
	int number = 0 ;
	int flags = 0;
	const char *p;
	for (p = format; *p != '\0'; ++p) {
		switch (*p) {
			case '%': {
				if (!flags) {
					flags = 1;
				} else {
					if (fputc('%', stream) < 0) {
						return EOF;
					}
					++number;
					flags = 0;
				}
				break;
			}
			case 'd': {
				if (flags) {
					char buf[16];
					flags = 0;
					itoa(va_arg(arg_start, int), buf, 10);
					if (fputs(buf, stream) < 0) {
						return EOF;
					}
					number += strlen(buf);
				} else if (fputc('c', stream) < 0) {
					return EOF;
				} else {
					++number;
				}
				break;
			}
			case 's': {
				if (flags) {
					const char *str = va_arg(arg_start, const char *);
					flags = 0;
					if (fputs(str, stream) < 0) {
						return EOF;
					}
					number += strlen(str);
				} else if (fputc('s', stream) < 0) {
					return EOF;
				} else {
					++number;
				}
				break;
			}
			default : {
				if (flags) {
					flags = 0;
				}	  

				if (fputc(*p, stream) < 0) {
					return EOF;
				} else {
					++number;
				}
				break;
			}
		}
	}	

	return number;
}

int fprintf(FILE *stream, const char *format, ...)
{
	va_list arg_start;
	va_start(arg_start, format);
	return vfprintf(stream, format, arg_start);
}

