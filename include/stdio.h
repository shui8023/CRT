/*
 * =====================================================================================
 *
 *       Filename:  stdio.h
 *
 *    Description:  标准IO的操作，包括格式化输入输出
 *
 *        Version:  1.0
 *        Created:  2014年08月26日 21时37分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef STDIO_H
#define STDIO_H

typedef int FILE

#define EOF (-1)

#define stdin  ((FILE*)0)
#define stdout ((FILE*)1)
#define stderr ((FILE*)2)

/*
 *概述：打开文件，参数为文件名，打开的方式和权限
 *返回值：返回一个文件指针
 */
FILE * fopen(const char *filename, const char *mode);

/*
 *概述：读取一个文件，
 *返回值：读取数据的字节数
 */

int fread(void *buffer, int size, int count, FILE *stream);

/*
 *概述：写入一个文件
 *返回值：返回写入数据的字节数
 */

int fwrite(const void *buffer, int size, int count, FILE *stream);

/*
 *概述：关闭一个文件
 *返回值：返回关闭文件的描述符
 */
int fclose(FILE *fd);

/*
 *概述：移动文件指针的位置
 */

int fseek(FILE *fp, int offset, int set);

#endif //STDIO_H

