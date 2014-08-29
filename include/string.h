/*
 * =====================================================================================
 *
 *       Filename:  string.h
 *
 *    Description:  字符串的操作函数
 *
 *        Version:  1.0
 *        Created:  2014年08月26日 21时54分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#ifndef STRING_H
#define STRING_H

typedef unsigned size_t;

#define NULL 	0x0

/*概述： 函数strlen计算s指向的串的长度
 *返回值：返回空字符前面的字符的数目
 */
size_t strlen(const char *s);

/*
 *概述：将s2指向的串包括终止的空字符串复制给s1指向的数组
 *返回值：返回s1的值
 */
char *strcpy(char *s1, const char *s2);

/*
 *概述：将s2指向字符串中复制最多n个字符（不复制空字符后面的字符）到s1指向的数组中，
 *如果s2指向的字符串是一个长度比n短的字符串，则在s1指向的数组后面添加空字符，直到写入了n个字符
 *返回值：返回s1的值
 */
char *strncpy(char *s1, const char *s2, size_t n);

/*
 *概述：对s1指向的串和s2指向的串进行比较
 *返回值：当s1指向的串大于，等于或者小于s2指向的串是，返回一个大于，等于或者小于零的整数
 */
int strcmp(const char *s1, const char *s2);


/*
 *概述：从s2指向的对象中复制n个字符到s1指向的对象中
 *返回值：返回s1的值
 */
void *memcpy(void *s1, const void *s2, size_t n);

/*
 *概述：将s1中指向的对象赋值为0,
 *返回值：返回s1的值
 */
void *bzero(char *s1);

/*
 *概述：将s指向的n个字节用c填充
 *返回值：返回s的值
 */
void *memset(void *s, int c, size_t n);

/*
 *概述：将数字转化为字符串
 *返回值：返回指向字符串的指针
 */
char *itoa(int n, char *str, int radix);
#endif //STRING_H
